package ringzhl

import (
	"bytes"
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"errors"
	"fmt"
	"math/big"

	"github.com/ethereum/go-ethereum/crypto"
	"golang.org/x/crypto/sha3"
)

type Ring []ecdsa.PublicKey

type RingSign struct {
	Size  int       // size of ring
	M     [32]byte  // message
	C     big.Int   // ring signature value
	S     []big.Int // ring signature values
	Ring  Ring      // array of public keys
	Ix    big.Int   // key image x
	Iy    big.Int   // key image y
	Curve elliptic.Curve
}

// calculate key image I = x * H_p(P) where H_p is a hash function that returns a point
// H_p(P) = sha3(P) * G
func GenKeyImage(privkey ecdsa.PrivateKey) (big.Int, big.Int) {
	pubkey := privkey.Public().(*ecdsa.PublicKey)

	// calculate sha3(P)
	h_x, h_y := HashPoint(pubkey)

	// calculate H_p(P) = x * sha3(P) * G
	i_x, i_y := privkey.Curve.ScalarMult(h_x, h_y, privkey.D.Bytes())

	return *i_x, *i_y
}

func HashPoint(p *ecdsa.PublicKey) (*big.Int, *big.Int) {
	hash := sha3.Sum256(append(p.X.Bytes(), p.Y.Bytes()...))
	return p.Curve.ScalarBaseMult(hash[:])
}

// creates a ring with size specified by `size` and places the public key corresponding to `privkey` in index s of the ring
// returns a new key ring of type []*ecdsa.PublicKey
func GenNewKeyRing(size int, privkey ecdsa.PrivateKey, s int) ([]ecdsa.PublicKey, error) {
	ring := make([]ecdsa.PublicKey, size)
	pubkey := privkey.Public().(*ecdsa.PublicKey)

	if s > len(ring) {
		return nil, errors.New("index s out of bounds")
	}

	ring[s] = *pubkey

	for i := 1; i < size; i++ {
		idx := (i + s) % size
		priv, err := crypto.GenerateKey()
		if err != nil {
			return nil, err
		}

		pub := priv.Public()
		ring[idx] = *pub.(*ecdsa.PublicKey)
	}

	return ring, nil
}

// create ring signature from list of public keys given inputs:
// msg: byte array, message to be signed
// ring: array of *ecdsa.PublicKeys to be included in the ring
// privkey: *ecdsa.PrivateKey of signer
// s: index of signer in ring
func Sign(m [32]byte, ring []ecdsa.PublicKey, privkey ecdsa.PrivateKey, s int) (RingSign, error) {
	// check ringsize > 1
	ringsize := len(ring)
	if ringsize < 2 {
		return RingSign{}, errors.New("size of ring less than two")
	} else if s >= ringsize || s < 0 {
		return RingSign{}, errors.New("secret index out of range of ring size")
	}

	// setup
	//pubkey := privkey.Public().(*ecdsa.PublicKey)
	pubkey := privkey.PublicKey
	curve := pubkey.Curve
	var sig RingSign
	sig.Size = ringsize
	sig.M = m
	sig.Ring = ring
	sig.Curve = curve

	// check that key at index s is indeed the signer
	if ring[s] != pubkey {
		return RingSign{}, errors.New("secret index in ring is not signer")
	}

	// generate key image
	sig.Ix, sig.Iy = GenKeyImage(privkey)

	// start at c[1]
	// pick random scalar u (glue value), calculate c[1] = H(m, u*G) where H is a hash function and G is the base point of the curve
	C := make([]big.Int, ringsize)
	S := make([]big.Int, ringsize)

	// pick random scalar u
	u, err := rand.Int(rand.Reader, curve.Params().P)
	if err != nil {
		return RingSign{}, err
	}

	// start at secret index s
	// compute L_s = u*G
	l_x, l_y := curve.ScalarBaseMult(u.Bytes())
	// compute R_s = u*H_p(P[s])
	h_x, h_y := HashPoint(&pubkey)
	r_x, r_y := curve.ScalarMult(h_x, h_y, u.Bytes())

	l := append(l_x.Bytes(), l_y.Bytes()...)
	r := append(r_x.Bytes(), r_y.Bytes()...)

	// concatenate m and u*G and calculate c[s+1] = H(m, L_s, R_s)
	C_i := sha3.Sum256(append(m[:], append(l, r...)...))
	idx := (s + 1) % ringsize
	C[idx] = *new(big.Int).SetBytes(C_i[:])

	// start loop at s+1
	for i := 1; i < ringsize; i++ {
		idx := (s + i) % ringsize

		// pick random scalar s_i
		s_i, err := rand.Int(rand.Reader, curve.Params().P)
		S[idx] = *s_i
		if err != nil {
			return RingSign{}, err
		}

		if curve == nil {
			return RingSign{}, errors.New(fmt.Sprintf("No curve at index %d", idx))
		}
		if ring[idx].Curve == nil {
			return RingSign{}, errors.New(fmt.Sprintf("No public key at index %d", idx))
		}

		// calculate L_i = s_i*G + c_i*P_i
		px, py := curve.ScalarMult(ring[idx].X, ring[idx].Y, C[idx].Bytes()) // px, py = c_i*P_i
		sx, sy := curve.ScalarBaseMult(s_i.Bytes())                          // sx, sy = s[n-1]*G
		l_x, l_y := curve.Add(sx, sy, px, py)

		// calculate R_i = s_i*H_p(P_i) + c_i*I
		px, py = curve.ScalarMult(&sig.Ix, &sig.Iy, C[idx].Bytes()) // px, py = c_i*I
		hx, hy := HashPoint(&ring[idx])
		sx, sy = curve.ScalarMult(hx, hy, s_i.Bytes()) // sx, sy = s[n-1]*H_p(P_i)
		r_x, r_y := curve.Add(sx, sy, px, py)

		// calculate c[i+1] = H(m, L_i, R_i)
		l := append(l_x.Bytes(), l_y.Bytes()...)
		r := append(r_x.Bytes(), r_y.Bytes()...)
		C_i = sha3.Sum256(append(m[:], append(l, r...)...))

		if i == ringsize-1 {
			C[s] = *new(big.Int).SetBytes(C_i[:])
		} else {
			C[(idx+1)%ringsize] = *new(big.Int).SetBytes(C_i[:])
		}
	}

	// close ring by finding S[s] = ( u - c[s]*k[s] ) mod P where k[s] is the private key and P is the order of the curve
	S[s] = *new(big.Int).Mod(new(big.Int).Sub(u, new(big.Int).Mul(&C[s], privkey.D)), curve.Params().N)

	// check that u*G = S[s]*G + c[s]*P[s]
	ux, uy := curve.ScalarBaseMult(u.Bytes()) // u*G
	px, py := curve.ScalarMult(ring[s].X, ring[s].Y, C[s].Bytes())
	sx, sy := curve.ScalarBaseMult(S[s].Bytes())
	l_x, l_y = curve.Add(sx, sy, px, py)

	// check that u*H_p(P[s]) = S[s]*H_p(P[s]) + C[s]*I
	px, py = curve.ScalarMult(&sig.Ix, &sig.Iy, C[s].Bytes()) // px, py = C[s]*I
	hx, hy := HashPoint(&ring[s])
	tx, ty := curve.ScalarMult(hx, hy, u.Bytes())
	sx, sy = curve.ScalarMult(hx, hy, S[s].Bytes()) // sx, sy = S[s]*H_p(P[s])
	r_x, r_y = curve.Add(sx, sy, px, py)

	l = append(l_x.Bytes(), l_y.Bytes()...)
	r = append(r_x.Bytes(), r_y.Bytes()...)

	// check that H(m, L[s], R[s]) == C[s+1]
	C_i = sha3.Sum256(append(m[:], append(l, r...)...))

	if !bytes.Equal(ux.Bytes(), l_x.Bytes()) || !bytes.Equal(uy.Bytes(), l_y.Bytes()) || !bytes.Equal(tx.Bytes(), r_x.Bytes()) || !bytes.Equal(ty.Bytes(), r_y.Bytes()) { //|| !bytes.Equal(C[(s+1)%ringsize].Bytes(), C_i[:]) {
		return RingSign{}, errors.New("error closing ring")
	}

	// everything ok, add values to signature
	sig.S = S
	sig.C = C[0]

	return sig, nil
}

// verify ring signature contained in RingSign struct
// returns true if a valid signature, false otherwise
func Verify(sig RingSign) bool {
	// setup
	ring := sig.Ring
	ringsize := sig.Size
	S := sig.S
	C := make([]big.Int, ringsize)
	C[0] = sig.C
	curve := sig.Curve
	Ix := sig.Ix
	Iy := sig.Iy

	// calculate c[i+1] = H(m, s[i]*G + c[i]*P[i])
	// and c[0] = H)(m, s[n-1]*G + c[n-1]*P[n-1]) where n is the ring size
	for i := 0; i < ringsize; i++ {
		// calculate L_i = s_i*G + c_i*P_i
		px, py := curve.ScalarMult(ring[i].X, ring[i].Y, C[i].Bytes()) // px, py = c_i*P_i
		sx, sy := curve.ScalarBaseMult(S[i].Bytes())                   // sx, sy = s[i]*G
		l_x, l_y := curve.Add(sx, sy, px, py)

		// calculate R_i = s_i*H_p(P_i) + c_i*I
		px, py = curve.ScalarMult(&Ix, &Iy, C[i].Bytes()) // px, py = c[i]*I
		hx, hy := HashPoint(&ring[i])
		sx, sy = curve.ScalarMult(hx, hy, S[i].Bytes()) // sx, sy = s[i]*H_p(P[i])
		r_x, r_y := curve.Add(sx, sy, px, py)

		// calculate c[i+1] = H(m, L_i, R_i)
		l := append(l_x.Bytes(), l_y.Bytes()...)
		r := append(r_x.Bytes(), r_y.Bytes()...)
		C_i := sha3.Sum256(append(sig.M[:], append(l, r...)...))

		if i == ringsize-1 {
			C[0] = *new(big.Int).SetBytes(C_i[:])
		} else {
			C[i+1] = *new(big.Int).SetBytes(C_i[:])
		}
	}

	return bytes.Equal(sig.C.Bytes(), C[0].Bytes())
}

func Link(sig_a RingSign, sig_b RingSign) bool {
	return sig_a.Ix.Cmp(&sig_b.Ix) == 0 && sig_a.Iy.Cmp(&sig_b.Iy) == 0
}

package blockchain

import (
	"bytes"
	"crypto/sha256"
	"crypto/subtle"
	"encoding/gob"
	"fmt"
	"math/big"

	"github.com/hyperledger/fabric-sdk-go/pkg/client/channel"
)

type schnorrSigFF struct {
	V, A, C, R *big.Int
}

type keyParams struct {
	G, P, Q *big.Int
}

type QueryNIZK struct {
	Sig, Params []byte
}

func (setup *FabricSetup) NizkGet() ([]byte, []byte, error) {
	var nizk = new(QueryNIZK)
	var args []string
	args = append(args, "query")
	args = append(args, "querysign")
	transientDataMap := make(map[string][]byte)
	transientDataMap["result"] = []byte("Query NIZK from PublicPeer or Private Peer")
	response, err := setup.channelClient.Query(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1])}, TransientMap: transientDataMap})
	if err != nil {
		return nil, nil, fmt.Errorf(err.Error())
	}

	buf := bytes.NewBuffer(response.Payload)
	dec := gob.NewDecoder(buf)
	dec.Decode(nizk)

	//从链码请求来的不是nil说明解压成功，并且query操作并没有生成新的区块。

	// var sig = new(schnorrSigFF)
	// var keyparams = new(keyParams)

	// buf = bytes.NewBuffer(nizk.Sig)
	// dec = gob.NewDecoder(buf)
	// dec.Decode(sig)

	// buf = bytes.NewBuffer(nizk.Params)
	// dec = gob.NewDecoder(buf)
	// dec.Decode(keyparams)

	// fmt.Printf("sig=%+v\n", sig)
	// fmt.Printf("keyparams=%+v\n", keyparams)
	return nizk.Sig, nizk.Params, nil
}

func NizkPubVerify(data []byte, params []byte) bool {
	var isValid bool
	var sig = new(schnorrSigFF)
	var keyparams = new(keyParams)

	buf := bytes.NewBuffer(data)
	dec := gob.NewDecoder(buf)
	dec.Decode(sig)

	buf = bytes.NewBuffer(params)
	dec = gob.NewDecoder(buf)
	dec.Decode(keyparams)

	isValid = schnorrPubVerifyFF(sig.V, keyparams.G, sig.R, sig.A, keyparams.P, keyparams.Q)
	if isValid == true {
		return true
	} else {
		return false
	}
}

func NizkPriVerify(data []byte, params []byte) bool {
	var isValid bool
	var sig = new(schnorrSigFF)
	var keyparams = new(keyParams)

	if data == nil {
		println("didn't get the public peer sig in NizkPriVerify")
	}
	buf := bytes.NewBuffer(data)
	dec := gob.NewDecoder(buf)
	dec.Decode(sig)

	if params == nil {
		println("didn't get the public key params in NizkPriVerify")
	}
	buf = bytes.NewBuffer(params)
	dec = gob.NewDecoder(buf)
	dec.Decode(keyparams)

	//fmt.Printf("sig=%+v\n", sig)

	isValid = schnorrPriVerifyFF(sig.V, keyparams.G, sig.R, sig.A, keyparams.P, keyparams.Q)
	if isValid == true {
		return true
	} else {
		return false
	}
}

func schnorrPubVerifyFF(V, g, r, A, p, q *big.Int) bool {
	var c, Ac, Aq *big.Int
	// todo: should this return (bool, error)
	// todo verify that A is within [1, p) and
	// A^q = 1 mod p

	// sanity check that a is not 0; g^0 = A is a degenerate case
	if A.Cmp(big.NewInt(1)) <= 0 {
		return false // degenerate case
	}

	// make sure g is actually in the p-group
	if g.Cmp(p) >= 0 {
		return false // degnerate case
	}

	// A is within [1, p-1]
	// A greater than or equal to p
	if A.Cmp(p) >= 0 {
		return false // degenerate case
	}

	// A^q == 1 mod p
	Aq = big.NewInt(0)
	Aq.Exp(A, q, p)
	// check that Aq == 1; Aq.Cmp returns 0 if they equal
	if Aq.Cmp(big.NewInt(1)) != 0 {
		return false // degenerate case
	}

	// A^c mod p
	UserID := "E-voting-PrivatePeer-received"
	c = schnorrHash(g, V, A, UserID)
	Ac = big.NewInt(0)
	Ac.Exp(A, c, p)

	// g^r mod p
	gr := big.NewInt(0)
	gr.Exp(g, r, p)

	// g^r * A^c mod p
	V1 := big.NewInt(0)
	V1.Mul(gr, Ac)
	V1.Mod(V1, p)
	// computed V1 = g^r * A^c mod p

	// replace with own methods
	isVerified := subtle.ConstantTimeCompare(V.Bytes(), V1.Bytes())

	if isVerified == 1 {
		return true
	} else {
		return false
	}
}

func schnorrPriVerifyFF(V, g, r, A, p, q *big.Int) bool {
	var c, Ac, Aq *big.Int
	// todo: should this return (bool, error)
	// todo verify that A is within [1, p) and
	// A^q = 1 mod p

	// sanity check that a is not 0; g^0 = A is a degenerate case
	if A.Cmp(big.NewInt(1)) <= 0 {
		return false // degenerate case
	}

	// make sure g is actually in the p-group
	if g.Cmp(p) >= 0 {
		return false // degnerate case
	}

	// A is within [1, p-1]
	// A greater than or equal to p
	if A.Cmp(p) >= 0 {
		return false // degenerate case
	}

	// A^q == 1 mod p
	Aq = big.NewInt(0)
	Aq.Exp(A, q, p)
	// check that Aq == 1; Aq.Cmp returns 0 if they equal
	if Aq.Cmp(big.NewInt(1)) != 0 {
		return false // degenerate case
	}

	// A^c mod p
	UserID := "E-voting-PublicPeer-sent"
	c = schnorrHash(g, V, A, UserID)
	Ac = big.NewInt(0)
	Ac.Exp(A, c, p)

	// g^r mod p
	gr := big.NewInt(0)
	gr.Exp(g, r, p)

	// g^r * A^c mod p
	V1 := big.NewInt(0)
	V1.Mul(gr, Ac)
	V1.Mod(V1, p)
	// computed V1 = g^r * A^c mod p

	// replace with own methods
	isVerified := subtle.ConstantTimeCompare(V.Bytes(), V1.Bytes())

	if isVerified == 1 {
		return true
	} else {
		return false
	}
}

func schnorrHash(g, V, A *big.Int, id string) *big.Int {
	var c *big.Int
	var buf []byte

	buf = append(buf, g.Bytes()...)
	buf = append(buf, V.Bytes()...)
	buf = append(buf, A.Bytes()...)
	buf = append(buf, []byte(id)...)

	c = big.NewInt(0)
	digest := hashBuffer(buf)
	c.SetBytes(digest)
	return c
}

// this is to make it easier to drop in a different hash function
func hashBuffer(buf []byte) []byte {
	sum := sha256.Sum256(buf)
	// returning a slice
	// this converts the array in to a slice to that array
	return sum[:]
}

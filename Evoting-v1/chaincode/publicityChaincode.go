package main

import (
	"bytes"
	"encoding/gob"
	"fmt"

	"github.com/hyperledger/fabric-chaincode-go/shim"
	pb "github.com/hyperledger/fabric-protos-go/peer"
)

var Candidates = []string{"Jason", "Michael"}
var Hashed_Geohashes = []string{"Haidian", "Chaoyang"}

type publicChaincode struct {
}

// type SchnorrSigFF struct {
// 	V, A, C, R *big.Int
// }

// type KeyParams struct {
// 	G, P, Q *big.Int
// }

// type QueryNIZK struct {
// 	Sig, Params []byte
// }

// var privKey *dsa.PrivateKey

func (t *publicChaincode) Init(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("publicityChaincode Init")
	_, args := stub.GetFunctionAndParameters()
	var Candidate_1, Candidate_1_val, Candidate_2, Candidate_2_val string // Entities
	var err error

	if len(args) != 4 {
		return shim.Error("Incorrect number of arguments. Expecting 4")
	}

	// Initialize the chaincode
	Candidate_1 = args[0]
	Candidate_1_val = args[1]
	if in(Candidate_1_val, Candidates) == false {
		return shim.Error("Candidate not in Candidates")
	}

	Candidate_2 = args[2]
	Candidate_2_val = args[3]
	if in(Candidate_2_val, Candidates) == false {
		return shim.Error("Candidate not in Candidates")
	}

	// Write the state to the ledger
	err = stub.PutState(Candidate_1, []byte(Candidate_1_val))
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.PutState(Candidate_2, []byte(Candidate_2_val))
	if err != nil {
		return shim.Error(err.Error())
	}

	return shim.Success(nil)
}

func (t *publicChaincode) Invoke(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("publicityChaincode Invoke")
	function, args := stub.GetFunctionAndParameters()
	// Check whether it is an invoke request
	if function != "invoke" {
		return shim.Error("Unknown function call")
	}

	// Check whether the number of arguments is sufficient
	if len(args) < 1 {
		return shim.Error("The number of arguments is insufficient.")
	}

	// In order to manage multiple type of request, we will check the first argument.
	// Here we have one possible argument: query (every query request will read in the ledger without modification)
	fmt.Print("The function that has been invoke:")
	fmt.Println(args[0])

	// The update argument will manage all update in the ledger
	if args[0] == "invokevote" {
		return t.invokevote(stub, args)
	}

	// if args[0] == "nizksign" {
	// 	return t.nizksign(stub)
	// }

	if args[0] == "query" {
		return t.query(stub, args)
	}

	if args[0] == "count" {
		return t.result(stub)
	}

	return shim.Error("Invalid invoke function name. Expecting \"invokevote\" \"query\" \"nizksign\" ")
}

func (t *publicChaincode) query(stub shim.ChaincodeStubInterface, args []string) pb.Response {

	if args[1] == "queryvalue" {
		return t.queryvalue(stub, args[1:])
	}

	// if args[1] == "querysign" {
	// 	return t.querysign(stub)
	// }

	return shim.Error("Invalid invoke function name. Expecting \"queryvalue\" \"querysign\" ")
}

// func (t *publicChaincode) querysign(stub shim.ChaincodeStubInterface) pb.Response {
// 	var querynizk = new(QueryNIZK)
// 	var err error

// 	// Get the state from the ledger
// 	sig, err := stub.GetState("signature")
// 	if err != nil {
// 		jsonResp := "{\"Error\":\"Failed to get state for " + "signature" + "\"}"
// 		return shim.Error(jsonResp)
// 	}

// 	if sig == nil {
// 		jsonResp := "{\"Error\":\"Nil candidateNum for " + "signature" + "\"}"
// 		return shim.Error(jsonResp)
// 	}
// 	querynizk.Sig = sig

// 	params, err := stub.GetState("keyparams")
// 	if err != nil {
// 		jsonResp := "{\"Error\":\"Failed to get state for " + "keyparams" + "\"}"
// 		return shim.Error(jsonResp)
// 	}

// 	if params == nil {
// 		jsonResp := "{\"Error\":\"Nil candidateNum for " + "keyparams" + "\"}"
// 		return shim.Error(jsonResp)
// 	}
// 	querynizk.Params = params

// 	buf := bytes.NewBuffer(nil)
// 	enc := gob.NewEncoder(buf)
// 	err = enc.Encode(querynizk)
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	// jsonResp := "{" + Key + ":" + string(sig) + "}"
// 	// fmt.Printf("Query Response:%s\n", jsonResp)
// 	return shim.Success(buf.Bytes())
// }

func (t *publicChaincode) queryvalue(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	var Key string // Entities
	var err error

	if len(args) != 2 {
		return shim.Error("Incorrect number of arguments. Expecting name of the person to query")
	}

	Key = args[1]

	historyIter, err := stub.GetHistoryForKey(Key)

	if err != nil {
		fmt.Println(err)
		return shim.Error(err.Error())
	}

	for historyIter.HasNext() {
		modification, err := historyIter.Next()
		if err != nil {
			fmt.Println(err)
			return shim.Error(err.Error())
		}
		fmt.Println("Returning information related to", string(modification.Value))
	}

	// Get the state from the ledger
	// Keyvalbytes, err := stub.GetState(Key)
	// if err != nil {
	// 	jsonResp := "{\"Error\":\"Failed to get state for " + Key + "\"}"
	// 	return shim.Error(jsonResp)
	// }

	// if Keyvalbytes == nil {
	// 	jsonResp := "{\"Error\":\"Nil candidateNum for " + Key + "\"}"
	// 	return shim.Error(jsonResp)
	// }

	// jsonResp := "{" + Key + ":" + string(Keyvalbytes) + "}"
	// fmt.Printf("Query Response:%s\n", jsonResp)
	// return shim.Success(Keyvalbytes)
	return shim.Success(nil)
}

// func (t *publicChaincode) nizksign(stub shim.ChaincodeStubInterface) pb.Response {
// 	privKey = genKeys()
// 	sig, err := signFF(privKey.P, privKey.Q, privKey.G, privKey.Y, privKey.X)
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	buf := bytes.NewBuffer(nil)
// 	enc := gob.NewEncoder(buf)
// 	err = enc.Encode(sig)
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	err = stub.PutState("signature", buf.Bytes())
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	keyparams, err := queryparam()
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	err = stub.PutState("keyparams", keyparams)
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}

// 	// err = stub.PutState("UserID", []byte("E-voting-privatePeer-received"))
// 	// if err != nil {
// 	// 	return shim.Error(err.Error())
// 	// }

// 	return shim.Success(nil)
// }

func (t *publicChaincode) invokevote(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	var TxID, Candidate, Hashed_Geohash, Ring_signature string             // Entities
	var TxIDval, Candidateval, Hashed_Geohashval, Ring_signatureval string // Asset holdings
	var err error

	if len(args) != 9 {
		return shim.Error("Incorrect number of arguments. Expecting 9")
	}

	args = args[1:]
	fmt.Printf("%v", args)
	// Initialize the chaincode
	TxID = args[0]
	TxIDval = args[1]

	// Block = args[2]
	// BlockNum = args[3]
	// num, err = strconv.Atoi(BlockNum)

	// if err != nil {
	// 	fmt.Println(err)
	// }
	// if num < 1 {
	// 	return shim.Error("invalid BlockNum")
	// }

	Candidate = args[2]
	Candidateval = args[3]
	if in(Candidateval, Candidates) == false {
		return shim.Error("Candidate not in Candidates")
	}

	Hashed_Geohash = args[4]
	Hashed_Geohashval = args[5]
	if in(Hashed_Geohashval, Hashed_Geohashes) == false {
		return shim.Error("Hashed_Geohashval not in Hashed_Geohashs")
	}

	Ring_signature = args[6]
	Ring_signatureval = args[7]
	fmt.Printf("TxID = %s, Candidate = %s, Hashed_Geohash = %s, Ring_signature = %s\n", TxIDval, Candidateval, Hashed_Geohashval, Ring_signatureval)

	// Write the state to the ledger
	err = stub.PutState(TxID, []byte(TxIDval))
	if err != nil {
		return shim.Error(err.Error())
	}

	// err = stub.PutState(Block, []byte(BlockNum))
	// if err != nil {
	// 	return shim.Error(err.Error())
	// }

	err = stub.PutState(Candidate, []byte(Candidateval))
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.PutState(Hashed_Geohash, []byte(Hashed_Geohashval))
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.PutState(Ring_signature, []byte(Ring_signatureval))
	if err != nil {
		return shim.Error(err.Error())
	}

	// Notify listeners that an event "eventInvoke" have been executed
	err = stub.SetEvent("eventInvoke", []byte{})
	if err != nil {
		return shim.Error(err.Error())
	}

	return shim.Success(nil)
}

func (t *publicChaincode) result(stub shim.ChaincodeStubInterface) pb.Response {
	var candidate string
	var err error
	var Result = struct {
		Candidate_1       string
		Candidate_2       string
		Result_of_Jason   int64
		Result_of_Michael int64
	}{
		Candidate_1:       "Jason",
		Candidate_2:       "Michael",
		Result_of_Jason:   0,
		Result_of_Michael: 0,
	}

	historyIter, err := stub.GetHistoryForKey("Candidate")

	if err != nil {
		fmt.Println(err.Error())
		return shim.Error(err.Error())
	}

	for historyIter.HasNext() {
		modification, err := historyIter.Next()
		if err != nil {
			return shim.Error(err.Error())
		}
		if modification.IsDelete != true {
			candidate = string(modification.Value)
			if candidate == "Jason" {
				Result.Result_of_Jason += 1
			} else if candidate == "Michael" {
				Result.Result_of_Michael += 1
			} else {
				fmt.Println("We recorded some wrong value")
			}
		}
	}
	fmt.Println(Result)

	buf := bytes.NewBuffer(nil)
	enc := gob.NewEncoder(buf)
	err = enc.Encode(Result)
	if err != nil {
		return shim.Error(err.Error())
	}
	return shim.Success(buf.Bytes())
}

// Deletes an entity from state
// func (t *publicChaincode) delete(stub shim.ChaincodeStubInterface, args []string) pb.Response {
// 	if len(args) != 1 {
// 		return shim.Error("Incorrect number of arguments. Expecting 1")
// 	}

// 	A := args[0]

// 	// Delete the key from the state in ledger
// 	err := stub.DelState(A)
// 	if err != nil {
// 		return shim.Error("Failed to delete state")
// 	}

// 	return shim.Success(nil)
// }

// it is only used in testing the success of instantiating chaincode

func in(target string, str_array []string) bool {
	for _, element := range str_array {
		if target == element {
			return true
		}
	}
	return false
}

// func queryparam() ([]byte, error) {
// 	params := KeyParams{
// 		G: privKey.G,
// 		P: privKey.P,
// 		Q: privKey.Q,
// 	}

// 	buf := bytes.NewBuffer(nil)
// 	enc := gob.NewEncoder(buf)
// 	err := enc.Encode(params)
// 	if err != nil {
// 		return nil, err
// 	}

// 	return buf.Bytes(), nil
// }

// func genKeys() *dsa.PrivateKey {
// 	params := new(dsa.Parameters)
// 	privKey := new(dsa.PrivateKey)

// 	// is this the right way to refer to parameterSizes?
// 	err := dsa.GenerateParameters(params, rand.Reader, dsa.L2048N256)
// 	if err != nil {
// 		fmt.Printf("%v, \n", err)
// 	}
// 	privKey.PublicKey.Parameters = *params

// 	err = dsa.GenerateKey(privKey, rand.Reader)
// 	if err != nil {
// 		fmt.Printf("%v, \n", err)
// 	}
// 	return privKey
// }

// for finite field, hashes returns c = H(g || V || A || etc)
// returns the data set inside a big Int
// func schnorrHash(g, V, A *big.Int, id string) *big.Int {
// 	var c *big.Int
// 	var buf []byte

// 	buf = append(buf, g.Bytes()...)
// 	buf = append(buf, V.Bytes()...)
// 	buf = append(buf, A.Bytes()...)
// 	buf = append(buf, []byte(id)...)

// 	c = big.NewInt(0)
// 	digest := hashBuffer(buf)
// 	c.SetBytes(digest)
// 	return c
// }

// this is to make it easier to drop in a different hash function
// func hashBuffer(buf []byte) []byte {
// 	sum := sha256.Sum256(buf)
// 	// returning a slice
// 	// this converts the array in to a slice to that array
// 	return sum[:]
// }

// SignFF is a Schnorr signature over a Finite Field
// it proves knowledge of private key 'a' where A = g ^ a
// A is the public exponent
// g is a generator of G
// func signFF(p, q, g, A, a *big.Int) (*SchnorrSigFF, error) {
// 	// V is g ^ v
// 	// c is a bigInt and c = H(g || V || A || etc) after setting bytes
// 	// r = v - a*c mod q
// 	var V, c, r, ac *big.Int

// 	// sanity check that a is not 0; g^0 = A is a degenerate case
// 	if A.Cmp(big.NewInt(1)) <= 0 {
// 		return nil, fmt.Errorf("in SignFF, denegerate A == 0!\n")
// 	}

// 	// make sure g is actually in the p-group
// 	if g.Cmp(p) >= 0 {
// 		return nil, fmt.Errorf("in SignFF, degenerate g not in elem p\n")
// 	}

// 	// v is random number in [0, q)
// 	v, err := rand.Int(rand.Reader, q)
// 	if err != nil {
// 		return nil, fmt.Errorf("in SignFF, %v\n", err)
// 	}

// 	// V = g^v mod p
// 	// modular exponentiation may leak information
// 	V = big.NewInt(0)
// 	V.Exp(g, v, p)

// 	// c is the challenge
// 	// it has been redefined in the non-interactive version
// 	// c = H(g || V || A || UserID || OtherInfo)
// 	// https://tools.ietf.org/html/rfc8235#section-2.3
// 	// todo: change this out
// 	UserID := "E-voting-PrivatePeer-received"
// 	c = schnorrHash(g, V, A, UserID)

// 	// r = v-a*c mod q
// 	r = big.NewInt(0)

// 	// a*c mod q
// 	ac = big.NewInt(0)
// 	ac.Mul(a, c)
// 	ac.Mod(ac, q)

// 	// v - (a*c) mod q
// 	r.Sub(v, ac)
// 	r.Mod(r, q)

// 	// must send A, g, V, c, r
// 	// hopefully the public key A, g is sent already
// 	// verifier must verify that 1) A is a valid public key
// 	// and that 2) V = g^r * A^c

// 	SchnorrSig := new(SchnorrSigFF)
// 	SchnorrSig.V = V // g^v we send
// 	SchnorrSig.A = A // A is public key
// 	SchnorrSig.C = c // c is hash challenge
// 	SchnorrSig.R = r // r = v-a*c mod q we send

// 	return SchnorrSig, nil
// }

func main() {
	err := shim.Start(new(publicChaincode))
	if err != nil {
		fmt.Printf("Error starting Simple chaincode: %s", err)
	}
}

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

type votingChaincode struct {
}

//var privKey *dsa.PrivateKey

func (t *votingChaincode) Init(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("votingChaincode Init")
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

	//privKey = genKeys()

	return shim.Success(nil)
}

func (t *votingChaincode) Invoke(stub shim.ChaincodeStubInterface) pb.Response {
	fmt.Println("votingChaincode Invoke")
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

	if args[0] == "delete" {
		return t.delete(stub, args)
	}

	return shim.Error("Invalid invoke function name. Expecting \"invokevote\" \"query\" \"nizksign\" ")
}

func (t *votingChaincode) query(stub shim.ChaincodeStubInterface, args []string) pb.Response {

	if args[1] == "queryvalue" {
		return t.queryvalue(stub, args)
	}

	// if args[1] == "querysign" {
	// 	return t.querysign(stub)
	// }

	return shim.Error("Invalid invoke function name. Expecting \"queryvalue\" \"querysign\" ")
}

// func (t *votingChaincode) querysign(stub shim.ChaincodeStubInterface) pb.Response {
// 	//var querynizk = new(QueryNIZK)
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

func (t *votingChaincode) queryvalue(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	var Key string // Entities
	var err error

	if len(args) != 2 {
		return shim.Error("Incorrect number of arguments. Expecting name of the person to query")
	}

	Key = args[1]

	// Get the state from the ledger
	Keyvalbytes, err := stub.GetState(Key)
	if err != nil {
		jsonResp := "{\"Error\":\"Failed to get state for " + Key + "\"}"
		return shim.Error(jsonResp)
	}

	if Keyvalbytes == nil {
		jsonResp := "{\"Error\":\"Nil candidateNum for " + Key + "\"}"
		return shim.Error(jsonResp)
	}

	jsonResp := "{" + Key + ":" + string(Keyvalbytes) + "}"
	fmt.Printf("Query Response:%s\n", jsonResp)
	return shim.Success(Keyvalbytes)
}

// Transaction makes payment of X units from A to B
func (t *votingChaincode) invokevote(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	var Candidate, Hashed_Geohash, Address, Signature string              // Entities
	var Candidateval, Hashed_Geohashval, Addressval, Signature_val string // Asset holdings
	// var voterRingSign RingSign
	// var voterPrivateKey ecdsa.PrivateKey
	var err error

	// fmt.Printf("%v", args)

	if len(args) != 9 {
		fmt.Println(len(args))
		return shim.Error("Incorrect number of arguments. Expecting 9")
	}

	args = args[1:]
	// fmt.Printf("%v", args)
	// Initialize the chaincode
	Candidate = args[0]
	Candidateval = args[1]
	if in(Candidateval, Candidates) == false {
		return shim.Error("Candidate not in Candidates")
	}

	Hashed_Geohash = args[2]
	Hashed_Geohashval = args[3]
	if in(Hashed_Geohashval, Hashed_Geohashes) == false {
		return shim.Error("Hashed_Geohashval not in Hashed_Geohashs")
	}

	Address = args[4]
	Addressval = args[5]

	Signature = args[6]
	Signature_val = args[7]
	// Ring = args[7]
	// Pri = args[8]

	// msg := Candidateval + "_" + Hashed_Geohashval
	// msgHash := sha3.Sum256([]byte(msg))

	// buf := bytes.NewBuffer([]byte(Ring))
	// gob.Register(elliptic.P256())
	// dec := gob.NewDecoder(buf)
	// err = dec.Decode(&voterRingSign)
	// if err != nil {
	// 	fmt.Println("decode the voterRingSign")
	// 	return shim.Error(err.Error())
	// }

	// buf = bytes.NewBuffer([]byte(Pri))
	// gob.Register(elliptic.P256())
	// dec = gob.NewDecoder(buf)
	// err = dec.Decode(&voterPrivateKey)
	// if err != nil {
	// 	fmt.Println("decode the voterPrivateKey")
	// 	return shim.Error(err.Error())
	// }

	// voterRingSign, err = Sign(msgHash, voterRingSign.Ring, voterPrivateKey, 1)
	// if err != nil {
	// 	return shim.Error(err.Error())
	// }

	fmt.Printf("Candidate = %s, Hashed_Geohash = %s, Ring_signature = a structure\n", Candidateval, Hashed_Geohashval)

	// Write the state to the ledger
	err = stub.PutState(Candidate, []byte(Candidateval))
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.PutState(Hashed_Geohash, []byte(Hashed_Geohashval))
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.PutState(Address, []byte(Addressval))
	if err != nil {
		return shim.Error(err.Error())
	}

	// sign := bytes.NewBuffer(nil)
	// enc := gob.NewEncoder(sign)
	// gob.Register(elliptic.P256())
	// err = enc.Encode(voterRingSign)
	// if err != nil {
	// 	return shim.Error(err.Error())
	// }

	err = stub.PutState(Signature, []byte(Signature_val))
	if err != nil {
		return shim.Error(err.Error())
	}

	// Notify listeners that an event "eventInvoke" have been executed
	err = stub.SetEvent("eventInvoke", []byte{})
	if err != nil {
		return shim.Error(err.Error())
	}

	//return shim.Success(sign.Bytes())
	return shim.Success(nil)
}

func (t *votingChaincode) delete(stub shim.ChaincodeStubInterface, args []string) pb.Response {
	var Candidate, Hashed_Geohash, Address, Signature string // Entities
	var Candidateval, Hashed_Geohashval string               // Asset holdings

	var err error

	if len(args) != 9 {
		fmt.Println(len(args))
		return shim.Error("Incorrect number of arguments. Expecting 9")
	}

	args = args[1:]
	// fmt.Printf("%v", args)
	// Initialize the chaincode
	Candidate = args[0]
	Candidateval = args[1]
	if in(Candidateval, Candidates) == false {
		return shim.Error("Candidate not in Candidates")
	}

	Hashed_Geohash = args[2]
	Hashed_Geohashval = args[3]
	if in(Hashed_Geohashval, Hashed_Geohashes) == false {
		return shim.Error("Hashed_Geohashval not in Hashed_Geohashs")
	}

	Address = args[4]
	//Addressval = args[5]

	Signature = args[6]
	//Signature_val = args[7]

	fmt.Printf("We will delete the Tx Candidate = %s, Hashed_Geohash = %s, Ring_signature = a structure in private blockchian\n", Candidateval, Hashed_Geohashval)

	err = stub.DelState(Candidate)
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.DelState(Hashed_Geohash)
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.DelState(Address)
	if err != nil {
		return shim.Error(err.Error())
	}

	err = stub.DelState(Signature)
	if err != nil {
		return shim.Error(err.Error())
	}

	return shim.Success(nil)
}

func (t *votingChaincode) result(stub shim.ChaincodeStubInterface) pb.Response {
	var candidate string
	var err error
	result := struct {
		Result_of_Jason   int64
		Result_of_Michael int64
	}{
		Result_of_Jason:   0,
		Result_of_Michael: 0,
	}

	historyIter, err := stub.GetHistoryForKey("Candidate")

	if err != nil {
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
				result.Result_of_Jason += 1
			} else if candidate == "Michael" {
				result.Result_of_Michael += 1
			} else {
				fmt.Println("We recorded some wrong value")
			}
		}
	}

	buf := bytes.NewBuffer(nil)
	enc := gob.NewEncoder(buf)
	err = enc.Encode(result)
	if err != nil {
		return shim.Error(err.Error())
	}
	return shim.Success(buf.Bytes())
}

// func (t *votingChaincode) verifysign(stub shim.ChaincodeStubInterface, args []string) pb.Response {
// 	var voterRingSign RingSign

// 	buf := bytes.NewBuffer([]byte(args[0]))
// 	gob.Register(secp256k1.S256())
// 	dec := gob.NewDecoder(buf)
// 	err := dec.Decode(&voterRingSign)
// 	if err != nil {
// 		return shim.Error(err.Error())
// 	}
// 	if Verify(&voterRingSign) == false {
// 		return shim.Success([]byte("false"))
// 	} else {
// 		return shim.Success([]byte("true"))
// 	}
// }

// func (t *votingChaincode) nizksign(stub shim.ChaincodeStubInterface) pb.Response {
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
// 	return shim.Success(nil)
// }
// Deletes an entity from state
// func (t *votingChaincode) delete(stub shim.ChaincodeStubInterface, args []string) pb.Response {
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

// query callback representing the query of a chaincode

// func S256() *BitCurve {
// 	return new(BitCurve)
// }

func in(target string, str_array []string) bool {
	for _, element := range str_array {
		if target == element {
			return true
		}
	}
	return false
}

func main() {
	err := shim.Start(new(votingChaincode))
	if err != nil {
		fmt.Printf("Error starting Simple chaincode: %s", err)
	}
}

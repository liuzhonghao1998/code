package controllers

import (
	"bytes"
	"crypto/ecdsa"
	"encoding/gob"
	"fmt"
	"net/http"
	"strconv"
	"time"

	"database/sql"

	"github.com/ethereum/go-ethereum/crypto/secp256k1"
	_ "github.com/mattn/go-sqlite3"
	"github.com/noot/ring-go"
	"golang.org/x/crypto/sha3"
)

func (app *Application) RequestHandler(rw http.ResponseWriter, r *http.Request, VoterRingSig *ring.RingSign, VoterPrivateKey *ecdsa.PrivateKey) {

	var args []string
	//var msg string
	var err error
	if r.FormValue("submitted") == "true" {
		//var msg string
		candidateVal := r.FormValue("Candidate")
		fmt.Println(candidateVal)
		args = append(args, candidateVal)
		geoVal := r.FormValue("Geo_Hash")
		fmt.Println(geoVal)
		args = append(args, geoVal)
		args = append(args, "127.0.0.1")

		msg := args[0] + "_" + args[1]
		msgHash := sha3.Sum256([]byte(msg))

		fmt.Println(VoterPrivateKey)

		VoterRingSig, err = ring.Sign(msgHash, VoterRingSig.Ring, VoterPrivateKey, 1)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to sig the vote", 500)
		}

		// ring := bytes.NewBuffer(nil)
		// enc := gob.NewEncoder(ring)
		// gob.Register(elliptic.P256())
		// err = enc.Encode(VoterRingSig)
		// if err != nil {
		// 	fmt.Println(err)
		// 	http.Error(rw, "Unable to encode the signature", 500)
		// }

		// pri := bytes.NewBuffer(nil)
		// enc = gob.NewEncoder(pri)
		// gob.Register(elliptic.P256())
		// err = enc.Encode(VoterPrivateKey)
		// if err != nil {
		// 	fmt.Println(err)
		// 	http.Error(rw, "Unable to encode the private key", 500)
		// }

		sign := bytes.NewBuffer(nil)
		enc := gob.NewEncoder(sign)
		// gob.Register(elliptic.P256())
		//gob.Register(secp256k1.BitCurve{})
		gob.Register(secp256k1.S256())
		err = enc.Encode(VoterRingSig)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to encode the signature", 500)
		}

		//args = append(args, "Ring Signature For Real")
		fmt.Print("Have got the request data:")
		fmt.Println(args)

		// [Jason, Haidian, 127.0.0.1, sig, prk]
		//txid, signed, err := app.PrivateFabric.InvokeCandidateinPrivate(args, sig.Bytes(), prk.Bytes())
		//txid, sign, err := app.PrivateFabric.InvokeCandidateinPrivate(args, ring.Bytes(), pri.Bytes())
		txid, err := app.PrivateFabric.InvokeCandidateinPrivate(args, sign.Bytes())
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to invoke vote in the Private blockchain", 500)
		}
		Data.TransactionIdinPrivate = txid
		Data.PrivateHeight, err = app.PrivateFabric.QueryBlockHeightByTxID(txid)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to query vote's blockheight in the Private blockchain", 500)
		}

		args = []string{}
		args = append(args, Data.TransactionIdinPrivate)
		args = append(args, candidateVal)
		args = append(args, geoVal)
		//args = append(args, "abcdefg")
		votetime, err := app.PrivateFabric.QueryCreateTimeByTxID(txid)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to query create time of Tx by txid", 500)
		}
		Data.PrivateTimestamp = votetime

		err = databaseStorage(args, sign.Bytes(), votetime)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to write publicdata into the off-chain database", 500)
		}

		//test part
		// rand.Seed(time.Now().UnixNano())
		// randomnum := rand.Intn(2) //[0,2)
		// if randomnum == 0 {
		// 	time.Sleep(time.Second * 30)
		// }

		txid, err = app.PublicFabric.InvokeCandidateinPublic(args, sign.Bytes())
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to invoke vote in the Public blockchain", 500)
		}

		votetime, err = app.PublicFabric.QueryCreateTimeByTxID(txid)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to query create time of Tx by txid", 500)
		}

		Data.TransactionIdinPublic = txid
		Data.PublicHeight, err = app.PublicFabric.QueryBlockHeightByTxID(txid)
		if err != nil {
			fmt.Println(err)
			http.Error(rw, "Unable to query vote's blockheight in the Public blockchain", 500)
		}
		Data.PublicTimestamp = votetime

		if verifyDataConsistency(Data.PrivateHeight, Data.PublicHeight, Data.PrivateTimestamp, votetime) == false {
			http.Error(rw, "This item does not hold the data consistency between the Private chain and Public chain", 500)
		}

		privateHeight := strconv.FormatUint(Data.PrivateHeight, 10)
		publicheight := strconv.FormatUint(Data.PublicHeight, 10)
		err = cloudDatabaseStorage(Data.TransactionIdinPrivate, privateHeight, Data.PrivateTimestamp, Data.TransactionIdinPublic, publicheight, Data.PublicTimestamp)
		if err != nil {
			fmt.Println(err)
			// http.Error(rw, "Unable to write receipt in cloud database", 500)
		}
		Data.Success = true
		Data.Response = true
		Data.ShowCandidate = false
	}
	renderTemplate(rw, r, "request.html", Data)
}

func (app *Application) TestHandler(rw http.ResponseWriter, r *http.Request, VoterRingSig *ring.RingSign, VoterPrivateKey *ecdsa.PrivateKey) {
	data := &struct {
		TransactionIdinPrivate string
		PrivateHeight          uint64
		PrivateTimestamp       time.Time
		TransactionIdinPublic  string
		PublicHeight           uint64
		PublicTimestamp        time.Time
		Success                bool
		Response               bool
	}{
		TransactionIdinPrivate: "",
		PrivateHeight:          0,
		TransactionIdinPublic:  "",
		PublicHeight:           0,
		Success:                false,
		Response:               false,
	}

	var args []string
	//var msg string
	var err error

	//var msg string
	candidateVal := "Jason"
	fmt.Println(candidateVal)
	args = append(args, candidateVal)
	geoVal := "Haidian"
	fmt.Println(geoVal)
	args = append(args, geoVal)
	args = append(args, "127.0.0.1")

	msg := args[0] + "_" + args[1]
	msgHash := sha3.Sum256([]byte(msg))

	fmt.Println(VoterPrivateKey)

	VoterRingSig, err = ring.Sign(msgHash, VoterRingSig.Ring, VoterPrivateKey, 1)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to sig the vote", 500)
	}

	sign := bytes.NewBuffer(nil)
	enc := gob.NewEncoder(sign)
	// gob.Register(elliptic.P256())
	//gob.Register(secp256k1.BitCurve{})
	gob.Register(secp256k1.S256())
	err = enc.Encode(VoterRingSig)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to encode the signature", 500)
	}

	//args = append(args, "Ring Signature For Real")
	fmt.Print("Have got the request data:")
	fmt.Println(args)

	// [Jason, Haidian, 127.0.0.1, sig, prk]
	//txid, signed, err := app.PrivateFabric.InvokeCandidateinPrivate(args, sig.Bytes(), prk.Bytes())
	//txid, sign, err := app.PrivateFabric.InvokeCandidateinPrivate(args, ring.Bytes(), pri.Bytes())
	txid, err := app.PrivateFabric.InvokeCandidateinPrivate(args, sign.Bytes())
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to invoke vote in the Private blockchain", 500)
	}
	data.TransactionIdinPrivate = txid
	data.PrivateHeight, err = app.PrivateFabric.QueryBlockHeightByTxID(txid)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to query vote's blockheight in the Private blockchain", 500)
	}

	args = []string{}
	args = append(args, data.TransactionIdinPrivate)
	args = append(args, candidateVal)
	args = append(args, geoVal)
	//args = append(args, "abcdefg")
	votetime, err := app.PrivateFabric.QueryCreateTimeByTxID(txid)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to query create time of Tx by txid", 500)
	}
	data.PrivateTimestamp = votetime

	//去除off-chain数据库功能
	err = databaseStorage(args, sign.Bytes(), votetime)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to write publicdata into the off-chain database", 500)
	}

	//test part
	// rand.Seed(time.Now().UnixNano())
	// randomnum := rand.Intn(2) //[0,2)
	// if randomnum == 0 {
	// 	time.Sleep(time.Second * 30)
	// }

	txid, err = app.PublicFabric.InvokeCandidateinPublic(args, sign.Bytes())
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to invoke vote in the Public blockchain", 500)
	}

	votetime, err = app.PublicFabric.QueryCreateTimeByTxID(txid)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to query create time of Tx by txid", 500)
	}

	data.TransactionIdinPublic = txid
	data.PublicHeight, err = app.PublicFabric.QueryBlockHeightByTxID(txid)
	if err != nil {
		fmt.Println(err)
		http.Error(rw, "Unable to query vote's blockheight in the Public blockchain", 500)
	}
	data.PublicTimestamp = votetime

	//去除验证data consistency步骤
	if verifyDataConsistency(data.PrivateHeight, data.PublicHeight, data.PrivateTimestamp, votetime) == false {
		http.Error(rw, "This item does not hold the data consistency between the Private chain and Public chain", 500)
	}

	data.Success = true
	data.Response = true

	renderTemplate(rw, r, "test.html", data)
}

func databaseStorage(args []string, sign []byte, votetime time.Time) error { //数据库中的DATE可以直接和go的time.Time相互转换
	db, err := sql.Open("sqlite3", "/Users/liuzhonghao/go/src/Evoting-v1/db/evoting.db")
	if err != nil {
		return err
	}

	stmt, err := db.Prepare("INSERT INTO publicdata(txid, candidate, location, signature, time) values(?,?,?,?,?)")
	if err != nil {
		return err
	}

	var sig string
	sig = string(sign)
	res, err := stmt.Exec(args[0], args[1], args[2], sig, votetime)
	if err != nil {
		return err
	}

	id, err := res.LastInsertId()
	if err != nil {
		return err
	}
	fmt.Println("the off-chain data has stored in database and its id is", id)
	defer db.Close()
	// err = db.Close()
	// if err != nil {
	// 	return err
	// }

	return nil
}

func cloudDatabaseStorage(transactionIdinPrivate string, privateHeight string, privateTimestamp time.Time, transactionIdinPublic string, publicHeight string, publicTimestamp time.Time) error {
	db, err := sql.Open("mysql", "admin:nqtradenotification1234Secret@tcp(database-1.c6nb76zfkw27.us-east-2.rds.amazonaws.com:3306)/e_voting?charset=utf8&parseTime=true")
	if err != nil {
		return err
	}
	stmt, err := db.Prepare("UPDATE vote_table SET receipt_private_tran_id=?, receipt_private_block_height=?, receipt_private_create_time=?, receipt_public_tran_id=?, receipt_public_block_height=?, receipt_public_create_time=? WHERE vote_id=?")
	if err != nil {
		return err
	}
	res, err := stmt.Exec(transactionIdinPrivate, privateHeight, privateTimestamp, transactionIdinPublic, publicHeight, publicTimestamp, 1)
	id, err := res.LastInsertId()
	if err != nil {
		return err
	}
	fmt.Println("the receipt has stored in cloud database and its id is", id)
	return nil
}

func verifyDataConsistency(heightinprivate uint64, heightinpublic uint64, timeinprivate time.Time, timeinpublic time.Time) bool {
	// var PeerChannelUpdateTxNuminPrivate uint64
	// PeerChannelUpdateTxNuminPrivate = 2

	realelapsed := timeinpublic.Sub(timeinprivate)
	theoreticalelapsed := (heightinpublic - heightinprivate + 1) * 2 //块中记录的是每个交易的创建（created）时间。需要考虑极限情况，即私链在time=0时创建第一个交易并在time=30时在公链创建交易。
	fmt.Println("the create time in private blockchain is", timeinprivate)
	fmt.Println("the create time in public blockchain is", timeinpublic)
	fmt.Println("realelapsed is ", realelapsed.Seconds())
	fmt.Println("theoreticalelapsed is ", theoreticalelapsed)
	fmt.Println("heightinprivate is", heightinprivate)
	fmt.Println("heightinpublic is ", heightinpublic)
	if heightinprivate == heightinpublic {
		return true
	} else {
		if realelapsed.Seconds() <= float64(theoreticalelapsed) {
			return true
		} else {
			return false
		}
	}
}

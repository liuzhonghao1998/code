package controllers

import (
	"fmt"
	"net/http"
	"strconv"
)

var data = &struct {
	DeliveryTransactionId string
	CurrentHeight         string
	TxID                  string
	//TxNum                 string
	BlockNum         string
	Candidate        string
	HashedGeo        string
	LinkableRingSign string
	Start            bool
	Query            bool
	Success          bool
	Response         bool
	Sig              []byte
	Keyparams        []byte
}{
	DeliveryTransactionId: "",
	CurrentHeight:         "",
	TxID:                  "",
	//TxNum:                 "",
	BlockNum:         "3",
	Candidate:        "",
	HashedGeo:        "",
	LinkableRingSign: "",
	Start:            false,
	Query:            true,
	Success:          false,
	Response:         false,
}

//var votes = []blockchain.Vote{}

func (app *Application) DeliveryHandler(w http.ResponseWriter, r *http.Request) {
	//var args []string
	//var err error
	if r.FormValue("submitted") == "true" {
		messageType := r.FormValue("MessageType")

		if messageType == "start" {
			var err error
			println("Got start message.")
			data.BlockNum = "4"
			//请求第一次数据
			data.Start = true
			data.Query = true
			data.Success = false
			data.Response = false
			if err != nil {
				http.Error(w, err.Error(), 500)
				return
			}
			renderTemplate(w, r, "delivery.html", data)

		} else if messageType == "query" {
			println("Got query message.")
			num, err := strconv.ParseUint(data.BlockNum, 10, 64)
			if err != nil {
				http.Error(w, "Fail to change the string to uint64", 500)
				return
			}
			votes, err := app.PublicFabric.QueryVoteByBlockNum(num)
			if err != nil {
				http.Error(w, "Fail to query the vote data", 500)
				return
			}
			for index := 0; index < len(votes); index++ {
				fmt.Printf("vote=%+v\n", votes[index])
			}
			num++
			data.BlockNum = strconv.FormatUint(num, 10)
			renderTemplate(w, r, "delivery.html", data)
			// println("Got NIZk from PublicPeer")
			// data.Sig, data.Keyparams, err = app.PublicFabric.NizkGet()

			// if err != nil {
			// 	http.Error(w, err.Error(), 500)
			// 	return
			// }
			// println("Got sign form PublicPeer")

			// println("Got query message.")
			// num, err := strconv.ParseUint(data.BlockNum, 10, 64)
			// if err != nil {
			// 	http.Error(w, "Fail to change the string to uint64", 500)
			// 	return
			// }
			// vote, err := app.PublicFabric.QueryVoteByBlockNum(num)
			// if err != nil {
			// 	http.Error(w, "Fail to query the vote data", 500)
			// 	return
			// }

			// data.Query = false

			// currentheight, err := strconv.ParseUint(vote.CurrentHeight, 10, 64)
			// if err != nil {
			// 	http.Error(w, "Fail to change the height string to uint64", 500)
			// 	return
			// }
			// currentheight = currentheight - 3

			// data.CurrentHeight = strconv.FormatUint(currentheight, 10)
			// data.TxID = vote.TxID
			// data.BlockNum = vote.BlockNum
			// data.Candidate = vote.Candidate
			// data.HashedGeo = vote.HashedGeo
			// data.LinkableRingSign = vote.LinkableRingSignature
			// data.Start = true
			// data.Success = true
			// data.Response = false
			// renderTemplate(w, r, "delivery.html", data)

		} else if messageType == "delivery" {
			// println("Got deliver message.")
			// args = append(args, data.TxID)
			// args = append(args, data.BlockNum)
			// args = append(args, data.Candidate)
			// args = append(args, data.HashedGeo)
			// args = append(args, data.LinkableRingSign)

			// isValid := blockchain.NizkPriVerify(data.Sig, data.Keyparams)
			// if isValid == false {
			// 	http.Error(w, "NIZK is not passed in private side", 500)
			// 	return
			// }
			// println("PrivatePeer has check PublicPeer identity")

			// data.Sig, data.Keyparams, err = app.PrivateFabric.NizkGet()
			// if err != nil {
			// 	http.Error(w, err.Error(), 500)
			// 	return
			// }
			// println("Got sign from PrivatePeer")

			// txid, err := app.PrivateFabric.InvokeCandidate(args)
			// if err != nil {
			// 	http.Error(w, err.Error(), 500)
			// 	return
			// }
			// data.DeliveryTransactionId = txid
			// data.Success = true
			// data.Response = true
			// index, err := strconv.Atoi(data.TxNum)
			// if index == len(votes) {
			// 	num, err := strconv.ParseUint(data.BlockNum, 10, 64)
			// 	if err != nil {
			// 		http.Error(w, "Fail to change the string to uint64", 500)
			// 		return
			// 	}
			// 	num++
			// 	data.BlockNum = strconv.FormatUint(num, 10)
			// 	data.TxID = ""
			// 	data.Candidate = ""
			// 	data.HashedGeo = ""
			// 	data.LinkableRingSign = ""
			// 	data.Query = true
			// 	data.Success = false
			// 	data.Response = false

			// 	Reports.Showlist = votes
			// } else {
			// 	index++
			// 	data.TxID = votes[index-1].TxID
			// 	data.TxNum = strconv.Itoa(index)
			// 	data.BlockNum = votes[index-1].BlockNum
			// 	data.Candidate = votes[index-1].Candidate
			// 	data.HashedGeo = votes[index-1].HashedGeo
			// 	data.LinkableRingSign = votes[index-1].LinkableRingSignature
			// 	data.Start = true
			// 	data.Success = true
			// 	data.Response = true
			//}

			// isValid = blockchain.NizkPubVerify(data.Sig, data.Keyparams)
			// if isValid == false {
			// 	http.Error(w, "NIZK is not passed in private side", 500)
			// 	return
			// }
			// println("PublicPeer has check PrivatePeer identity")

			// num, err := strconv.ParseUint(data.BlockNum, 10, 64)
			// if err != nil {
			// 	http.Error(w, err.Error(), 500)
			// 	return
			// }
			// num++
			// data.BlockNum = strconv.FormatUint(num, 10)
			// data.TxID = ""
			// data.Candidate = ""
			// data.HashedGeo = ""
			// data.LinkableRingSign = ""
			// data.Query = true
			// data.Success = false
			renderTemplate(w, r, "delivery.html", data)
		}
	} else {
		renderTemplate(w, r, "delivery.html", data)
	}
}

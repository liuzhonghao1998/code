package blockchain

import (
	"Evoting-v1/Evoting-sdk-go/voting-sdk-1/ringzhl"
	"bytes"
	"crypto/elliptic"
	"encoding/gob"
	"fmt"
	"math/big"
	"strconv"
	"time"

	"github.com/hyperledger/fabric-protos-go/common"
	"github.com/hyperledger/fabric-sdk-go/Evoting"
	"github.com/hyperledger/fabric-sdk-go/pkg/common/providers/fab"
	"github.com/pkg/errors"
)

type Vote struct {
	CurrentHeight         string
	TxID                  string
	BlockNum              string
	Candidate             string
	HashedGeo             string
	LinkableRingSignature big.Int
}

func (setup *FabricSetup) QueryVoteByBlockNum(num uint64) ([]Vote, error) {

	// Prepare arguments
	// var args []string
	// args = append(args, "query")
	// args = append(args, "Candidate")

	// response, err := setup.client.Query(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1])}})
	// if err != nil {
	// 	return "", fmt.Errorf("failed to query: %v", err)
	// }

	// return string(response.Payload), nil
	var err error
	var block *common.Block
	var sign ringzhl.RingSign
	vote := Vote{
		CurrentHeight: "",
		TxID:          "",
		BlockNum:      "",
		Candidate:     "",
		HashedGeo:     "",
	}
	// Add parameters for the initialization
	// clientContext := votingSetup.sdk.ChannelContext(votingSetup.ChannelID, fabsdk.WithUser(votingSetup.UserName))
	// votingSetup.ledgerClient, err = ledger.New(clientContext)
	// if err != nil {
	// 	return nil, errors.WithMessage(err, "failed to create new channel client")
	// }
	// fmt.Println("Channel client created")

	blockchaininforesponse, err := setup.ledgerClient.QueryInfo()
	if err != nil {
		return nil, fmt.Errorf("failed to query vote: %v", err)
	}
	blockchaininfo := blockchaininforesponse.BCI
	height := blockchaininfo.Height
	vote.CurrentHeight = strconv.FormatUint(height, 10)

	if num > height {
		return nil, errors.Errorf("the query block num is larger than the newest block num")
	}

	block, err = setup.ledgerClient.QueryBlock(num)

	if err != nil {
		return nil, errors.WithMessage(err, "failed to query block")
	}

	// Close SDK
	// defer votingSetup.CloseSDK()

	votes := []Vote{}

	for index := 0; index < len(block.Data.Data); index++ {
		transactioninfo, err := Evoting.QueryData(block, index)
		if err != nil {
			return nil, fmt.Errorf("failed to query vote: %v", err)
		}
		//fmt.Printf("%+v\n", transactioninfo)
		vote.TxID = transactioninfo.Args[3]
		vote.BlockNum = strconv.FormatUint(num, 10)
		vote.Candidate = transactioninfo.Args[5]
		vote.HashedGeo = transactioninfo.Args[7]

		buf := bytes.NewBuffer([]byte(transactioninfo.Args[9]))
		gob.Register(elliptic.P256())
		dec := gob.NewDecoder(buf)
		err = dec.Decode(&sign)
		if err != nil {
			return votes, err
		}
		vote.LinkableRingSignature = sign.C

		votes = append(votes, vote)
	}
	// transactioninfo, err := Evoting.QueryData(block, 0)
	// if err != nil {
	// 	return nil, fmt.Errorf("failed to query vote: %v", err)
	// }
	// //fmt.Printf("%+v\n", transactioninfo)
	// vote.TxID = transactioninfo.TxID
	// vote.BlockNum = strconv.FormatUint(num, 10)
	// vote.Candidate = transactioninfo.Args[3]
	// vote.HashedGeo = transactioninfo.Args[5]
	// vote.LinkableRingSignature = transactioninfo.Args[7]

	// return vote, nil
	return votes, nil
}

func (setup *FabricSetup) QueryVoteByTxID(txid string) (Vote, error) {
	vote := Vote{
		CurrentHeight: "",
		TxID:          "",
		BlockNum:      "",
		Candidate:     "",
		HashedGeo:     "",
	}
	var sign ringzhl.RingSign

	processedTransaction, err := setup.ledgerClient.QueryTransaction(fab.TransactionID(txid))
	if err != nil {
		return vote, err
	}

	if processedTransaction != nil {
		fmt.Println("Retrieved transaction")
	}

	envelop := processedTransaction.GetTransactionEnvelope()

	payload := envelop.GetPayload()

	data, err := Evoting.UnmarshalTransaction(payload)
	if err != nil {
		return vote, err
	}

	buf := bytes.NewBuffer([]byte(data.Args[9]))
	gob.Register(elliptic.P256())
	dec := gob.NewDecoder(buf)
	err = dec.Decode(&sign)
	if err != nil {
		return vote, err
	}
	fmt.Println(sign)

	vote.TxID = data.Args[3]
	vote.Candidate = data.Args[5]
	vote.HashedGeo = data.Args[7]
	vote.LinkableRingSignature = sign.C

	// queryvote := struct {
	// 	TxID           string
	// 	Candidate      string
	// 	Hashed_Geohash string
	// 	Ring_Signature string
	// }{}

	fmt.Println("The vote we have query is")
	fmt.Printf("%v\n", vote)
	//fmt.Println(string(payload.GetData()))

	return vote, nil
}

func (setup *FabricSetup) QueryBlockHeightByTxID(txid string) (uint64, error) {
	block, err := setup.ledgerClient.QueryBlockByTxID(fab.TransactionID(txid))
	if err != nil {
		return 0, err
	}
	return block.Header.Number, nil
}

func (setup *FabricSetup) QueryCreateTimeByTxID(txid string) (time.Time, error) {
	processedTransaction, err := setup.ledgerClient.QueryTransaction(fab.TransactionID(txid))
	if err != nil {
		return time.Now(), err
	}

	if processedTransaction != nil {
		fmt.Println("Retrieved transaction")
	}

	envelop := processedTransaction.GetTransactionEnvelope()

	payload := envelop.GetPayload()

	data, err := Evoting.UnmarshalTransaction(payload)
	if err != nil {
		return time.Now(), err
	}

	return data.CreateTime, nil
}

func (setup *FabricSetup) QueryFinalResult() (struct {
	Candidate_1 string
	Amount_1    int
	Candidate_2 string
	Amount_2    int
}, error) {

	result := struct {
		Candidate_1 string
		Amount_1    int
		Candidate_2 string
		Amount_2    int
	}{"Jason", 0, "Michael", 0}

	blockchaininforesponse, err := setup.ledgerClient.QueryInfo()
	if err != nil {
		return result, fmt.Errorf("failed to query vote: %v", err)
	}
	blockchaininfo := blockchaininforesponse.BCI
	finalheight := blockchaininfo.Height
	fmt.Println("the final height is ", finalheight) //当前区块链的高度是最后一个有数据的区块高度+1，+1是指当前为空的区块高度，查询的时候是没有办法查到这个区块的数据的。

	if finalheight <= 2 {
		return result, fmt.Errorf("the final height is no larger than 2.")
	} else {
		var height uint64
		for height = 3; height < finalheight; height++ {
			fmt.Println("current block height is ", height)
			block, err := setup.ledgerClient.QueryBlock(height)
			if err != nil {
				return result, errors.WithMessage(err, "failed to query block")
			}

			for index := 0; index < len(block.Data.Data); index++ {
				transactioninfo, err := Evoting.QueryData(block, index)
				if err != nil {
					return result, fmt.Errorf("failed to query vote: %v", err)
				}
				//fmt.Printf("%+v\n", transactioninfo)
				if transactioninfo.Args[3] == "Jason" {
					result.Amount_1 += 1
				} else if transactioninfo.Args[3] == "Michael" {
					result.Amount_2 += 1
				}
			}
		}
	}
	return result, nil
}
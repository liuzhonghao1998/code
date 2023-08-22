package blockchain

import (
	"fmt"
	"strconv"

	"github.com/hyperledger/fabric-protos-go/common"
	"github.com/hyperledger/fabric-sdk-go/Evoting"
	"github.com/pkg/errors"
)

type Vote struct {
	CurrentHeight         string
	TxID                  string
	BlockNum              string
	Candidate             string
	HashedGeo             string
	LinkableRingSignature string
}

func (setup *FabricSetup) QueryVoteByBlockNum(num uint64) (*Vote, error) {

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
	// Add parameters for the initialization
	// clientContext := votingSetup.sdk.ChannelContext(votingSetup.ChannelID, fabsdk.WithUser(votingSetup.UserName))
	// votingSetup.ledgerClient, err = ledger.New(clientContext)
	// if err != nil {
	// 	return nil, errors.WithMessage(err, "failed to create new channel client")
	// }
	// fmt.Println("Channel client created")

	block, err = setup.ledgerClient.QueryBlock(num)

	if err != nil {
		return nil, errors.WithMessage(err, "failed to query block")
	}
	fmt.Println("Chaincode Installation & Instantiation Successful")

	// Close SDK
	// defer votingSetup.CloseSDK()

	vote := &Vote{
		CurrentHeight:         "",
		TxID:                  "",
		BlockNum:              "",
		Candidate:             "",
		HashedGeo:             "",
		LinkableRingSignature: "",
	}

	//votes := []Vote{}

	// for index := 0; index < len(block.Data.Data); index++ {
	// 	transactioninfo, err := Evoting.QueryVote(block, 0)
	// 	if err != nil {
	// 		return nil, fmt.Errorf("failed to query vote: %v", err)
	// 	}
	// 	//fmt.Printf("%+v\n", transactioninfo)
	// 	vote.TxID = transactioninfo.TxID
	// 	vote.BlockNum = strconv.FormatUint(num, 10)
	// 	vote.Candidate = transactioninfo.Args[3]
	// 	vote.HashedGeo = transactioninfo.Args[5]
	// 	vote.LinkableRingSignature = transactioninfo.Args[7]

	// 	blockchaininforesponse, err := votingSetup.ledgerClient.QueryInfo()
	// 	if err != nil {
	// 		return nil, fmt.Errorf("failed to query vote: %v", err)
	// 	}
	// 	blockchaininfo := blockchaininforesponse.BCI
	// 	height := blockchaininfo.Height
	// 	vote.CurrentHeight = strconv.FormatUint(height, 10)

	// 	votes = append(votes, vote)
	// }
	transactioninfo, err := Evoting.QueryData(block, 0)
	if err != nil {
		return nil, fmt.Errorf("failed to query vote: %v", err)
	}
	//fmt.Printf("%+v\n", transactioninfo)
	vote.TxID = transactioninfo.TxID
	vote.BlockNum = strconv.FormatUint(num, 10)
	vote.Candidate = transactioninfo.Args[3]
	vote.HashedGeo = transactioninfo.Args[5]
	vote.LinkableRingSignature = transactioninfo.Args[7]

	blockchaininforesponse, err := setup.ledgerClient.QueryInfo()
	if err != nil {
		return nil, fmt.Errorf("failed to query vote: %v", err)
	}
	blockchaininfo := blockchaininforesponse.BCI
	height := blockchaininfo.Height
	vote.CurrentHeight = strconv.FormatUint(height, 10)

	return vote, nil
}

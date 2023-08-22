package main

import (
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/blockchain"
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/web"
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/web/controllers"
	"fmt"
)

func main() {
	// Definition of the Fabric SDK properties

	publicSetup := blockchain.FabricSetup{
		// Network parameters
		OrdererID: "orderer.evoting.com",

		// Channel parameters
		ChannelID:     "publicchannel",
		ChannelConfig: "/Users/liuzhonghao/go/src/Evoting-v1/channel-artifacts/pubchannel.tx",

		// Chaincode parameters
		ChainCodeID: "publicityChaincode",
		// ChaincodeGoPath: os.Getenv("GOPATH"),
		// ChaincodePath:   "",
		OrgAdmin: "Admin",
		// OrgName:    "PublicMSP",
		ConfigFile: "/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/config.yaml",

		// User parameters
		UserName: "User1",
	}

	fmt.Printf("test start\n")

	// Query the chaincode
	// response, err := privateSetup.QueryVote(1)
	// if err != nil {
	// 	fmt.Printf("Unable to query vote on the chaincode: %v\n", err)
	// 	return
	// } else {
	// 	fmt.Printf("Response from the query hello: %s\n", response)
	// 	return
	// }

	//在hyperledger fabric中所有的区块链的索引从1开始而且第一个区块中存放的都是系统配置相关的信息，
	//在本项目中所谓的第一个区块其实是第二个区块存放候选人信息，真正的vote从第三个区块开始
	// vote, err := privateSetup.QueryVoteByBlockNum(5)
	// if err != nil {
	// 	fmt.Errorf("failed to query vote by block num: %v", err)
	// }
	// fmt.Printf("%+v\n", vote)

	// Invoke the chaincode
	// value := []string{"Jason", "Chaoyang", "abcdefg"}
	// txID, err := privateSetup.InvokeJason(value)
	// if err != nil {
	// 	fmt.Printf("Unable to invoke Jason on the chaincode: %v\n", err)
	// } else {
	// 	fmt.Printf("Successfully invoke Jason, transaction ID: %s\n", txID)
	// }
	err := publicSetup.Initialize()
	if err != nil {
		fmt.Printf("Unable to initialize the Fabric SDK: %v\n", err)
		return
	}

	// Close SDK
	defer publicSetup.CloseSDK()

	// err = publicSetup.CreateChannelClient()
	// if err != nil {
	// 	fmt.Printf("Unable to install and instantiate the chaincode: %v\n", err)
	// 	return
	// }

	err = publicSetup.CreateLedgerClient()
	if err != nil {
		fmt.Printf("Unable to create ledger client: %v\n", err)
		return
	}

	err = publicSetup.CreateChannelClient()
	if err != nil {
		fmt.Printf("Unable to create public channelclient: %v\n", err)
		return
	}
	//Launch the web application listening
	app := &controllers.Application{
		PublicFabric: &publicSetup,
	}
	web.Serve(app)
}

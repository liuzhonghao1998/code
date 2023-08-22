package blockchain

import (
	"fmt"

	"github.com/hyperledger/fabric-sdk-go/pkg/client/channel"
)

// InvokeHello
func (setup *FabricSetup) InvokeCandidateinPrivate(value []string, sign []byte) (string, error) {
	// Prepare arguments
	var args []string
	args = append(args, "invokevote")
	args = append(args, "Candidate")
	args = append(args, value[0])
	args = append(args, "Hashed_Geohash")
	args = append(args, value[1])
	args = append(args, "Address")
	args = append(args, value[2])
	args = append(args, "Ring_Signature")

	//eventID := "eventInvoke"

	// Add data that will be visible in the proposal, like a description of the invoke request
	transientDataMap := make(map[string][]byte)
	transientDataMap["result"] = []byte("Transient data in Jason invoke")

	// reg, notifier, err := setup.event.RegisterChaincodeEvent(setup.ChainCodeID, eventID)
	// if err != nil {
	// 	return "", err
	// }
	// defer setup.event.Unregister(reg)

	// Create a request (proposal) and send it
	// sizeofbytes := len([]byte(args[0]))
	// for i := 1; i <= 7; i++ {
	// 	sizeofbytes += len([]byte(args[i]))
	// }
	// sizeofbytes += len(sign)
	// fmt.Println("args和sign占的字节数为:", sizeofbytes)
	response, err := setup.channelClient.Execute(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1]), []byte(args[2]), []byte(args[3]), []byte(args[4]), []byte(args[5]), []byte(args[6]), []byte(args[7]), sign}, TransientMap: transientDataMap})
	if err != nil {
		return "", fmt.Errorf("failed to move funds: %v", err)
	}

	// Wait for the result of the submission
	// select {
	// case ccEvent := <-notifier:
	// 	fmt.Printf("Received CC event: %v\n", ccEvent)
	// case <-time.After(time.Second * 20):
	// 	return "", fmt.Errorf("did NOT receive CC event for eventId(%s)", eventID)
	// }

	return string(response.TransactionID), nil
}

func (setup *FabricSetup) InvokeCandidateinPublic(value []string, sign []byte) (string, error) {
	// Prepare arguments
	var args []string
	args = append(args, "invokevote")
	args = append(args, "TxHash")
	args = append(args, value[0])
	args = append(args, "Candidate")
	args = append(args, value[1])
	args = append(args, "Hashed_Geohash")
	args = append(args, value[2])
	args = append(args, "Ring_Signature")
	//args = append(args, value[3])

	//eventID := "eventInvoke"

	// Add data that will be visible in the proposal, like a description of the invoke request
	transientDataMap := make(map[string][]byte)
	transientDataMap["result"] = []byte("Transient data in Jason invoke")

	// reg, notifier, err := setup.event.RegisterChaincodeEvent(setup.ChainCodeID, eventID)
	// if err != nil {
	// 	return "", err
	// }
	// defer setup.event.Unregister(reg)

	// Create a request (proposal) and send it
	response, err := setup.channelClient.Execute(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1]), []byte(args[2]), []byte(args[3]), []byte(args[4]), []byte(args[5]), []byte(args[6]), []byte(args[7]), sign}, TransientMap: transientDataMap})
	if err != nil {
		return "", fmt.Errorf("failed to move funds: %v", err)
	}

	// Wait for the result of the submission
	// select {
	// case ccEvent := <-notifier:
	// 	fmt.Printf("Received CC event: %v\n", ccEvent)
	// case <-time.After(time.Second * 20):
	// 	return "", fmt.Errorf("did NOT receive CC event for eventId(%s)", eventID)
	// }

	return string(response.TransactionID), nil
}

func (setup *FabricSetup) DeleteTransactioninPrivate(value []string, sign []byte) (string, error) {
	var args []string
	args = append(args, "delete")
	args = append(args, "Candidate")
	args = append(args, value[0])
	args = append(args, "Hashed_Geohash")
	args = append(args, value[1])
	args = append(args, "Address")
	args = append(args, value[2])
	args = append(args, "Ring_Signature")

	transientDataMap := make(map[string][]byte)
	transientDataMap["result"] = []byte("Transient data in Jason invoke")

	response, err := setup.channelClient.Execute(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1]), []byte(args[2]), []byte(args[3]), []byte(args[4]), []byte(args[5]), []byte(args[6]), []byte(args[7]), sign}, TransientMap: transientDataMap})
	if err != nil {
		return "", fmt.Errorf("failed to move funds: %v", err)
	}

	return string(response.TransactionID), nil
}

package blockchain

import (
	"fmt"
	"time"

	"github.com/hyperledger/fabric-sdk-go/pkg/client/channel"
)

// InvokeHello
func (setup *FabricSetup) InvokeCandidate(value []string) (string, error) {

	// Prepare arguments
	var args []string
	args = append(args, "invokevote")
	args = append(args, "TxID")
	args = append(args, value[0])
	args = append(args, "BlockNum")
	args = append(args, value[1])
	args = append(args, "Candidate")
	args = append(args, value[2])
	args = append(args, "HashedGeo")
	args = append(args, value[3])
	args = append(args, "LinkableRingSign")
	args = append(args, value[4])

	eventID := "eventInvoke"

	// Add data that will be visible in the proposal, like a description of the invoke request
	transientDataMap := make(map[string][]byte)
	transientDataMap["result"] = []byte("Collect vote in smartphone or PC")

	reg, notifier, err := setup.event.RegisterChaincodeEvent(setup.ChainCodeID, eventID)
	if err != nil {
		return "", err
	}
	defer setup.event.Unregister(reg)

	fmt.Println("Start to execute the request:")
	//fmt.Println(args)
	// Create a request (proposal) and send it
	response, err := setup.channelClient.Execute(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1]), []byte(args[2]), []byte(args[3]), []byte(args[4]), []byte(args[5]), []byte(args[6]), []byte(args[7]), []byte(args[8]), []byte(args[9]), []byte(args[10])}, TransientMap: transientDataMap})
	if err != nil {
		return "", fmt.Errorf("failed to move funds: %v", err)
	}

	// Wait for the result of the submission
	select {
	case ccEvent := <-notifier:
		fmt.Printf("Received CC event: %v\n", ccEvent)
	case <-time.After(time.Second * 20):
		return "", fmt.Errorf("did NOT receive CC event for eventId(%s)", eventID)
	}

	return string(response.TransactionID), nil
}

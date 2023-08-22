package blockchain

import (
	"fmt"

	"github.com/hyperledger/fabric-sdk-go/pkg/client/channel"
)

func (setup *FabricSetup) QueryCandidate() (string, error) {

	//Prepare arguments
	var args []string
	args = append(args, "query")
	args = append(args, "Candidate_1")

	response, err := setup.channelClient.Query(channel.Request{ChaincodeID: setup.ChainCodeID, Fcn: "invoke", Args: [][]byte{[]byte(args[0]), []byte(args[1])}})
	if err != nil {
		return "", fmt.Errorf("failed to query: %v", err)
	}
	return string(response.Payload), nil
}

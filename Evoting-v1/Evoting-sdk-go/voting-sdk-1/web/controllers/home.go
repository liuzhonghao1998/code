package controllers

import (
	"net/http"
	"time"

	"github.com/noot/ring-go"
)

var Data = &struct {
	TransactionIdinPrivate string
	PrivateHeight          uint64
	PrivateTimestamp       time.Time
	TransactionIdinPublic  string
	PublicHeight           uint64
	PublicTimestamp        time.Time
	Success                bool
	Response               bool
	//Check                  bool
	ShowCandidate bool
}{
	TransactionIdinPrivate: "",
	PrivateHeight:          0,
	TransactionIdinPublic:  "",
	PublicHeight:           0,
	Success:                false,
	Response:               false,
	//Check:                  false,
	ShowCandidate: true,
}

func (app *Application) HomeHandler(rw http.ResponseWriter, r *http.Request, VoterRingSig *ring.RingSign) {
	// candidateVal, err := app.Fabric.QueryCandidate()
	// if err != nil {
	// 	http.Error(w, "Unable to query the blockchain", 500)
	// }

	// data := &struct {
	// 	Candidate string
	// }{
	// 	Candidate: candidateVal,
	// }

	/* generate new private public keypair */
	Data.Success = false
	Data.Response = false
	Data.ShowCandidate = true
	renderTemplate(rw, r, "home.html", VoterRingSig)
}

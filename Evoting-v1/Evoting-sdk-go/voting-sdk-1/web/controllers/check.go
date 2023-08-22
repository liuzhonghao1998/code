package controllers

import (
	"net/http"
	"time"
)

func (app *Application) CheckHandler(rw http.ResponseWriter, r *http.Request, data *struct {
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
}) {
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
	// fmt.Println(Data.Check)
	// if r.FormValue("checked") == "true" {
	// 	Data.Check = true
	// 	renderTemplate(rw, r, "check.html", Data)
	// } else {
	// 	renderTemplate(rw, r, "check.html", Data)
	// }
	renderTemplate(rw, r, "check.html", Data)
}

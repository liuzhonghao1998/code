package controllers

import (
	"net/http"
)

func (app *Application) HomeHandler(w http.ResponseWriter, r *http.Request) {
	// candidateVal, err := app.Fabric.QueryCandidate()
	// if err != nil {
	// 	http.Error(w, "Unable to query the blockchain", 500)
	// }

	// data := &struct {
	// 	Candidate string
	// }{
	// 	Candidate: candidateVal,
	// }
	data := &struct {
		Candidate_1 string
		Candidate_2 string
	}{
		Candidate_1: "Jason",
		Candidate_2: "Michael",
	}
	renderTemplate(w, r, "home.html", data)
}

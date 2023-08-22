package controllers

import (
	"fmt"
	"net/http"
)

func (app *Application) RequestHandler(w http.ResponseWriter, r *http.Request) {
	data := &struct {
		TransactionIdinPrivate string
		TransactionIdinPublic  string
		Success                bool
		Response               bool
	}{
		TransactionIdinPrivate: "",
		TransactionIdinPublic:  "",
		Success:                false,
		Response:               false,
	}

	var args []string
	if r.FormValue("submitted") == "true" {
		candidateVal := r.FormValue("Candidate")
		fmt.Println(candidateVal)
		args = append(args, candidateVal)
		geoVal := r.FormValue("Geo_Hash")
		fmt.Println(geoVal)
		args = append(args, geoVal)
		args = append(args, "abcdefg")
		args = append(args, "127.0.0.1")
		fmt.Print("Have got the request data:")
		fmt.Println(args)

		txid, err := app.PrivateFabric.InvokeCandidateinPrivate(args)
		if err != nil {
			fmt.Println(err)
			http.Error(w, "Unable to invoke vote in the Private blockchain", 500)
		}
		data.TransactionIdinPrivate = txid

		args = []string{}
		args = append(args, data.TransactionIdinPrivate)
		args = append(args, candidateVal)
		args = append(args, geoVal)
		args = append(args, "abcdefg")

		txid, err = app.PublicFabric.InvokeCandidateinPublic(args)
		if err != nil {
			fmt.Println(err)
			http.Error(w, "Unable to invoke vote in the Public blockchain", 500)
		}
		data.TransactionIdinPublic = txid

		data.Success = true
		data.Response = true
	}
	renderTemplate(w, r, "request.html", data)
}

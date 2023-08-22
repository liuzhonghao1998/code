package controllers

import (
	"Evoting-v1/Evoting-sdk-go/voting-sdk-4/blockchain"
	"fmt"
	"html/template"
	"net/http"
	"os"
	"path/filepath"
)

type Application struct {
	PrivateFabric *blockchain.FabricSetup
	PublicFabric  *blockchain.FabricSetup
}

func renderTemplate(w http.ResponseWriter, r *http.Request, templateName string, data interface{}) {
	lp := filepath.Join("/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/voting-sdk-4/web", "templates", "layout.html")
	tp := filepath.Join("/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/voting-sdk-4/web", "templates", templateName)

	// Return a 404 if the template doesn't exist
	info, err := os.Stat(tp)
	if err != nil {
		if os.IsNotExist(err) {
			http.NotFound(w, r)
			return
		}
	}

	// Return a 404 if the request is for a directory
	if info.IsDir() {
		http.NotFound(w, r)
		return
	}

	resultTemplate, err := template.ParseFiles(tp, lp)
	if err != nil {
		// Log the detailed error
		fmt.Println(err.Error())
		// Return a generic "Internal Server Error" message
		http.Error(w, http.StatusText(500), 500)
		return
	}
	if err := resultTemplate.ExecuteTemplate(w, "layout", data); err != nil {
		fmt.Println(err.Error())
		http.Error(w, http.StatusText(500), 500)
	}
}

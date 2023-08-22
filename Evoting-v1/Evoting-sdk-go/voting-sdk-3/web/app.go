package web

import (
	"Evoting-v1/Evoting-sdk-go/voting-sdk-3/web/controllers"
	"fmt"
	"net/http"
)

func Serve(app *controllers.Application) {
	fs := http.FileServer(http.Dir("/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/voting-sdk-3/web/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fs))

	http.HandleFunc("/home.html", app.HomeHandler)
	http.HandleFunc("/request.html", app.RequestHandler)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.Redirect(w, r, "/home.html", http.StatusTemporaryRedirect)
	})

	fmt.Println("Listening (http://localhost:3002/) ...")
	http.ListenAndServe(":3002", nil)
}

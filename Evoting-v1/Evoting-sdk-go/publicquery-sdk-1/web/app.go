package web

import (
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/web/controllers"
	"fmt"
	"net/http"
)

func Serve(app *controllers.Application) {
	fs := http.FileServer(http.Dir("/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/web/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fs))

	http.HandleFunc("/home.html", app.HomeHandler)
	http.HandleFunc("/delivery.html", app.DeliveryHandler)
	http.HandleFunc("/report.html", app.ReportingHandler)
	http.HandleFunc("/query.html", app.QueryingHandler)
	http.HandleFunc("/announce.html", app.AnnounceHandler)

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.Redirect(w, r, "/home.html", http.StatusTemporaryRedirect)
	})

	fmt.Println("Listening (http://localhost:4000/) ...")
	http.ListenAndServe(":4000", nil)
}

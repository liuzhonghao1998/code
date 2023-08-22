package controllers

import (
	"fmt"
	"net/http"
)

//GO语言中要提供给外面访问的方法或是结构体必须是首字母大写。这个结构体只有结构体名大写了，
//而里面的字段没有首字母大写，而GO语言在模板调用时应该认为是两个不同的过程，所以找不到值。

func (app *Application) AnnounceHandler(w http.ResponseWriter, r *http.Request) {
	//fmt.Println("The test public report is running!")
	// fmt.Println(data.Response)
	// fmt.Println(data.TxID)
	// fmt.Println(data.BlockNum)
	// fmt.Println(data.Candidate)
	// fmt.Println(data.HashedGeo)
	if r.FormValue("submitted") == "true" {
		Announcement, err := app.PublicFabric.QueryFinalResult()
		fmt.Println(Announcement)
		if err != nil {
			fmt.Println("The error we met in announce function is")
			fmt.Print(err)
			http.Error(w, "Unable to generate the final result.", 500)
		}
		renderTemplate(w, r, "announce.html", Announcement)
	} else {
		renderTemplate(w, r, "announce.html", nil)
	}
}

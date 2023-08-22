package controllers

import (
	"fmt"
	"net/http"
)

//GO语言中要提供给外面访问的方法或是结构体必须是首字母大写。这个结构体只有结构体名大写了，
//而里面的字段没有首字母大写，而GO语言在模板调用时应该认为是两个不同的过程，所以找不到值。

func (app *Application) QueryingHandler(w http.ResponseWriter, r *http.Request) {
	if r.FormValue("submitted") == "true" {
		txid := r.FormValue("TxID")
		vote, err := app.PublicFabric.QueryVoteByTxID(txid)
		if err != nil {
			http.Error(w, "Fail to query the vote by txid", 500)
			fmt.Println(err.Error())
			return
		}
		renderTemplate(w, r, "query.html", vote)
	} else {
		renderTemplate(w, r, "query.html", nil)
	}
}

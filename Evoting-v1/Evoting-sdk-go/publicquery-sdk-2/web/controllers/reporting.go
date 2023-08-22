package controllers

import (
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-2/blockchain"
	"net/http"
)

//GO语言中要提供给外面访问的方法或是结构体必须是首字母大写。这个结构体只有结构体名大写了，
//而里面的字段没有首字母大写，而GO语言在模板调用时应该认为是两个不同的过程，所以找不到值。

var Reports = struct {
	Showlist []blockchain.Vote
}{}

func (app *Application) ReportingHandler(w http.ResponseWriter, r *http.Request) {
	//fmt.Println("The test public report is running!")
	// fmt.Println(data.Response)
	// fmt.Println(data.TxID)
	// fmt.Println(data.BlockNum)
	// fmt.Println(data.Candidate)
	// fmt.Println(data.HashedGeo)
	renderTemplate(w, r, "reporting.html", Reports)
}

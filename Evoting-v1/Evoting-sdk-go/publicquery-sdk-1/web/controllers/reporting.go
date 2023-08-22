package controllers

import (
	"Evoting-v1/Evoting-sdk-go/publicquery-sdk-1/blockchain"
	"fmt"
	"net/http"
)

//GO语言中要提供给外面访问的方法或是结构体必须是首字母大写。这个结构体只有结构体名大写了，
//而里面的字段没有首字母大写，而GO语言在模板调用时应该认为是两个不同的过程，所以找不到值。

func (app *Application) ReportingHandler(w http.ResponseWriter, r *http.Request) {
	//fmt.Println("The test public report is running!")
	// fmt.Println(data.Response)
	// fmt.Println(data.TxID)
	// fmt.Println(data.BlockNum)
	// fmt.Println(data.Candidate)
	// fmt.Println(data.HashedGeo)
	var Reports = struct {
		Showlist []blockchain.Vote
	}{}
	var err error
	Reports.Showlist, err = app.PublicFabric.QueryVoteByBlockNum(5)
	if err != nil {
		http.Error(w, "Fail to query the vote by txid", 500)
		fmt.Println(err.Error())
		return
	}
	renderTemplate(w, r, "report.html", Reports)
}

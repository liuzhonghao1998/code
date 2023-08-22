package web

import (
	"Evoting-v1/Evoting-sdk-go/voting-sdk-1/web/controllers"
	"crypto/ecdsa"
	"fmt"
	"net/http"

	_ "github.com/go-sql-driver/mysql"

	"github.com/ethereum/go-ethereum/crypto"
	"github.com/noot/ring-go"
)

var VoterRingSig = new(ring.RingSign)
var VoterPrivateKey *ecdsa.PrivateKey

func Serve(app *controllers.Application) {
	// db, err := sql.Open("mysql", "admin:nqtradenotification1234Secret@tcp(database-1.c6nb76zfkw27.us-east-2.rds.amazonaws.com:3306)/e_voting?charset=utf8&parseTime=true")
	// if err != nil {
	// 	fmt.Println(err.Error())
	// }
	// var vote_id int
	// var vote, ring_signature_private_key, ring_signature_public_key, mac_address, district, priTxid, priBlockHeight, pubTxid, pubBlockHeight string
	// var pri_create_time, pub_create_time time.Time
	// err = db.QueryRow(`SELECT * From vote_table where vote_id = 1`).Scan(&vote_id, &vote, &ring_signature_private_key, &ring_signature_public_key, &mac_address, &district, &priTxid, &priBlockHeight, &pri_create_time, &pubTxid, &pubBlockHeight, &pub_create_time)
	// if err != nil {
	// 	fmt.Println(err.Error())
	// }
	// fmt.Println(vote_id, vote, ring_signature_private_key, ring_signature_public_key, mac_address, district)

	// defer db.Close()

	VoterPrivateKey, _ := crypto.HexToECDSA("358be44145ad16a1add8622786bef07e0b00391e072855a5667eb3c78b9d3803")
	//VoterPrivateKey, _ = ecdsa.GenerateKey(elliptic.P256(), rand.Reader)
	pubkey := VoterPrivateKey.PublicKey
	/* generate keyring */
	keyring, err := ring.GenNewKeyRing(3, VoterPrivateKey, 1)
	if err != nil {
		fmt.Println(err)
	}

	if keyring == nil || len(keyring) != 3 {
		fmt.Println("Could not generate keyring of size 3")
	}

	VoterRingSig.Size = 3
	VoterRingSig.Ring = keyring
	//VoterRingSig.I = ring.GenKeyImage(VoterPrivateKey)
	VoterRingSig.Curve = pubkey.Curve

	fs := http.FileServer(http.Dir("/Users/liuzhonghao/go/src/Evoting-v1/Evoting-sdk-go/voting-sdk-1/web/assets"))
	http.Handle("/assets/", http.StripPrefix("/assets/", fs))

	http.HandleFunc("/home.html", func(rw http.ResponseWriter, r *http.Request) { app.HomeHandler(rw, r, VoterRingSig) })
	http.HandleFunc("/request.html", func(rw http.ResponseWriter, r *http.Request) {
		app.RequestHandler(rw, r, VoterRingSig, VoterPrivateKey)
	})
	http.HandleFunc("/test.html", func(rw http.ResponseWriter, r *http.Request) {
		app.TestHandler(rw, r, VoterRingSig, VoterPrivateKey)
	})
	http.HandleFunc("/announce.html", app.AnnounceHandler)
	http.HandleFunc("/", func(rw http.ResponseWriter, r *http.Request) {
		http.Redirect(rw, r, "/home.html", http.StatusTemporaryRedirect)
	})
	http.HandleFunc("/check.html", func(rw http.ResponseWriter, r *http.Request) {
		app.CheckHandler(rw, r, controllers.Data)
	})

	fmt.Println("Listening (http://localhost:3000/) ...")
	http.ListenAndServe(":3000", nil)
}

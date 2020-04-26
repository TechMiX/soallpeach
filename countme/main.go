package main

import (
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"strconv"

	"github.com/sasha-s/go-deadlock"
)

var mutex deadlock.Mutex
var sum int64

func main() {

	listener, err := net.Listen("tcp", "0.0.0.0:80")
	if err != nil {
		log.Println("Error! cannot bind to port 80 :", err)
		return
	}

	serverMux := http.NewServeMux()
	serverMux.HandleFunc("/", SumRoute)
	serverMux.HandleFunc("/count", CountRoute)

	http.Serve(listener, serverMux)
}

func SumRoute(w http.ResponseWriter, r *http.Request) {
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		http.Error(w, "can't read body", http.StatusBadRequest)
		return
	}

	number, _ := strconv.Atoi(string(body))

	mutex.Lock()
	sum += int64(number)
	mutex.Unlock()
	w.Write([]byte(strconv.FormatInt(sum, 10)))
}

func CountRoute(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	w.Write([]byte(strconv.FormatInt(sum, 10)))
	mutex.Unlock()
}

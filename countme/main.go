package main

import (
	"io/ioutil"
	"net"
	"net/http"
	"strconv"

	"github.com/sasha-s/go-deadlock"
)

var sum int64
var mutex deadlock.Mutex

func main() {

	listener, _ := net.Listen("tcp", "0.0.0.0:80")

	serverMux := http.NewServeMux()
	serverMux.HandleFunc("/", IncreaseRoute)
	serverMux.HandleFunc("/count", CountRoute)

	http.Serve(listener, serverMux)
}

func IncreaseRoute(w http.ResponseWriter, r *http.Request) {
	body, _ := ioutil.ReadAll(r.Body)
	number, _ := strconv.Atoi(string(body[:len(body)-1]))

	mutex.Lock()
	sum += int64(number)
	mutex.Unlock()
}

func CountRoute(w http.ResponseWriter, r *http.Request) {
	mutex.Lock()
	w.Write([]byte(strconv.FormatInt(sum, 10)))
	mutex.Unlock()
}

package main

import (
	"io/ioutil"
	"net"
	"net/http"
	"strconv"
)

var sum int64

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

	sum += int64(number)

	w.Write([]byte(strconv.FormatInt(sum, 10)))
}

func CountRoute(w http.ResponseWriter, r *http.Request) {
	w.Write([]byte(strconv.FormatInt(sum, 10)))
}

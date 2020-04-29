package main

import (
	"strconv"

	"github.com/sasha-s/go-deadlock"
	"github.com/valyala/fasthttp"
)

var sum int64
var mutex deadlock.Mutex

func main() {

	m := func(ctx *fasthttp.RequestCtx) {
		switch string(ctx.Path()) {
		case "/":
			IncreaseRoute(ctx)
		case "/count":
			CountRoute(ctx)
		default:
			ctx.Error("not found", fasthttp.StatusNotFound)
		}
	}

	fasthttp.ListenAndServe(":80", m)
}

func IncreaseRoute(ctx *fasthttp.RequestCtx) {

	number, _ := strconv.Atoi(string(ctx.PostBody()))

	mutex.Lock()
	sum += int64(number)
	mutex.Unlock()
}

func CountRoute(ctx *fasthttp.RequestCtx) {
	mutex.Lock()
	ctx.Write([]byte(strconv.FormatInt(sum, 10)))
	mutex.Unlock()
}

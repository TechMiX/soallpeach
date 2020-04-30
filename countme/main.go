package main

import (
	"strconv"

	"github.com/valyala/fasthttp"
)

var sum int64

func main() {

	m := func(ctx *fasthttp.RequestCtx) {
		switch string(ctx.Path()) {
		case "/":
			buf := ctx.PostBody()
			number := int64(0)
			for i := 0; i < len(buf); i++ {
				number = (number << 1) + (number << 3) + int64(buf[i]-'0')
			}
			sum += number
		case "/count":
			ctx.Write([]byte(strconv.FormatInt(sum, 10)))
		default:
			ctx.Error("not found", fasthttp.StatusNotFound)
		}
	}

	fasthttp.ListenAndServe(":80", m)
}

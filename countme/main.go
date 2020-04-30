package main

import (
	"sync/atomic"

	"github.com/valyala/fasthttp"
)

const smallsString = "00010203040506070809" +
	"10111213141516171819" +
	"20212223242526272829" +
	"30313233343536373839" +
	"40414243444546474849" +
	"50515253545556575859" +
	"60616263646566676869" +
	"70717273747576777879" +
	"80818283848586878889" +
	"90919293949596979899"

var sum = new(int64)

func main() {

	m := func(ctx *fasthttp.RequestCtx) {

		// ENDPOINT /
		if len(ctx.Path()) == 1 {
			buf := ctx.PostBody()
			number := int64(0)
			for i := 0; i < len(buf); i++ {
				number = (number << 1) + (number << 3) + int64(buf[i]-'0')
			}
			atomic.AddInt64(sum, number)
			return
		}

		// ENDPOINT /count

		// from strconv/itoa.go
		// converts int64 to []byte: sum -> a
		var a [64 + 1]byte
		i := len(a)
		us := uint(atomic.LoadInt64(sum))
		for us >= 100 {
			is := us % 100 * 2
			us /= 100
			i -= 2
			a[i+1] = smallsString[is+1]
			a[i+0] = smallsString[is+0]
		}
		is := us * 2
		i--
		a[i] = smallsString[is+1]
		if us >= 10 {
			i--
			a[i] = smallsString[is]
		}

		ctx.Write(a[i:])

	}

	fasthttp.ListenAndServe(":80", m)
}

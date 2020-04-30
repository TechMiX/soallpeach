FROM golang:latest
WORKDIR ~
COPY . .
RUN go get github.com/valyala/fasthttp
RUN CGO_ENABLED=0 go build -ldflags="-s -w" -o countme main.go
ENTRYPOINT ["./countme"]

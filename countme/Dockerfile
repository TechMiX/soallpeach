FROM golang:latest
WORKDIR ~
COPY . .
RUN go get github.com/valyala/fasthttp
ENV GOGC off
RUN CGO_ENABLED=0 go build -ldflags="-s -w" -o countme main.go
ENTRYPOINT ["./countme"]

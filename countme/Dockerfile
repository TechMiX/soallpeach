FROM golang
WORKDIR ~
COPY . .
RUN go get github.com/sasha-s/go-deadlock
RUN CGO_ENABLED=0 go build -ldflags="-s -w" -o countme main.go
ENTRYPOINT ["./countme"]

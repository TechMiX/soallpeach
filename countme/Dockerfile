FROM gcc:latest
COPY . /app
WORKDIR /app
RUN gcc main.c -ocountme -O3
ENTRYPOINT ["./countme"]

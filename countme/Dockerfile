FROM gcc:latest
COPY . /app
WORKDIR /app
RUN gcc main.c -ocountme -ffast-math -O3
ENTRYPOINT ["./countme"]

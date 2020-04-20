FROM gcc:latest
COPY . /app
WORKDIR /app
RUN gcc main.c -oprimality -ffast-math -O3
ENTRYPOINT ["./primality"]

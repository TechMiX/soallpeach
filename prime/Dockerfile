FROM gcc:4.9
COPY . /usr/src/primality
WORKDIR /usr/src/primality
RUN gcc main.c -oprimality -lm -ffast-math -O2
ENTRYPOINT ["./primality"]

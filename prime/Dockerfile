FROM gcc:4.9
COPY . /usr/src/primality
WORKDIR /usr/src/primality
RUN gcc main.cpp -oprimality -lcrypto -lstdc++
ENTRYPOINT ["./primality"]

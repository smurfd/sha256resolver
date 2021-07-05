# to build on MacOS with Homebrew and openssl installed
g++ -o sha256 sha256.cc -lssl -lcrypto -I/opt/homebrew/Cellar/openssl@1.1/1.1.1k/include -L/opt/homebrew/Cellar/openssl@1.1/1.1.1k/lib

# to build on MacOS with Homebrew and openssl installed
g++ -o scripts/build/sha256 src/sha256.cc -lssl -lcrypto -I/opt/homebrew/Cellar/openssl@1.1/1.1.1q/include -L/opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib

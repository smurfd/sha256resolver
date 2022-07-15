# to build on MacOS with Homebrew and openssl installed
SSLINC=/opt/homebrew/Cellar/openssl@1.1/1.1.1q/include
SSLLIB=/opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib
g++ -o scripts/build/rsa src/rsa.cc -lssl -lcrypto -I$SSLINC -L$SSLLIB
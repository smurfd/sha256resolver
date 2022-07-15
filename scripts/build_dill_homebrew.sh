# brew install --build-from-source libdill
/opt/homebrew/bin/gcc-11 -o scripts/build/dill src/dill.c -I/opt/homebrew/Cellar/libdill/2.14/include/ -L/opt/homebrew/Cellar/libdill/2.14/lib/ -ldill

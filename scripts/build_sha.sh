# this only works on linux, didnt get it to build in Mac M1

# install crypto++
# sudo emerge -vaD crypto++
g++ -DNDEBUG -g3 -O3 -Wall -Wextra -o scripts/build/sha src/sha.cc -l:libcryptopp.so

# then run ./sha and you should get this output:
# name: SHA-256
# digest size: 32
# block size: 64
# -----------
# message: Yoda said, Do or do not. There is no try.
# digest: F00E3F70A268FBA990296B32FF2B6CE7A0757F31EC3059B13D3DB1E60D9E885C
# -----------
# message: Yoda said, Do or do not. There is no try.
# digest: F00E3F70A268FBA990296B32FF2B6CE7
# -----------
# message: Yoda said, Do or do not. There is no try.
# digest: F00E3F70A268FBA990296B32FF2B6CE7A0757F31EC3059B13D3DB1E60D9E885C
# -----------
# digest: F00E3F70A268FBA990296B32FF2B6CE7A0757F31EC3059B13D3DB1E60D9E885C
# verified hash over message
# -----------
# digest: F00E3F70A268FBA990296B32FF2B6CE7A0757F31EC3059B13D3DB1E60D9E885C
# verified hash over message

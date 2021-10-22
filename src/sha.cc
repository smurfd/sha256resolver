/*
https://cryptopp.com/
https://github.com/weidai11/cryptopp
https://cryptopp.com/docs/ref/
https://www.cryptopp.com/wiki/SHA
https://www.cryptopp.com/wiki/HashVerificationFilter
https://www.cryptopp.com/wiki/HMAC
*/

#include "cryptopp/cryptlib.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include <iostream>

using namespace CryptoPP;

void fn1(SHA256 hash) {
  printf("name: %s\n", hash.AlgorithmName().c_str());
  printf("digest size: %d\n", hash.DigestSize());
  printf("block size: %d\n", hash.BlockSize());
}

void fn2(SHA256 hash, std::string digest, std::string msg) {
  HexEncoder encoder(new FileSink(std::cout));

  hash.Update((const byte*)msg.data(), msg.size());
  digest.resize(hash.DigestSize());
  hash.Final((byte*)&digest[0]);
  printf("message: %s\n", msg.c_str());
  printf("digest: ");
  StringSource(digest, true, new Redirector(encoder));
  printf("\n");
}

void fn3(SHA256 hash, std::string digest, std::string msg) {
  HexEncoder encoder(new FileSink(std::cout));

  printf("message: %s\n", msg.c_str());
  hash.Update((const byte*)msg.data(), msg.size());
  digest.resize(hash.DigestSize()/2);
  hash.TruncatedFinal((byte*)&digest[0], digest.size());

  printf("digest: ");
  StringSource(digest, true, new Redirector(encoder));
  printf("\n");
}

void fn4(SHA256 hash, std::string digest, std::string msg) {
  HexEncoder encoder(new FileSink(std::cout));

  StringSource(msg, true, new HashFilter(hash, new StringSink(digest)));
  printf("message: %s\n", msg.c_str());
  printf("digest: ");
  StringSource(digest, true, new Redirector(encoder));
  printf("\n");
}

void fn5(SHA256 hash, std::string digest, std::string msg) {
  HexEncoder encoder(new FileSink(std::cout));

  hash.Update((const byte*)msg.data(), msg.size());
  digest.resize(hash.DigestSize());
  hash.Final((byte*)&digest[0]);

  printf("digest: ");
  StringSource(digest, true, new Redirector(encoder));
  printf("\n");

  hash.Update((const byte*)msg.data(), msg.size());
  bool verified = hash.Verify((const byte*)digest.data());
  if (verified == true)
    printf("verified hash over message\n");
  else
    printf("failed to verify hash over message\n");
}

void fn6(SHA256 hash, std::string digest, std::string msg) {
  HexEncoder encoder(new FileSink(std::cout));

  hash.Update((const byte*)msg.data(), msg.size());
  digest.resize(hash.DigestSize());
  hash.Final((byte*)&digest[0]);

  printf("digest: ");
  StringSource(digest, true, new Redirector(encoder));
  printf("\n");

  bool result;
  StringSource(digest+msg, true, new HashVerificationFilter(hash, new ArraySink((byte*)&result, sizeof(result))));

  if (result == true)
    printf("verified hash over message\n");
  else
    printf("failed to verify hash over message\n");
}


int main () {
  SHA256 hash;
  std::string msg = "Yoda said, Do or do not. There is no try.";
  std::string digest;

  fn1(hash);
  printf("-----------\n");
  fn2(hash, digest, msg);
  printf("-----------\n");
  fn3(hash, digest, msg);
  printf("-----------\n");
  fn4(hash, digest, msg);
  printf("-----------\n");
  fn5(hash, digest, msg);
  printf("-----------\n");
  fn6(hash, digest, msg);
  return 0;
}

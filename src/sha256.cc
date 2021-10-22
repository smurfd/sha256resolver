#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

char* sha256(const char *str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, (const void*)str, strlen(str));
  SHA256_Final(hash, &sha256);
  static char ss[SHA256_DIGEST_LENGTH*2];
  char ss_tmp[3];

  strcpy(ss, "");
  strcpy(ss_tmp, "");

  for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(ss_tmp, "%02x", (int)hash[i]);
    strcat(ss, ss_tmp);
  }
  return (char*)ss;
}

int main() {
  const char s[] = "test";
  const char s2[] = "test2";
  char s3[100];
  printf("--- %s\n", (char*)sha256(s));
  printf("--- %s\n", (char*)sha256(s));
  printf("--- %s\n", (char*)sha256(s2));
  printf("--- %s\n", (char*)sha256(s2));

  //printf("vvv %s\n", HASH_MAKE_STRING1((char*)sha256(s), s3);
  //printf("vvv %s\n", s3);
  return 0;
}

// BELOW SHIT WONT COMPILE
// grabbed below from openssl, will this create string from hash?
/*
#define HASH_MAKE_STRING1(c,s)   do {    \
  unsigned long ll;               \
  unsigned int  nn;               \
  switch ((c)->md_len)            \
  {   case SHA224_DIGEST_LENGTH:  \
    for (nn=0;nn<SHA224_DIGEST_LENGTH/4;nn++)       \
    {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
       break;                  \
       case SHA256_DIGEST_LENGTH:  \
       for (nn=0;nn<SHA256_DIGEST_LENGTH/4;nn++)       \
                {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
                break;                  \
            default:                    \
                if ((c)->md_len > SHA256_DIGEST_LENGTH) \
                    return 0;                           \
                for (nn=0;nn<(c)->md_len/4;nn++)                \
                {   ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));   }  \
                break;                  \
        }                               \
        } while (0)
*/

/*
// trying to reproduce HASH_MAKE_STRING
void mkstr(char* c, char* s) {
  do {
  unsigned long ll;
  unsigned int  nn;
  switch ((c)->md_len) {
    case SHA224_DIGEST_LENGTH:
      for (nn=0;nn<SHA224_DIGEST_LENGTH/4;nn++) {
        ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));
      }
      break;

    case SHA256_DIGEST_LENGTH:
      for (nn=0;nn<SHA256_DIGEST_LENGTH/4;nn++) {
        ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));
      }
      break;

    default:
      if ((c)->md_len > SHA256_DIGEST_LENGTH)
        return 0;
      for (nn=0;nn<(c)->md_len/4;nn++) {
        ll=(c)->h[nn]; (void)HOST_l2c(ll,(s));
      }
      break;
    }
  } while (0);
}
*/

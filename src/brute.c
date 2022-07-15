// inspired from https://gist.github.com/lvidakovic/5859203
// Author of above gist: Luka Vidakovi?
// Website: http://www.lukavidakovic.com

// Segfaults on mac, works on linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 5
int clength = 1, co, i;
char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char pw[] = "qXaY";
char *charsetptr = charset;
char **base = NULL;

void expandArray(char **baseArray, char* symbols, int length) {
  baseArray = (char**) realloc(baseArray, sizeof(char*)*(length+1));
  for(int i=0; i<length; i++) {
    baseArray[i] = symbols;
  }
}

int checkArray(char **baseArray, int len) {
  static char str[LENGTH];
  for(int i=0; i<len; i++)
    str[i] = *baseArray[i];

  // printf("%s\n", str); // enable for debugging output
  return strcmp(str, pw);
}

int main() {
  base = (char**) malloc(sizeof(char*));
  const char *charsetend = charsetptr + strlen(charset);

  while (clength <= LENGTH) {
    while (charsetptr < charsetend) {
      printf("c : %s %s\n", charsetptr, charsetend);
      base[clength - 1] = charsetptr++;
      if (checkArray(base, clength) == 0)
        printf("FOUND ... exiting\n");
    }

    co = 0;
    for (long i=clength - 1; i >=0; i--) {
      if (*base[i] == *(charsetend - 1))
        co++;
      else
        break;
    }

    if (co == clength) {
      expandArray(base, charset, clength);
      clength++;
    } else {
      base[clength - co - 1]++;
      for (long i=clength - 1; i>=clength - co; i--)
        base[i] = charset;
    }
    charsetptr = charset;
  }

  if (base)
    free(base);
  return 0;
}

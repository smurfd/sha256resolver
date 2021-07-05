#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
int ret1,ret2;

typedef struct {
  long l1;
  long l2;
  char* s;
  char* s_ret;
} things;

void swap(char *x, char *y) {
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void permute(char *a, long l, long r, things *t) {
  long i;
  if (l == r) {
    strcpy(t->s_ret, a);
//    printf("%s\n", a); // debug output
  } else {
    for (i = l; i <= r; i++) {
      swap((a+l), (a+i));
      permute(a, l+1, r, t);
      swap((a+l), (a+i)); //backtrack
    }
  }
}

void* doSomeThingCool(void *arg) {
  things *t = (things *)arg;
  unsigned long j = 0;
  pthread_t id = pthread_self();

  if(pthread_equal(id,tid[0])) {
    // 1st thread processing done
    permute(t->s, t->l1, t->l2, t);
  } else {
    // 2nd thread processing done
  }

  if(pthread_equal(id,tid[0])) {
    pthread_exit(&ret1);
  } else {
    pthread_exit(&ret2);
  }
  return NULL;
}

int main(void) {
  int i = 0;
  int err;
  int *ptr[2];
  char str[] = "abcdefghij";
  things *t = malloc(sizeof(things));

  t->l1 = 0;
  t->l2 = 9;
  t->s = (char*)malloc(sizeof(char) * (strlen("abcdefghij") + 1));
  t->s_ret = (char*)malloc(sizeof(char) * (strlen("abcdefghij") + 1));
  strcpy(t->s, "abcdefghij");
  strcpy(t->s_ret, "abcdefghij");
  printf("before : %s %s\n", t->s, t->s_ret);
  while(i < 2) {
    if (i == 0) { // future : i % 2 == 0 (to see if its dividable by 2
    err = pthread_create(&(tid[i]), NULL, &doSomeThingCool, t);
    } else if (i == 1) {
      err = pthread_create(&(tid[i]), NULL, &doSomeThingCool, t);
    }
    if (err != 0)
      printf("can't create thread :[%s]", strerror(err));
    else
      printf("Thread created successfully\n");

    i++;
  }

  pthread_join(tid[0], (void**)&(ptr[0]));
  pthread_join(tid[1], (void**)&(ptr[1]));

  printf("return value from first thread is [%d]\n", *ptr[0]);
  printf("return value from second thread is [%d]\n", *ptr[1]);

  printf("after : %s %s\n", t->s, t->s_ret);
  free(t);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int work(int i) {
  return i+1;
}

void fork1() {
  int a[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12, 13, 14, 15};
  int odd_sum = 0, even_sum = 0, n, i;
  n = fork(); //subdivide process
  if (n > 0) { //when n is not 0, then it is parent process
     for (int i : a) {
        if (i % 2 == 0)
        even_sum = even_sum + i;
        sleep(2);
     }
     printf("parent process\n");
     printf("sum of even numbers: %d\n", even_sum);
  } else { //when n is 0, then it is child process
     for (int i : a) {
        if (i % 2 != 0)
           odd_sum = odd_sum + i;
        sleep(2);
     }
     printf("Child process\n");
     printf("sum of odd numbers: %d\n", odd_sum);
  }
}

void fork2() {
  pid_t forkStatus;

  forkStatus = fork();

/* Child... */
  if (forkStatus == 0) {
    printf("Child is running, processing. %d\n", forkStatus);
    sleep(5);
    printf("Child is done, exiting. %d\n", forkStatus);

/* Parent... */
  } else if (forkStatus != -1) {
    printf("Parent is waiting...%d\n", forkStatus);
    wait(NULL);
    printf("Parent is exiting...%d\n", forkStatus);
  } else {
    perror("Error while calling the fork function");
  }


  int i,j = 0;

  const int targetFork = 4;

  do {
    j = work(j);
    forkStatus = fork();
    printf("forking %d...\n", i);
    sleep(6);
    i++;
  } while ((forkStatus != 0 && forkStatus != -1) && (i < targetFork));

  i = 0;
  do {
    i++;
    printf("waiting %d...\n", i);
    sleep(6);
    wait(NULL);
  } while (i < targetFork);


  printf("j = %d", j);
}

int main() {
  fork1();
  printf("---------\n");
  fork2();
/*
   int a[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12, 13, 14, 15};
   int odd_sum = 0, even_sum = 0, n, i;
   n = fork(); //subdivide process
   if (n > 0) { //when n is not 0, then it is parent process
      for (int i : a) {
         if (i % 2 == 0)
         even_sum = even_sum + i;
         sleep(2);
      }
      printf("parent process\n");
      printf("sum of even numbers: %d\n", even_sum);
   } else { //when n is 0, then it is child process
      for (int i : a) {
         if (i % 2 != 0)
            odd_sum = odd_sum + i;
         sleep(2);
      }
      printf("Child process\n");
      printf("sum of odd numbers: %d\n", odd_sum);
   }*/
  return 0;
}

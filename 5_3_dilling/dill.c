#include <libdill.h>
#include <stdio.h>
#include <stdlib.h>

coroutine void worker(const char *text) {
  while(1) {
    printf("%s\n", text);
    msleep(now() + random() % 500);
  }
}

coroutine void worker2(const char *text) {
  printf("--%s\n", text);
  msleep(now() + random() % 500);
}

int main() {
  go(worker("Hello!"));
  go(worker("Hai?!"));
  go(worker("World!"));
  msleep(now() + 500);

  int b = bundle();
  bundle_go(b, worker2("hai"));
  bundle_go(b, worker2("wurld"));
  bundle_go(b, worker2("???"));
  /* Give workers a bit to finish. */
  bundle_wait(b, now() + 2000);
  /* Cancel any remaining workers. */
  hclose(b);

  return 0;
}

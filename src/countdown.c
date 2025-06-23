#include "../include/modules.h"
#include <stdio.h>
#include <time.h>

int countDownMain() {
  int sec = 0;
  printf("Seconds: ");
  scanf("%d", &sec);

  while (sec > 0) {
    int h = sec / 3600;
    int m = (sec % 3600) / 60;
    int s = sec % 60;

    printf("\r%02d:%02d:%02d", h, m, s);
    fflush(stdout);

    clock_t stop = clock() + CLOCKS_PER_SEC;
    while (clock() < stop) {
    }

    sec--;
  }

  printf("\rTime's up!\n");
  return 0;
}

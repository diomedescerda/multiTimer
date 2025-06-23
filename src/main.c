#include "../include/modules.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("MultiTimer - A countup/countdown timer system\n");
    printf("\nUsage:  multitimer [options]\n");
    printf("Options:\n");
    printf("    --up     - Displays countUp timers system\n");
    printf("    --down     - Displays countDown timers system\n");
  } else if (argc == 2) {
    if (strcmp(argv[1], "--up") == 0) {
      countUpMain();
    } else if (strcmp(argv[1], "--down") == 0) {
      countDownMain();
    } else {
      printf("That's not a real option\n\n");
      printf("Options:\n");
      printf("    --up     - Displays countUp timers system\n");
      printf("    --down     - Displays countDown timers system\n");
    }
  } else {
    printf("無理\n");
  }
}

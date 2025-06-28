#include "../include/modules.h"
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int countDownMain() {
  char name[256];
  char time[9];
  char subject[25];
  regex_t regex;
  int timeValidation;
  int globalSeconds = 0;
  timeValidation =
      regcomp(&regex, "^([0-9]|0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$",
              REG_EXTENDED);

  do {
    printf("Set countdown time (HH:MM:SS format): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = 0;

    timeValidation = regexec(&regex, time, 0, NULL, 0);
    if (timeValidation == REG_NOMATCH) {
      printf("Invalid time format. Please try again (HH:MM:SS format).\n");
    }
  } while (timeValidation == REG_NOMATCH);
  regfree(&regex);

  int hour, min, sec;
  if (sscanf(time, "%d:%d:%d", &hour, &min, &sec) != 3)
    return -1;

  globalSeconds = sec + min * 60 + hour * 3600;

  while (globalSeconds > 0) {
    hour = globalSeconds / 3600;
    min = (globalSeconds % 3600) / 60;
    sec = globalSeconds % 60;

    printf("\r%02d:%02d:%02d", hour, min, sec);
    fflush(stdout);

    clock_t stop = clock() + CLOCKS_PER_SEC;
    while (clock() < stop) {
    }

    globalSeconds--;
  }

  printf("\rTime's up!\n");
  return 0;
}

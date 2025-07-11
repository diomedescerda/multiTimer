#include "../include/modules.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock;
typedef struct {
  int sec, min, hour;
} TimerState;

typedef struct {
  TimerState timer;
  bool running;
  bool exit_flag;
  double elapsed_seconds;
  clock_t start_time;
} StopWatch;

StopWatch sw = {
    .timer = {0, 0, 0},
    .running = false,
    .exit_flag = false,
    .elapsed_seconds = 0,
    .start_time = 0,
};

void *input_thread(void *arg) {
  while (!sw.exit_flag) {
    char cmd = getchar();
    pthread_mutex_lock(&lock);

    switch (cmd) {
    case ' ':
      if (!sw.running) {
        sw.start_time = clock();
        sw.running = true;
      } else {
        sw.elapsed_seconds +=
            (double)(clock() - sw.start_time) / CLOCKS_PER_SEC;
        sw.running = false;
      }
      break;
    case 'r':
      sw.elapsed_seconds = 0;
      sw.start_time = sw.running ? clock() : 0;
      break;
    case 'q':
      sw.exit_flag = true;
      break;
    default:
      printf(CLEAR_LINE);
      printf(RESTORE_CURSOR);
      printf(CLEAR_LINE);
      break;
    }

    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

void update_timer_thread(TimerState *timer, int seconds) {
  timer->sec = seconds % 60;
  timer->min = (seconds % 3600) / 60;
  timer->hour = seconds / 3600;
}

void *timer_thread(void *arg) {
  while (!sw.exit_flag) {
    pthread_mutex_lock(&lock);
    int current_time = sw.elapsed_seconds;
    if (sw.running) {
      current_time = sw.elapsed_seconds +
                     (double)(clock() - sw.start_time) / CLOCKS_PER_SEC;
    }
    update_timer_thread(&sw.timer, current_time);
    printf("\r%02d:%02d:%02d", sw.timer.hour, sw.timer.min, sw.timer.sec);
    fflush(stdout);
    pthread_mutex_unlock(&lock);
  }

  return NULL;
}

int countUpMain() {

  pthread_mutex_init(&lock, NULL);
  printf("Commands:\n");
  printf("  SPACE - Start/Stop timer\n");
  printf("  r - Reset the timer\n");
  printf("  q - Quit\n\n");
  printf(SAVE_CURSOR);

  pthread_t timer_tid, input_tid;

  pthread_create(&timer_tid, NULL, timer_thread, NULL);
  pthread_create(&input_tid, NULL, input_thread, NULL);

  pthread_join(timer_tid, NULL);
  pthread_join(input_tid, NULL);

  pthread_mutex_destroy(&lock);
  printf("\rFinal time: %02d:%02d:%02d\n", sw.timer.hour, sw.timer.min,
         sw.timer.sec);

  return 0;
}

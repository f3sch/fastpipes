/**
 * @file read a stream
 * @brief License-Identifier: MIT
 */

#include "common.h"

static void handler(int sig) {
  if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) { // very bad!
    fprintf(stderr, "Could not get end time!\n");
  }

  close(fileno(stdin));  // close pipe
  free(buf);

  int sec = end.tv_sec - start.tv_sec;
  int nsec = end.tv_nsec - start.tv_nsec;
  double time = (((double)sec) * 1000000000.0 + (double)nsec) / 1000000000;
  double read_gib = ((double)total) / 1000000000.0;
  double read_gib_psec = read_gib / time;

  printf("Time %.2f sec\n", time);
  printf("Read in total %.2f GiB\n", read_gib);
  printf("Throughput %.2f GiB/sec\n", read_gib_psec);
  fprintf(stderr, "Caught interrupt!\n");
  exit(EXIT_SUCCESS);
}

int main(void) {
  // Terminate nicer
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = handler;
  if (sigaction(SIGINT, &sa, NULL) == -1) {
    printf("Could not install interrupt catcher!\n");
    exit(EXIT_FAILURE);
  }

  size_t buf_size = BUFSIZE;
  buf = (char*)malloc(buf_size);

  total = 0;

  int devnull = open("/dev/null", O_WRONLY);

  // Take time now
  if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
    fprintf(stderr, "Could not get start time!\n");
  }

  // Loop
  while (true) {
    ssize_t ret = splice(STDIN_FILENO, NULL, devnull, NULL, BUFSIZE, SPLICE_F_NONBLOCK|SPLICE_F_MORE);
        if (ret < 0 && errno == EAGAIN) {
      continue;
    }
    if (ret < 0) {
      fail("splice failed: %s", strerror(errno));
    }
    total += ret;
  }

}

#include "common.h"

static void handler(int sig) {
  free(buf);
  fprintf(stderr, "Caught Pipe closing!\n");
  exit(EXIT_SUCCESS);
}

int main(void) {
  // Terminate nicely when closing the pipe
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = handler;
  if (sigaction(SIGPIPE, &sa, NULL) == -1) {
    printf("Could not install signal!\n");
    exit(EXIT_FAILURE);
  }

  size_t buf_size = BUFSIZE;
  buf = (char*)malloc(buf_size);
  memset((void*)buf, 'X', buf_size);

  // Loop
  while (true) {
    size_t remaining = buf_size;
    while (remaining > 0) {
      size_t _written =
          write(STDOUT_FILENO, &buf[buf_size - remaining], remaining);
      remaining -= _written;
    }
  }
}

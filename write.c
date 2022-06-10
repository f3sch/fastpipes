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
  char* bufs[2] = {buf, buf + buf_size / 2};
  int buf_ix = 0;

  // Loop
  while (true) {
    struct iovec bufvec = {
        .iov_base = bufs[buf_ix],
        .iov_len = buf_size / 2,
    };
    buf_ix = (buf_ix + 1) % 2;
    while (bufvec.iov_len > 2) {
      ssize_t ret = vmsplice(STDOUT_FILENO, &bufvec, 1, 0);
      bufvec.iov_base = (void*)(((char*)bufvec.iov_base) + ret);
      bufvec.iov_len -= ret;
    }
  }
}

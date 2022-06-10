#define _POSIX_C_SOURCE 201212L
#define _GNU_SOURCE 1
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 1<<18
#define TESTSIZE 1<<24

#define fail(...) do { fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); } while (false)

char* buf;
struct timespec start, end;
size_t total;

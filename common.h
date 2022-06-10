#define _POSIX_C_SOURCE 201212L
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <time.h>
#include <unistd.h>

#define BUFSIZE 1<<18
#define TESTSIZE 1<<24

char* buf;
struct timespec start, end;
size_t total;

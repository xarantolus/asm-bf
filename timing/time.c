#include <stddef.h>
#include "time.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <assert.h>

long timediff_ns(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
}

long time_since(struct timespec start)
{
    return timediff_ns(start, time_now());
}

struct timespec time_now()
{
    struct timespec now;

    assert(clock_gettime(CLOCK_MONOTONIC, &now) == 0);

    return now;
}

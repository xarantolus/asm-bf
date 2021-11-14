// This makes sure that CLOCK_MONOTONIC is available
#define _POSIX_C_SOURCE 199309L

#include <time.h>

// timediff_ns returns the number of nanoseconds between start and end
long timediff_ns(struct timespec start, struct timespec end);

// time_since returns the number of nanoseconds since start
long time_since(struct timespec start);

// time_now returns the current monotonic clock time
struct timespec time_now();

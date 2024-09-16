#ifndef __TIME_H__
#define __TIME_H__	1

#ifdef __cplusplus
extern "C" {
#endif

struct timespec {
    long seconds;  // secunde
    long nanoseconds; // nanosecunde
};

int nanosleep(const struct timespec *t1, struct timespec *t2);
#ifdef __cplusplus
}
#endif

#endif

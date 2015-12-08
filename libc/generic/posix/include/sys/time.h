
#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <mlibc/time_t.h>
#include <mlibc/suseconds_t.h>
#include <mlibc/timeval.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: this function is [OB]. disable it by default and add a macro to enable it
int gettimeofday(struct timeval *__restrict result, void *__restrict unused);

#ifdef __cplusplus
}
#endif

#endif // _SYS_TIME_H


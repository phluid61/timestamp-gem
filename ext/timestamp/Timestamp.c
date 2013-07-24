/*
 * Copyright (c) 2013, Matthew Kerwin <matthew@kerwin.net.au>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "ruby.h"
#include <time.h>

#if defined(HAVE_SYS_TIME_H)
# include <sys/time.h>
#endif

/*
 * Emulate clock_gettime() in Windows API calls.
 */
#ifdef _WIN32
# include <windows.h>
# include <math.h>

typedef long clockid_t;

struct timespec
{
    time_t tv_sec;
    long   tv_nsec;
};
typedef struct timespec timespec;

/* realtime clock (seconds since Epoch) */
# define CLOCK_REALTIME  0
/* monotonic-ish clock */
# define CLOCK_MONOTONIC 1

/* number of seconds from 1 Jan. 1601 00:00 to 1 Jan 1970 00:00 UTC */
# define EPOCH_DIFF 11644473600.0

/**
 * Get time in seconds since Epoch
 */
static int
clock_gettime_realtime(struct timespec *tp)
{
    SYSTEMTIME lt;
    FILETIME ft;
    ULARGE_INTEGER ul;
    double full_s, s, ns;

    /* get local time and convert it to an integer format */
    GetLocalTime(&lt);
    SystemTimeToFileTime(&lt, &ft);
    ul.LowPart = ft.dwLowDateTime;
    ul.HighPart = ft.dwHighDateTime;

    /* convert the integer time to Unix time */
    full_s = (double)(ul.QuadPart) / 1e4 - EPOCH_DIFF;

    /* extract seconds-part and nanoseconds-part */
    ns = modf(full_s, &s) * 1e9;
    tp->tv_sec = (time_t)s;
    tp->tv_nsec = (long)ns;
}

static double tick_per_s = -1.0;
/**
 * Get high-frequency ticking clock
 */
static int
clock_gettime_monotonic(struct timespec *tp)
{
    LARGE_INTEGER li;
    double full_s, s, ns;

    /* get per-second frequency (~ 1e9) */
    if (tick_per_s == -1.0) {
        if (!QueryPerformanceFrequency(&li)) {
	    errno = GetLastError();
	    return -1;
	}
	tick_per_s = (double)(li.QuadPart);
    }

    /* get current number of ticks (> 1e9) */
    if (!QueryPerformanceCounter(&li)) {
	errno = GetLastError();
	return -1;
    }
    /* get current number of seconds */
    full_s = (double)(li.QuadPart) / tick_per_s;

    /* extract seconds-part and nanoseconds-part */
    ns = modf(full_s, &s) * 1e9;
    tp->tv_sec = (time_t)s;
    tp->tv_nsec = (long)ns;
}

/**
 * Retrieve the time of the specified clock +clk_id+.
 */
static int
clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    if (clk_id == CLOCK_REALTIME)
	return clock_gettime_realtime(tp);
    if (clk_id == CLOCK_MONOTONIC)
	return clock_gettime_monotonic(tp);
    errno = 22; /* EINVAL on Linux? */
    return -1;
}

# define HAVE_CLOCK_GETTIME 1
#endif /* _WIN32 */

/*
 *  call-seq:
 *     Time.timestamp  -> int
 * 
 * Returns a nanosecond timestamp on the system's monotonic clock.
 *
 *     Time.timestamp  #=> 17817203921822
 */

static VALUE
time_s_timestamp(VALUE klass)
{
    VALUE t;

#ifdef HAVE_CLOCK_GETTIME
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
	rb_sys_fail("clock_gettime");
    }
    t = rb_uint2big(ts.tv_sec*1000000000 + ts.tv_nsec);
#else
    struct timeval tv;
    if (gettimeofday(&tv, 0) < 0) {
	rb_sys_fail("gettimeofday");
    }
    t = rb_uint2big(tv.tv_sec*1000000000 + tv.tv_usec*1000);
#endif

    return t;
}

/*
 *  call-seq:
 *     Time.unix_timestamp  -> int
 *     Time.unix_time       -> int
 *
 *  Returns the current time as an integer number of seconds
 *  since the Epoch.
 *
 *     Time.unix_timestamp  #=> 1363352771
 *     Time.unix_time       #=> 1363352771
 */

static VALUE
time_s_unix_timestamp(VALUE klass)
{
    return LONG2NUM( time(NULL) );
}

/*
 *  call-seq:
 *     Time.unix_microtime  -> float
 *
 *  Returns the current time as a floating-point number of seconds
 *  since the Epoch.
 *
 *     Time.unix_microtime  #=> 1363352771.315240
 */

static VALUE
time_s_unix_microtime(VALUE klass)
{
    double t;
#ifdef HAVE_CLOCK_GETTIME
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
	rb_sys_fail("clock_gettime");
    }
    t = (double)ts.tv_sec;
    t += ((double)ts.tv_nsec / 1000000000.0);
#else
    struct timeval tv;
    if (gettimeofday(&tv, 0) < 0) {
	rb_sys_fail("gettimeofday");
    }
    t = (double)tv.tv_sec;
    t += ((double)tv.tv_usec / 1000000.0);
#endif
    return rb_float_new(t);
}

void Init_timestamp() {
    rb_define_singleton_method(rb_cTime, "timestamp", time_s_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_time", time_s_unix_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_timestamp", time_s_unix_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_microtime", time_s_unix_microtime, 0);
}

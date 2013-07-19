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
#include <sys/time.h>
#endif

#ifndef MUL_OVERFLOW_SIGNED_INTEGER_P
#  define MUL_OVERFLOW_SIGNED_INTEGER_P(a, b, min, max) ( \
     (a) == 0 ? 0 : \
     (a) == -1 ? (b) < -(max) : \
     (a) > 0 ? \
       ((b) > 0 ? (max) / (a) < (b) : (min) / (a) > (b)) : \
       ((b) > 0 ? (min) / (a) < (b) : (max) / (a) > (b)))
#endif

#ifdef HAVE_CLOCK_GETTIME
#  define TIMESPEC timespec
#  define nsec(tv) ((tv)->tv_nsec)
#else
#  define TIMESPEC timeval
#  define nsec(tv) ((tv)->tv_usec*1000)
#endif

static inline VALUE
timespec2num(const struct TIMESPEC *ts) {
#ifdef HAVE_LONG_LONG
    if (!MUL_OVERFLOW_SIGNED_INTEGER_P(1000000000, (LONG_LONG)ts->tv_sec, LLONG_MIN, LLONG_MAX-999999999)) {
	return LL2NUM(nsec(ts) + 1000000000 * (LONG_LONG)ts->tv_sec);
    }
#endif
    return rb_funcall(LONG2FIX(nsec(ts), '+', 1, rb_funcall(LONG2FIX(1000000000), '*', 1, UINT2NUM(ts->tv_sec)));
}
#else

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
    struct TIMESPEC ts;

#ifdef HAVE_CLOCK_GETTIME
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
	rb_sys_fail("clock_gettime");
    }
#else
    if (gettimeofday(&ts, 0) < 0) {
	rb_sys_fail("gettimeofday");
    }
#endif
    t = timespec2num(&ts)
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
    struct TIMESPEC ts;
#ifdef HAVE_CLOCK_GETTIME
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
	rb_sys_fail("clock_gettime");
    }
    t = (double)ts.tv_sec;
    t += ((double)ts.tv_nsec / 1000000000.0);
#else
    if (gettimeofday(&ts, 0) < 0) {
	rb_sys_fail("gettimeofday");
    }
    t = (double)ts.tv_sec;
    t += ((double)ts.tv_usec / 1000000.0);
#endif
    return rb_float_new(t);
}

void Init_timestamp() {
    rb_define_singleton_method(rb_cTime, "timestamp", time_s_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_time", time_s_unix_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_timestamp", time_s_unix_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_microtime", time_s_unix_microtime, 0);
}

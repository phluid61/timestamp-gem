/*
 * Copyright (c) 2013, Matthew Kerwin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ruby.h"
#include <time.h>

#if defined(HAVE_SYS_TIME_H)
#include <sys/time.h>
#endif

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
 *
 *  Returns the current time as an integer number of seconds
 *  since the Epoch.
 *
 *     Time.unix_timestamp  #=> 1363352771
 */

static VALUE
time_s_unix_timestamp(VALUE klass)
{
    return INT2NUM( time(NULL) );
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
    rb_define_singleton_method(rb_cTime, "unix_timestamp", time_s_unix_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "unix_microtime", time_s_unix_microtime, 0);
}

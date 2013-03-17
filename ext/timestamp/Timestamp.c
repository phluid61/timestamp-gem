#include "ruby.h"
#include <time.h>

/*
 *  call-seq:
 *     Time.current_timestamp -> int
 *     Time.timestamp         -> int
 *
 *  Returns the current time as an integer number of seconds
 *  since the Epoch.
 *
 *     Time.current_timestamp  #=> 1363352771
 *     Time.timestamp          #=> 1363352771
 */

static VALUE
time_s_current_timestamp(VALUE klass)
{
    return INT2NUM( time(NULL) );
}

/*
 *  call-seq:
 *     Time.microtime  -> float
 *
 *  Returns the current time as a floating-point number of seconds
 *  since the Epoch.
 *
 *     Time.microtime  #=> 1363352771.315240
 */

static VALUE
time_s_microtime(VALUE klass)
{
    struct timeval tv;
    double t;
    if (gettimeofday(&tv, 0) < 0) {
        rb_sys_fail("gettimeofday");
    }
    t = (double)tv.tv_sec;
    t += ((double)tv.tv_usec / 1000000.0);
    return rb_float_new(t);
}

void Init_timestamp() {
    rb_define_singleton_method(rb_cTime, "current_timestamp", time_s_current_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "timestamp", time_s_current_timestamp, 0);
    rb_define_singleton_method(rb_cTime, "microtime", time_s_microtime, 0);
}

#include "ruby.h"
#include <time.h>

/*
 *  call-seq:
 *     Time.current_timestamp -> int
 *
 *  Returns the current time as an integer number of seconds
 *  since the Epoch.
 *
 *     Time.current_timestamp  #=> 1363352771
 */

static VALUE
time_s_current_timestamp(VALUE klass)
{
    return INT2NUM( time(NULL) );
}

void Init_timestamp() {
    rb_define_singleton_method(rb_cTime, "current_timestamp", time_s_current_timestamp, 0);
}

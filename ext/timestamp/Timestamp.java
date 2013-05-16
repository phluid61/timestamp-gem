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

//package au.net.kerwin.jruby;

import java.io.IOException;
import org.jruby.Ruby;
import org.jruby.RubyClass;
import org.jruby.RubyInteger;
import org.jruby.RubyFloat;
import org.jruby.RubyModule;
import org.jruby.anno.JRubyMethod;
import org.jruby.runtime.load.BasicLibraryService;

public class Timestamp implements BasicLibraryService {
    private Ruby runtime;

    public boolean basicLoad(final Ruby runtime) throws IOException {
	this.runtime = runtime;
	RubyClass rb_cTime = runtime.getClass("Time");
	rb_cTime.defineAnnotatedMethods(Timestamp.class);
	return true;
    }

    /*
     *  call-seq:
     *     Time.timestamp  -> int
     * 
     * Returns a nanosecond timestamp on the system's monotonic clock.
     *
     *     Time.timestamp  #=> 17817203921822
     */

    @JRubyMethod( name = "timestamp", meta = true )
    public RubyInteger timestamp() {
	return runtime.newFixnum(System.nanoTime());
    }

    /*
     *  call-seq:
     *     Time.unix_timestamp -> int
     *     Time.unix_time      -> int
     *
     *  Returns the current time as an integer number of seconds
     *  since the Epoch.
     *
     *     Time.unix_timestamp  #=> 1363352771
     *     Time.unix_time       #=> 1363352771
     */

    @JRubyMethod( name = {"unix_timestamp", "unix_time"}, meta = true )
    public RubyInteger unix_timestamp() {
	return runtime.newFixnum(System.currentTimeMillis() / 1000);
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

    @JRubyMethod( name = "unix_microtime", meta = true )
    public RubyFloat unix_microtime() {
	return RubyFloat.newFloat(runtime, System.currentTimeMillis() / 1000.0);
    }

}


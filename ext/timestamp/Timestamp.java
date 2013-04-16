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

package au.net.kerwin.jruby;

import org.jruby.Ruby;
import org.jruby.RubyClass;
import org.jruby.RubyFixnum;
import org.jruby.RubyFloat;
import org.jruby.anno.JRubyMethod;
import org.jruby.runtime.builtin.IRubyObject;
import org.jruby.runtime.load.BasicLibraryService;

public class Timestamp implements BasicLibraryService {
    private Ruby runtime;

    public boolean basicLoad(Ruby runtime) throws IOException {
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

    @JRubyMethod( name = "timestamp" )
    public IRubyObject timestamp() {
	//return new RubyFixnum(this.runtime, System.currentTimeMillis * 1000);
	return new RubyFixnum(this.runtime, System.nanoTime());
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

    @JRubyMethod( name = "unix_timestamp", alias = { "unix_time" } )
    public IRubyObject current_timestamp() {
	return new RubyFixnum(this.runtime, System.currentTimeMillis / 1000);
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

    @JRubyMethod( name = "microtime" )
    public IRubyObject microtime() {
	return new RubyFloat(this.runtime, System.currentTimeMillis / 1000.0);
    }
}


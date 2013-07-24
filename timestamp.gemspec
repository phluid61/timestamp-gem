Gem::Specification.new do |s|
	s.name    = 'timestamp'
	s.version = '1.0.2-win32'
	s.date    = '2013-07-24'
	s.summary = 'Time.timestamp'
	s.description = <<EOS
== Time.timestamp

Defines <tt>Time::timestamp</tt> and <tt>Time::unix_timestamp</tt>.

See the original discussion at {Ruby-Lang}[https://bugs.ruby-lang.org/issues/8096]

:call-seq:
  Time::timestamp  -> Integer

Returns a nanosecond-precision timestamp from the system's monotonic
clock. Note that the resolution of the measured time is system-
dependent (i.e. while the value displayed is always an integer number
of nanoseconds, the values may not necessarily change in increments of
exactly one).

This time value does not correlate to any absolute, real-world time
system; it is only useful for measuring relative (or elapsed) times at
a high granularity.  For example, benchmark measurements.

:call-seq:
  Time::unix_timestamp  -> Integer
  Time::unix_time       -> Integer

Returns the current real-world time as a whole number of seconds since
the Epoch (1-Jan-1970).

:call-seq:
  Time::unix_microtime  -> Float

Returns the current real-world time as a floating-point number of
seconds since the Epoch (1-Jan-1970).
EOS
	s.authors = ['Matthew Kerwin']
	s.email   = ['matthew@kerwin.net.au']

	files = Dir[
		'ext/timestamp/*.{c,java,rb}',
		'lib/*.rb'
	]
	if RUBY_PLATFORM =~ /java/
		s.platform = 'java'
		files << 'lib/timestamp.jar'
	else
		s.extensions = ['ext/timestamp/extconf.rb']
	end
	s.files = files

	s.add_development_dependency 'rake'
	s.add_development_dependency 'rake-compiler'
	s.add_development_dependency 'bundler'

	s.homepage = 'http://phluid61.github.com/timestamp-gem/'
	s.license = 'ISC License'
end


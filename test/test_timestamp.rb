require 'test/unit'
$VERBOSE = true

if defined?(JRUBY_VERSION)
	pre = (Time.public_methods - Time.instance_methods)

	#require 'java'
	require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp.jar"

	post = (Time.public_methods - Time.instance_methods)
	diff = (post - pre)
	if diff.empty?
		p diff.sort, post.sort
		`jar -t -f '#{File.dirname File.dirname(__FILE__)}/lib/timestamp.jar'`
		throw 'methods not defined'
	end
else
	require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp"
end

class Test_timestamp < Test::Unit::TestCase
	def test_timestamp
		stp = 1000.times.map{Time.timestamp}
		stp.inject do |m,t|
			assert( t >= m, "Retrograde timestamp #{m} to #{t}" )
			t
		end
	end
	def test_unix_time
		int = Time.now.to_i
		stp = Time.unix_time
		d = (stp-int).abs
		assert( d <= 1, "Unexpectedly highly difference #{d}" )
	end
	def test_unix_timestamp
		int = Time.now.to_i
		stp = Time.unix_timestamp
		d = (stp-int).abs
		assert( d <= 1, "Unexpectedly highly difference #{d}" )
	end
	def test_unix_microtime
		flt = Time.now.to_f
		stp = Time.unix_microtime
		d = (stp-flt).abs
		assert( d <= 1, "Unexpectedly highly difference #{d}" )
	end
end


require 'test/unit'

$VERBOSE = true
require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp"

class Test_timestamp < Test::Unit::TestCase
	def test_timestamp
		stp = [Time.timestamp, Time.timestamp, Time.timestamp]
		stp.inject do |m,t|
			d = t - m
			assert( d > 0, "Retrograde timestamp #{m} to #{t}" )
		end
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


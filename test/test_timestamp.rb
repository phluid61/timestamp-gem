require 'test/unit'

$VERBOSE = true
require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp"

class Test_timestamp < Test::Unit::TestCase
	def test_timestamp
		int = Time.now.to_i
		stp = [Time.timestamp, Time.current_timestamp]
		stp.each do |t|
			d = (t-int).abs
			assert( d <= 1, "Unexpectedly highly difference #{d}" )
		end
	end
	def test_microtime
		stp = Time.microtime
		int = Time.now.to_f
		d = (stp-int).abs
		assert( d <= 1, "Unexpectedly highly difference #{d}" )
	end
end


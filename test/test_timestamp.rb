require 'test/unit'

$VERBOSE = true
require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp"

class Test_timestamp < Test::Unit::TestCase
	def test_timestamp
		i = Time.now.to_i
		j = Time.current_timestamp
		d = (j-i).abs
		assert( d < 1, "Unexpectedly highly difference #{d}" )
	end
end


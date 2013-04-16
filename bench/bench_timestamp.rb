require 'benchmark'

require "#{File.dirname File.dirname(__FILE__)}/lib/timestamp"

n = 1_000_000
Benchmark.bm(20) do |x|
	x.report('Time.now.to_i')       { for i in 1..n; Time.now.to_i; end }
	x.report('Time.unix_timestamp') { for i in 1..n; Time.unix_timestamp; end }
	x.report('Time.now.to_f')       { for i in 1..n; Time.now.to_f; end }
	x.report('Time.unix_microtime') { for i in 1..n; Time.unix_microtime; end }
	x.report('Time.timestamp')  { for i in 1..n; Time.timestamp; end }
end


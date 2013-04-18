#!/usr/bin/env rake
require 'rubygems'
unless ENV['RUBY_CC_VERSION']
	require 'bundler'
	Bundler.setup
	Bundler::GemHelper.install_tasks
end
ENV['RUBYOPT'] = nil

spec = Gem::Specification.load('timestamp.gemspec')

task :default => [:timestamp]
task :timestamp => :compile

# compile: ext/timestamp/Timestamp.?
#   $(CC) $<
if RUBY_PLATFORM =~ /java/
	require 'rake/javaextensiontask'
	Rake::JavaExtensionTask.new('timestamp', spec)
else
	require 'rake/extensiontask'
	Rake::ExtensionTask.new('timestamp', spec)
end

# test: lib/timestamp.* test/test_timestamp.rb
#   ruby test/test_timestamp.rb
require 'rake/testtask'
Rake::TestTask.new do |tt|
	tt.verbose = true
end
task :test => :compile

# bench: lib/timestamp.* bench/bench_timestamp.rb
task :bench => :compile do
	exec "ruby -Ilib -Iext bench/bench_timestamp.rb"
end

# clean:
#   rm -r ...
require 'rake/clean'
CLEAN.include [
	'pkg', 'tmp',
	'**/*.{o,bundler,jar,so}',
]


#!/usr/bin/env rake

spec = Gem::Specification.load('timestamp.gemspec')
if RUBY_PLATFORM =~ /java/
	require 'rake/javaextensiontask'
	Rake::JavaExtensionTask.new('timestamp', spec)
else
	require 'rake/extensiontask'
	Rake::ExtensionTask.new('timestamp', spec)
end

require 'bundler/gem_tasks'
require 'rake/testtask'
task :default => [:test]
Rake::TestTask.new do |tt|
	tt.verbose = true
end


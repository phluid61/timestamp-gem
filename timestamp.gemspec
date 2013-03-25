Gem::Specification.new do |s|
  s.name = 'timestamp'
  s.version = '0.3.1'
  s.date = '2013-03-21'
  s.summary = 'Time.current_timestamp'
  s.description = 'Defines Time.current_timestamp , from https://bugs.ruby-lang.org/issues/8096'
  s.authors = ['Matthew Kerwin']
  s.email = ['matthew@kerwin.net.au']

  files = Dir['ext/timestamp/*.{c,java,rb}']
	if RUBY_PLATFORM =~ /java/
		s.platform = 'java'
		files << 'lib/timestamp.jar'
	else
    s.extensions = ['ext/timestamp/extconf.rb']
	end
	s.files = files

  s.homepage = 'http://rubygems.org/gems/timestamp'
  s.license = 'Simplified BSD License'
end

Gem::Specification.new do |s|
  s.name = 'timestamp'
  s.version = '1.0.1'
  s.date = '2013-04-13'
  s.summary = 'Time.timestamp'
  s.description = 'Defines Time.timestamp and .unix_timestamp , from https://bugs.ruby-lang.org/issues/8096'
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

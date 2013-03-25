Gem::Specification.new do |s|
  s.name = 'timestamp'
  s.version = '1.0.0'
  s.date = '2013-03-26'
  s.summary = 'Time.timestamp'
  s.description = 'Defines Time.timestamp and .unix_timestamp , from https://bugs.ruby-lang.org/issues/8096'
  s.authors = ['Matthew Kerwin']
  s.email = ['matthew@kerwin.net.au']

  s.files = Dir['ext/timestamp/*.{c,rb}']
  s.extensions = ['ext/timestamp/extconf.rb']

  s.homepage = 'http://rubygems.org/gems/timestamp'
  s.license = 'Simplified BSD License'
end

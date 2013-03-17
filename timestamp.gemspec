Gem::Specification.new do |s|
  s.name = 'timestamp'
  s.version = '0.3.0'
  s.date = '2013-03-15'
  s.summary = 'Time.current_timestamp'
  s.description = 'Defines Time.current_timestamp , from https://bugs.ruby-lang.org/issues/8096'
  s.authors = ['Matthew Kerwin']
  s.email = ['matthew@kerwin.net.au']

  s.files = ['ext/timestamp/Timestamp.c']
  s.extensions = ['ext/timestamp/extconf.rb']

  s.homepage = 'http://rubygems.org/gems/timestamp'
  s.license = 'Simplified BSD License'
end

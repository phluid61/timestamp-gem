Gem::Specification.new do |s|
  s.name = 'timestamp'
  s.version = '1.0.2'
  s.date = '2013-04-19'
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

  s.add_development_dependency 'rake'
  s.add_development_dependency 'rake-compiler'
  s.add_development_dependency 'bundler'

  s.homepage = 'http://rubygems.org/gems/timestamp'
  s.license = 'ISC License'
end

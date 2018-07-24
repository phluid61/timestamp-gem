
if defined?(JRUBY_VERSION)
  require 'jruby'
  require_relative 'timestamp.jar'

  class Time
    @@timestamp = Java::Default::Timestamp.new.tap{|ts| ts.java_send :basicLoad, [org.jruby.Ruby], org.jruby.Ruby.getGlobalRuntime }
    class << self
      def timestamp
        @@timestamp.java_send :timestamp, []
      end
      def unix_timestamp
        @@timestamp.java_send :unix_timestamp, []
      end
      alias :unix_time :unix_timestamp
      def unix_microtime
        @@timestamp.java_send :unix_microtime, []
      end
    end
  end
else
  require_relative "timestamp.#{RbConfig::CONFIG['DLEXT']}"
end


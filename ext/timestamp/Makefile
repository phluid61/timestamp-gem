
.PHONY: install clean

install: timestamp.jar
	cp timestamp.jar ../../lib/

timestamp.jar: Timestamp.class
	jar cf timestamp.jar Timestamp.class

Timestamp.class: Timestamp.java
	javac -target 1.5 -source 1.5 -cp /usr/lib/jruby/lib/jruby.jar Timestamp.java

clean:
	-rm Timestamp.class timestamp.jar ../../lib/timestamp.jar


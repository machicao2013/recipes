all: kv

thrift:
	thrift --gen cpp kv.thrift

kv: thrift
	cp *.cpp gen-cpp
	cp Makefile.gen-cpp gen-cpp/Makefile
	make -C gen-cpp

clean:
	rm -rf gen-cpp

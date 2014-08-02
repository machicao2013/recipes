CC=g++
SRC=.
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/protobuf/include/
LIBS=/home/maxingsong/opt/protobuf/lib/libprotobuf.a -lpthread

target=message_test
all:$(target)

message_test:message_test.cpp Foo.pb.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

.PHONY: compile clean
compile:
	/home/maxingsong/opt/protobuf/bin/protoc --proto_path=$(SRC) --cpp_out=. $(SRC)/Foo.proto

clean:
	rm -rf $(target) *.o

CC=g++
SRC=.
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/protobuf/include/
LIBS=/home/maxingsong/opt/protobuf/lib/libprotobuf.a -lpthread

target=dynamic_message
all:$(target)

dynamic_message:dynamic_message.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

.PHONY: compile clean

clean:
	rm -rf $(target) *.o

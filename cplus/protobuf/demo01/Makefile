CC=g++
SRC=.
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/protobuf/include/
LIBS=-L/home/maxingsong/opt/protobuf/lib/ -lprotobuf -lpthread

target= encode decode encdec encode2
all:$(target)

encode:person.pb.o encode.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -static person.pb.o encode.cpp -o encode $(LIBS)

encode2:person.pb.o encode2.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -static person.pb.o encode2.cpp -o encode2 $(LIBS)

decode:person.pb.o decode.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -static person.pb.o decode.cpp -o decode $(LIBS)

encdec: person.pb.o encode_decode.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -static $^ -o $@ $(LIBS)

person.pb.o: person.pb.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c person.pb.cc

.PHONY: compile clean
compile:
	/home/maxingsong/opt/protobuf/bin/protoc --proto_path=$(SRC) --cpp_out=. $(SRC)/person.proto

clean:
	rm -rf $(target) *.o

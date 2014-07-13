CC=g++
SRC=.
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/protobuf/include/
LIBS=-L/home/maxingsong/opt/protobuf/lib/ -lprotobuf -lpthread

target= addperson listaddress
all:$(target)

addperson:addperson.cpp addressbook.pb.cc
	$(CC) $(CFLAGS) $(INCLUDES) -static addressbook.pb.cc addperson.cpp -o addperson $(LIBS)

listaddress:listaddress.cpp addressbook.pb.cc
	$(CC) $(CFLAGS) $(INCLUDES) -static addressbook.pb.cc listaddress.cpp -o listperson $(LIBS)

.PHONY: compile clean
compile:
	protoc --proto_path=$(SRC) --cpp_out=. $(SRC)/addressbook.proto

clean:
	rm -rf $(target) *.o

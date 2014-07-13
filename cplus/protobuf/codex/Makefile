CC=g++
SRC=.
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/protobuf/include/
LIBS=-L/home/maxingsong/opt/protobuf/lib/ -lprotobuf -lpthread

target= codex
all:$(target)

codex:codex.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

.PHONY: compile clean
compile:
	protoc --proto_path=$(SRC) --cpp_out=. $(SRC)/person.proto

clean:
	rm -rf *.o

cleanall:
	rm -rf $(target) *.o

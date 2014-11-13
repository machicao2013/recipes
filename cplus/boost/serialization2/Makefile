CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_serialization.a

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

target=$(OBJS)
all:$(target)

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(target)
	rm -rf *.o

CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_program_options.a /home/maxingsong/opt/boost/lib/libboost_system.a

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

target=$(OBJS)
all:$(target)

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ $< $(INCLUDES) $(LIBS)

.PHONY: clean
clean:
	rm -rf $(target)

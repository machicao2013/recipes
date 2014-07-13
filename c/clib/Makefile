CC=g++
CFLAGS=-g -Wall -Werror

SRCS_C=$(wildcard *.c)
OBJS_C=$(patsubst %.c,%.o,$(SRCS_C))
SRCS_CPP=$(wildcard *.cpp)
OBJS_CPP=$(patsubst %.cpp,%.o,$(SRCS_CPP))

OBJS=$(OBJS_C) $(OBJS_CPP)

all:$(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

%.o:%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS)

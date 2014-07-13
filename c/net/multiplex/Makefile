CC=g++
CFLAGS=-g -Wall -Werror

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all:$(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS)

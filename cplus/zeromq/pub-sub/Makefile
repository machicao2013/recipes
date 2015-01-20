CC=gcc
CFLAGS=-g -O2
INCLUDES=-I/home/maxingsong/opt/zeromq/include/
LIBS=/home/maxingsong/opt/zeromq/lib/libzmq.a -lstdc++ -lpthread -lrt

SRCS=$(wildcard ./*.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all:$(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS)

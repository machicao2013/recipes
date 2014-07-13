CFLAGS=-g -Wall -Werror -Wextra

SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

all:$(OBJS)

%.o:%.c
	$(CC) -o $@ $< -lpthread

clean:
	$(RM) $(OBJS)

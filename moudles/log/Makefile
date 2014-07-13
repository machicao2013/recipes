CC=gcc
INCLUDE=
LIBS=
CFLAGS=-g -O2 -Werror -Wall -Wextra

target=usage

all:$(target)

usage:usage.c
	$(CC) $(CFLAGS) usage.c log.c -o usage $(INCLUDE) $(LIBS)

clean:
	rm -rf $(target)

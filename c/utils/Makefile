CC=gcc
INCLUDE=-I/home/maxingsong/opt/CUnit/include/
LIBS=-L/home/maxingsong/opt/CUnit/lib/ -lcunit
CFLAGS=-Werror -g

target=network_util_test

.PHONY:all

all:$(target)

network_util_test: network_util_test.c network_util.c network_util.h
	$(CC) $(CFLAGS) -o $@ network_util_test.c network_util.c $(INCLUDE) $(LIBS)

clean:
	- rm -rf $(target) *.o

CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_thread.a /home/maxingsong/opt/boost/lib/libboost_system.a -lpthread

target=thread_group_test
all:$(target)

thread_group_test: thread_group_test.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

.PHONY: clean
clean:
	rm -rf $(target)

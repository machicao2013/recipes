CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_regex.a

target=regex_test1
all:$(target)

regex_test1: regex_test1.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(target)

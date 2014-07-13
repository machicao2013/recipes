CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra -std=c++0x
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=

target=ref_test
all:$(target)

ref_test: ref_test.cpp
	$(CC) $(CFLAGS) $(INCLUDES) ref_test.cpp -o ref_test

.PHONY: clean
clean:
	rm -rf $(target)

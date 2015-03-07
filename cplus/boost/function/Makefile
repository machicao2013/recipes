CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=

target=function_test function_test2 function_test3 function_test4
all:$(target)

function_test: function_test.cpp
	$(CC) $(CFLAGS) $(INCLUDES) function_test.cpp -o function_test

function_test2: function_test2.cpp
	$(CC) $(CFLAGS) $(INCLUDES) function_test2.cpp -o function_test2

function_test3: function_test3.cpp
	$(CC) $(CFLAGS) $(INCLUDES) function_test3.cpp -o function_test3

function_test4: function_test4.cpp
	$(CC) $(CFLAGS) $(INCLUDES) function_test4.cpp -o function_test4

.PHONY: clean
clean:
	rm -rf $(target)

CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_program_options.a /home/maxingsong/opt/boost/lib/libboost_system.a

target=program_options program_options_2
all:$(target)

program_options: program_options.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

program_options_2: program_options_2.cpp
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

.PHONY: clean
clean:
	rm -rf $(target)

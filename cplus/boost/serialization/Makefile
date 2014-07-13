CC=g++
OPTIMIZE=-O2
#CFLAGS=$(OPTIMIZE) -g -Wall -Wextra
CFLAGS=$(OPTIMIZE) -g
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=/home/maxingsong/opt/boost/lib/libboost_serialization.a
HIREDIS_INCLUDE=-I/home/maxingsong/opt/hiredis/include/
HIREDIS_LIB=/home/maxingsong/opt/hiredis/lib/libhiredis.a

target=save load xml_seralization xml_seralization2 binary
all:$(target)

save: save.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

load: load.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

xml_seralization: xml_seralization.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

xml_seralization2: xml_seralization2.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

binary: binary.cpp SDCondValue.h
	$(CC) $(CFLAGS) $(INCLUDES) $(HIREDIS_INCLUDE) -o $@ $^ $(LIBS) $(HIREDIS_LIB)

.PHONY: clean
clean:
	rm -rf $(target)
	rm -rf *.o

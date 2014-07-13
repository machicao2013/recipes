CC=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra -MD
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=

CPPFLAGS=$(CFLAGS) $(INCLUDES)

PROJECT_DIR=

SRC=$(wildcard $(PROJECT_DIR)*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRC))
DEPS=$(patsubst %.cpp,%.d,$(SRC))

noncopyable_test_objs=$(filter noncopyable_test.o,$(OBJS))

TARGET=noncopyable_test
all:$(TARGET)

noncopyable_test: $(noncopyable_test_objs)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(DEPS)
	$(RM) -f $(TARGET)

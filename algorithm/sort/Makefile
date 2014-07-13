CXX=g++
CFLAGS=-g -Wall -Wextra -Werror
INCLUDE=
BASE_LIBS=

CPPFLAGS=$(CFLAGS) -MD $(INCLUDE)

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
DEPS=$(patsubst %.cpp,%.d,$(SRCS))

TARGETS=sort

all:$(TARGETS)

sort:$(OBJS)
	$(CXX) -o $@ $^ $(BASE_LIBS)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGETS)

-include $(DEPS)

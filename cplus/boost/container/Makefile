CXX=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra -Werror -MMD
INCLUDES=-I/home/maxingsong/opt/boost/include/
LIBS=
CPPFLAGS=$(CFLAGS) $(INCLUDES)

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
DEPS=$(patsubst %.cpp,%.d,$(SRCS))

target=$(OBJS)

all:$(target)

%.o:%.cpp
	$(CXX) $(CPPFLAGS) -o $@ $< $(LIBS)

-include $(DEPS)

clean:
	$(RM) $(target)
	$(RM) $(OBJS)
	$(RM) $(DEPS)

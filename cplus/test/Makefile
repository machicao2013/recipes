CXX=g++
OPTIMIZE=-O2
CFLAGS=$(OPTIMIZE) -g -Wall -Wextra -Werror -MMD -Wno-strict-aliasing
INCLUDES=-I/home/maxingsong/opt/boost/include/ -I/home/maxingsong/opt/mysql5.6.16/include/
LIBS=/home/maxingsong/opt/mysql5.6.16/lib/libmysqlclient_r.a -lpthread -lrt -ldl
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

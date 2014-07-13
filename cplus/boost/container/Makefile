CXX=g++
CFLAGS=-g -Wall -Werror -Wextra

BOOST_INCLUDE=-I/home/maxingsong/opt/boost/include/
BOOST_LIBS=

INCLUDES=$(BOOST_INCLUDE)
LIBS=$(BOOST_LIBS)

CPPFLAGS=$(INCLUDES) -MD

SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
DEPS=$(patsubst %.cpp,%.d,$(SRCS))

PTR_VECTOR_OBJS=$(filter ptr_vector_test.o,$(OBJS))

TARGET=ptr_vector

all:$(TARGET)

ptr_vector:$(PTR_VECTOR_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(TARGET)

-include $(DEPS)

CC=g++
BOOST_INCLUDE=-I/home/maxingsong/opt/boost/include/
THRIFT_INCLUDE=-I/home/maxingsong/opt/thrift-0.9.1/include/
BOOST_LIBS=
THRIFT_LIBS=/home/maxingsong/opt/thrift-0.9.1/lib/libthrift.a
CPPFLAGS=-Werror -g -O2

target=BookServletClient BookServletServer

SRC=$(wildcard ./gen-cpp/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRC))

.PHONY:all clean veryclean
all:$(target)

$(OBJS): %.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ $(BOOST_INCLUDE) $(THRIFT_INCLUDE) $(THRIFT_LIBS)

BookServletClient: BookServletClient.cpp $(OBJS)
	$(CC) $(CPPFLAGS) BookServletClient.cpp $(OBJS) -o BookServletClient $(BOOST_INCLUDE) $(THRIFT_INCLUDE) $(THRIFT_LIBS)

BookServletServer: BookServlet_server.skeleton.cpp $(OBJS)
	$(CC) $(CPPFLAGS) BookServlet_server.skeleton.cpp $(OBJS) -o BookServletServer $(BOOST_INCLUDE) $(THRIFT_INCLUDE) $(THRIFT_LIBS)

clean:
	- rm -rf $(OBJS)
veryclean:
	- rm -rf $(target)
	- rm -rf $(OBJS)


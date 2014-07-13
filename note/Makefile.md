1. SRC=$(wildcard *.cpp ./gen-cpp/*.cpp):列出当前目录和./gen-cpp/目录下面的所有cpp结尾的文件
2. OBJS := $(patsubst %.cpp,%.o,$(SRC)):把$(SRC)中所有以*.cpp结尾的文件替换为*.o结尾
3. 特殊的符号:
```
    $(OBJS): %.o: %.cpp
        $(CC) -c $(CFLAGS) $< -o $@ $(BOOST_INCLUDE) $(THRIFT_INCLUDE) $(THRIFT_LIBS)
    - $<: 表示当前的*.cpp文件
    - $@: 表示当前的目标集
```
<<<<<<< HEAD
=======
4. VPATH:如果没有指名这个变量，make只会在当前的目录中去找寻依赖文件和目标文件。如果定义了这个变量，那么，make就会在当当前目录找不到的情况下，到所指定的目录中去找寻文件了。VPATH=src:../headers.上面的定义指定了两个目录，src和../headers，make会按照这个顺序进行搜索。目录有冒号分割。
5. make会把其要执行的命令行在命令执行前输出到屏幕。当我们用@字符在命令行前，那么，这个命令将不被make显示出来。

>>>>>>> 45460c5e59e4853d9f717545b62f3d7ae9f3fad4

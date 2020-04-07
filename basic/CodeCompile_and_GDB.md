[TOC]

编译器编译原理：预处理，编译，汇编，链接各步骤详解

#gcc/g++等编译器 编译原理：预处理，编译，汇编，链接各步骤详解

##概述
C和C++编译器是集成的，编译一般分为四个步骤：
1. 预处理(preprocessing)  ----------------- cpp/ gcc -E 
2. 编译(compilation) ------------------ cc1 / gcc -S
3. 汇编(assembly)  -------------------- as
4. 连接(linking) --------------------- ld 

gcc
　　认为预处理的文件是(.i)是C文件，并且设定C形式的连接；
g++
　　认为预处理的文件是(.i)是C++文件，并且设定C++形式的连接；

源文件后缀名的一些含义和后续的操作：
+ .c　　　　　　C源程序　　　　　　　　 预处理，编译，汇编
+ .C　　　　　  C++源程序　　  　　　　预处理，编译，汇编
+ .cc　　　　　 C++源程序　　
+ .cxx 　　　　 C++源程序　　　　  　　预处理，编译，汇编
+ .m 　　　　　 Objective-C源程序　　　预处理，编译，汇编
+ .i 　　　　　 预处理后的C文件　　 　　编译，汇编
+ .ii　　　　　 预处理后的C++文件　　　 编译，汇编
+ .s　　　　　　汇编语言源程序　　　　　汇编
+ .S　　　　　　汇编语言源程序　　　　　预处理，汇编
+ .h　　　　　　预处理器文件　　　　　　通常不出现在命令行上　 

其他后缀名的文件被传递给连接器(linker).通常包括:
　　.o 目标文件(Object file)
　　.a 归档库文件(Archive file)


##具体介绍一下GCC编译步骤
首先，有以下hello.c源代码
```
#include<stdio.h>
int main()
{
 printf("Hello! This is our embedded world!\n");
 return 0;
}
```

1. 预处理阶段
在该阶段，编译器将上述代码中的stdio.h编译进来，并且用户可以使用Gcc的选项”-E”进行查看，该选项的作用是让Gcc在预处理结束后停止编译过程。预处理阶段主要处理#include和#define，它把#include包含进来的.h 文件插入到#include所在的位置，把源程序中使用到的用#define定义的宏用实际的字符串代替，我们可以用-E选项要求gcc只进行预处理而不进行后面的三个阶段，
注意 ： Gcc指令的一般格式为：Gcc -选项 要编译的文件 -选项 目标文件
其中，目标文件可缺省，Gcc默认生成可执行的文件，命为：编译文件.out
[root@localhost Gcc]# Gcc –E hello.c –o hello.i
在此处，选项"-o"是指目标文件，".i"文件为已经过预处理的C原始程序。以下列出了hello.i文件的部分内容：
```
typedef int (*__gconv_trans_fct) (struct __gconv_step *, struct __gconv_step_data *, void *, __const unsigned char *,
	                              __const unsigned char **, __const unsigned char *, unsigned char **, size_t *);
…

#"hello.c"
int main()
{
    printf("Hello! This is our embedded world!\n");
    return 0;
} 
```
由此可见，gcc确实进行了预处理，它把”stdio.h”的内容插入到hello.i文件中。

2. 编译阶段
接下来进行的是编译阶段，在这个阶段中，Gcc首先要检查代码的规范性、是否有语法错误等，以确定代码的实际要做的工作，在检查无误后，Gcc把代码翻译成汇编语言。用户可以使用”-S”选项来进行查看，该选项只进行编译而不进行汇编，生成汇编代码。
编译阶段是最重要的阶段，在这个阶段GCC首先检查语法然后把由上步生成的*.i编译成*.s文件。我们可以用如下命令告诉gcc进行这一步处理，gcc -S hello.i -o hello.s，-S选项告诉gcc把hello.i编译成.s文件；
这个阶段可以接收.c和.i类型的文件
[root@localhost Gcc]# Gcc –S hello.i –o hello.s

3. 汇编阶段
汇编阶段把*.s文件翻译成二进制机器指令文件*.o，如命令gcc -c hello.s -o hello.o，其中-c告诉gcc进行汇编处理。这步生成的文件是二进制文件，直接用文本工具打开看到的将是乱码，我们需要反汇编工具如GDB的帮助才能读懂它；
这个阶段接收.c, .i, .s的文件都没有问题。比如gcc -c hello.i -o hello.o等
汇编阶段是把编译阶段生成的”.s”文件转成目标文件，读者在此可使用选项”-c”就可看到汇编代码已转化为”.o”的二进制目标代码了。如下所示： 
[root@localhost Gcc]# Gcc –c hello.s –o hello.o

4. 链接阶段
在成功编译之后，就进入了链接阶段。在这里涉及到一个重要的概念：函数库。
读者可以重新查看这个小程序，在这个程序中并没有定义printf的函数实现，且在预编译中包含进的stdio.h中也只有该函数的声明，而没有定义函数的实现，那么，是在哪里实现printf函数的呢？最后的答案是：系统把这些函数实现都被做到名为libc.so.6的库文件中去了，在没有特别指定时，gcc会到系统默认的搜索路径/usr/lib下进行查找，也就是链接到libc.so.6库函数中去，这样就能实现函数”printf”了，而这也就是链接的作用。

##函数库一般分为静态库和动态库两种。
+ 静态库是指编译链接时，把库文件的代码全部加入到可执行文件中，因此生成的文件比较大，但在运行时也就不再需要库文件了。其后缀名一般为”.a”。
+ 动态库与之相反，在编译链接时并没有把库文件的代码加入到可执行文件中，而是在程序执行时由运行时链接文件加载库，这样可以节省系统的开销。动态库一般后缀名为”.so”，如前面所述的libc.so.6就是动态库。Gcc在编译时默认使用动态库。

1. 说下生成静态库的方法：
ar cr libxxx.a file1.o file2.o
就是把file1.o和file2.o打包生成libxxx.a静态库
使用的时候  gcc test.c -L/path -lxxx -o test
2. 动态库的话：
gcc -fPIC -shared file1.c -o libxxx.so
也可以分成两部来写：
gcc -fPIC file1.c -c //这一步生成file1.o
gcc -shared file1.o -o libtest.so
效果是一样的，用的时候和上面的静态库的用法一样，但是到了运行程序的时候，需要指定动态库的位置，可以环境变量来指定export LD_LIBRARY_PATH=path，否则会提示找不到动态库的位置
-----------
由于链接动态库和静态库的时候使用的方法是一样的，所以如果在库中有同名的静态库文件和动态库文件，比如libtest.a和libtest.so，根据gcc链接时默认优先选择动态库，会链接libtest.so，如果想要让gcc选择链接libtest.a那么需要指定一个选项，就是-static,这样就会强制gcc找静态库文件了。

静态库链接时搜索路径顺序：
1. ld会去找GCC命令中的参数-L
2. 再找gcc的环境变量LIBRARY_PATH
3. 再找内定目录 /lib   /usr/lib   /usr/local/lib 这是当初compile gcc时写在程序内的

动态链接时、执行时搜索路径顺序:
1. 编译目标代码时指定的动态库搜索路径
2. 环境变量LD_LIBRARY_PATH指定的动态库搜索路径
3. 配置文件/etc/ld.so.conf中指定的动态库搜索路径
4. 默认的动态库搜索路径/lib
5. 默认的动态库搜索路径/usr/lib

有关环境变量：
+ LIBRARY_PATH环境变量：指定程序静态链接库文件搜索路径
+ LD_LIBRARY_PATH环境变量：指定程序动态链接库文件搜索路径

完成了链接之后，gcc就可以生成可执行文件，如下所示。
[root@localhost Gcc]# gcc hello.o –o hello
运行该可执行文件，出现正确的结果如下。 
[root@localhost Gcc]# ./hello
Hello! This is our embedded world!


#GDB调试
命令：
```
g++ -g
gdb ./
```
##GDB调试基础命令
list/l：查看程序源码10行，回车查看更多代码
run/r：从头开始运行程序，但会在断点处停下 **可带参数**（或者set args “参数”，然后run）
continue/c：运行程序，但会在断点处停下

break/b [N]：在第N行添加断点，N也可以是函数名或汇编指令的地址
	+ 假设程序某处发生崩溃，怀疑是某个地方出现了非期望的值，那么就可以在这里断点观察，当出现该非法值时，程序断住 b 23 if 变量==值
	+ 循环中设置临时断点：tbreak 10
	+ 跳过多次设置断点：ignore Num 次数
print/p [variable]：打印变量
next/n：执行下一条指令
step/s：功能类似next，但会进入函数内部
finish/s：从函数体（没断点的）跳出
设置变量值：set var 变量名 = 值
设置追踪变量：display  取消追踪变量：undisplay  获取编号：info display
info [param]：显示当前断点和寄存器等。如`info break`

delete/d [N]：删除第N行断点

x/NFU ptr：查看地址ptr后指定字节的内容

disassemble<addr>：查看汇编形式的代码

##GDB调试多线程
info threads：查看所有线程，结果中左侧有星号为正在运行线程
thread id：切换到线程id
set scheduler-locking on：只运行当前线程，让其他线程阻塞

##GDB调试多进程

##调试已运行程序
1. 首先使用ps命令找到进程id：$ ps -ef|grep 进程名 或者：$ pidof 进程名
2. 假设获取到进程id为20829，调试进程：$ gdb (gdb) attach 20829 或者 gdb hello 20829(gdb program pid)

# makefile
1  目标：依赖条件     menu:main.c friend.c parent.c
2  <Tab>命令         	gcc main.c friend.c parent.c -o menu

## 提高性能
源文件过多编译时间过长，可以
menu:main.o friend.o parent.o
	gcc main.o friend.o parent.c -o menu
main.o:main.c
	gcc -c main.c
friend.o:friend.c
	gcc -c friend.c
parent.o:parent.c
	gcc -c parent.c

## makefile中的变量
文件太多，语句重复，可以用变量替代
$():取值操作
$<:规则中的第一个依赖
$@:规则中的目标
$^:规则中的所有依赖
gcc main.o friend.o parent.c -o menu | gcc $^ -o $@

obj=main.o friend.o parent.o
target=menu                   # 自定义变量
$(target):$(obj)
	gcc $(obj) -o $(target)
%.o:%.c
	gcc -c $< -o $@

makefile中自己维护的变量
CC=gcc
$(target):$(obj)
	$(CC) $(obj) -o $(target)
%.o:%.c
	$(CC) -c $< -o $@

## makefile中的函数
target=menu
src=$(wildcard ./*.c)                #wildcard函数查找某目录下文件并返回
obj=$(patsubst ./%.c, ./%.o, $(src)) #patsubst函数匹配替换1变2
$(target):$(obj)
	gcc $(obj) -o $(target)
%.o:%.c
	gcc -c $< -o $@
.PHONY:clean          #伪目标
clean:
	-mkdir /aa        #命令执行失败（权限），忽略，继续执行
	rm $(obj) $(target)
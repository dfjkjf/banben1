 [TOC]
#目标
+ 了解C++的核心设计思想
+ 掌握C++面向对象的设计思想
+ 能够看懂，调试，贡献C++开源项目

#C++常见问题
+ 跨平台
C++本身支持跨平台，但对库和编译器有所要求。由于其依赖性，导致其跨平台不如动态语言好（JavaScript、python）
+ 内存
程序员自己管理
+ 库
偏底层
+ 缺少功能

#编程步骤
+ IPO：input/process/output
+ 面向对象的设计思想：抽象数据类型（ADT）

#课程结构
1. 基础
	+ 编译，调试，环境设置
	+ C++语言，语法，语义
2. 核心
	+ 面向对象思想
	C++最重要的就是面向对象和抽象：抽象把代码分离为接口和实现。所以在设计组件时，必须保持接口独立于实现，这样，如果改变底层实现，接口也将保持不变。
	接口：接口描述了类的行为和功能，而不需要完成类的特定实现。
	面向对象的系统可能会使用一个抽象基类为所有的外部应用程序提供一个适当的、通用的、标准化的接口。然后，派生类通过继承抽象基类，就把所有类似的操作都继承下来。
	外部应用程序提供的功能（即公有函数）在抽象基类中是以纯虚函数的形式存在的。这些纯虚函数在相应的派生类中被实现。
	+ 封装，抽象，继承，多态
	数据封装是一种把数据和操作数据的函数捆绑在一起的机制，数据抽象是一种仅向用户暴露接口而把具体的实现细节隐藏起来的机制。
	+ 模板，STL
	+ IO，Lambda

#纯虚函数和纯接口类
类中有一个纯虚函数即为纯接口类，接口类不能实例化，被用作继承

#强制类型转换符(casting)

#智能指针
是一个类，用析构的方式帮助管理内存
```
#include <memory>
class A;
...
unique_ptr<A> a1 {std::make_unique<A>()};
auto a2 {std::make_unique<A>()};
a1->fun();
```

#更好的信息隐藏 和 弱化耦合
+ 使用者不能知道构造者太多信息
+ 例如两个类不能单独测试，可以在其中引入一个接口类
开关和灯两个类，引入接口类，灯继承自接口类
```
class Base {
public:
    virtual ~Base() {cout << "Base destruct" << endl;}
    virtual void isOn() = 0;
};

class Lamp:public Base {
public:
    Lamp(bool s):state(s) {cout << "construct Lamp state = " << s << endl;}
    ~Lamp() {cout << "Lamp destruct" << endl;}
    void isOn() {if(state){cout << "Y" << endl;} else {cout << "N" << endl;}}
private:
    bool state;
};

class Switch {
public:
    Switch(Base *_b):b)(_b){cout << "construct Switch" << endl;}
    void isOn() {b->isOn();}
private:
    Base *b;
};

int main()
{
    Base *b = new Lamp(1); Switch swi(b); swi.isOn(); delete b;
    return 0;
}
```

#Makefile
1. 问题
+ 编译命令
+ 告诉编译器文件路径
+ 互相依赖，编译顺序
+ 某文件改动依赖她的文件重新编译
2. 

#scheme

#C++内存模型作业
二维和多维数组在内存中如何表示

LinuxC++编译程序、编译多文件、编译库
用python编写自动化测试工具

#调试问题
代码检查分为：
1. 静态检查：不运行被测程序本身，仅通过分析或检查源程序的语法、结构、过程、接口等来检查程序的正确性
	+ 出现问题：空指针引用（野指针）；数据类型不匹配；返回局部变量；数组越界；内存泄漏；...
	+ 解决方法：语法问题用静态检查工具；数组越界要自己检查、内存泄漏
2. 动态检查：运行程序时检查，侧重于内存和资源使用情况检查
	+ 查log
	+ 注释掉不相干逻辑代码，二分法一点点缩小范围查找


#C++11、14、17新特性
1. 新关键字
	1. auto
	auto的自动类型推导，用于从初始化表达式中推断出变量的数据类型。auto实际上实在编译时对变量进行了类型推导，所以不会对程序的运行效率造成不良影响另外，似乎auto并不会影响编译速度，因为编译时本来也要右侧推导然后判断与左侧是否匹配。
	```
	auto a; // 错误，auto是通过初始化表达式进行类型推导，如果没有初始化表达式，就无法确定a的类型
	auto d = 1.0;
	auto str = "Hello World";
	auto func = less<int>();
	vector<int> iv;
	auto ite = iv.begin();
	auto p = new foo() // 对自定义类型进行类型推导 
	```
	2. nullptr
	NULL的二义性，用nullptr代替
	NULL在C++中被明确定义为整数0，C++让NULL也支持void *的隐式类型转换，这样编译器就不知道应该调用哪一个函数
	NULL只是一个宏定义，而nullptr是一个C++关键字，它可以转换成任何指针类型和bool布尔类型，但是不能被转换为整数。
	```
	#include <iostream>
	using namespace std;

	void fun(int *i)
	{
	    cout << "指针  << i << endl;
	}

	void fun(int i)
	{
	    cout << "int" << i << endl;
	}

	int main()
	{
	    fun(0);
	//  fun(NULL);
	    fun(nullptr);

	    return 0;
	}
	```
	3. 智能指针
	要确保用 new 动态分配的内存空间在程序的各条执行路径都能被释放是一件麻烦的事情。C++ 11 模板库的 <memory> 头文件中定义的智能指针
	`shared_ptr<T> ptr(new T);  // T 可以是 int、char、类等各种类型`
	此后，ptr 就可以像 T* 类型的指针一样使用，即 *ptr 就是用 new 动态分配的那个对象。
2. 序列for循环
在C++中for循环可以使用类似java的简化的for循环，可以用于遍历数组，容器，string以及由begin和end函数定义的序列（即有Iterator）
```
map<string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};
for (auto p : m){
    cout << p.first << " : " << p.second << endl;
}
```

3. Lambda表达式
它可以用于创建并定义匿名的函数对象，以简化编程工作。Lambda的语法如下：
[函数对象参数]（操作符重载函数参数）->返回值类型{函数体}
```
int a = 123;
auto f = [a] { cout << a << endl; }; 
f();
```

4. 更加优雅的初始化方法
在引入C++11之前，只有数组能使用初始化列表，其他容器想要使用初始化列表，只能用以下方法：

之前|C++11
:----:|:----:
`int arr[3] = {1, 2, 3};`|`int arr[3]{1, 2, 3};`
`vector<int> v(arr, arr + 3);`|`vector<int> iv{1, 2, 3};`
`map<int, spring> m;m[1]="Liu";m[10]="Wang";`|`map<int, string>{{1, "a"}, {2, "b"}};`
`string str = "Hello World";`|`string str{"Hello World"};`

#STL(标准模板库)
在C的基础上封装类与方法；
在编写代码时要添加命名空间；
容器：数据结构的存储，vector,set,map,stack,queue；
算法：sort()；
迭代器：一种检查容器内元素并遍历元素的数据类型。
通过把数据存储在容器里，实现效率更高的查询、修改、增删。
vector是一块连续内存，当空间不足了会再分配。
list是双向链表。
deque是双端队列可在头和尾部插入、删除元素。

##vector(数组的增强版)
+ 需要#include<vector>
+ 下标只能用于获取已存在的元素
+ 常用操作：
size(),empty(),clear(),push_back(尾加),pop_back(尾删),front(),back()

vector的reserve增加了vector的capacity，但是它的size没有改变！而resize改变了vector的capacity同时也增加了它的size！
原因如下：
1. reserve是容器预留空间，但在空间内不真正创建元素对象，所以在没有添加新的对象之前，不能引用容器内的元素。加入新的元素时，要调用push_back()/insert()函数。
2. resize是改变容器的大小，且在创建对象，因此，调用这个函数之后，就可以引用容器内的对象了，因此当加入新的元素时，用operator[]操作符，或者用迭代器来引用元素对象。此时再调用push_back()函数，是加在这个新的空间后面的。

Vector的容量之所以重要，有以下两个原因：
1. 容器的大小一旦超过capacity的大小，vector会重新配置内部的存储器，导致和vector元素相关的所有reference、pointers、iterator都会失效。
2. 内存的重新配置会很耗时间。

Vector内存扩展方式:（1）另觅更大空间；（2）将原数据复制过去；（3）释放原空间三部曲。 

```
int a[3] = {1, 2, 3};
vector<int> v;  // 申请一维未知大小int型数组
v.push_back(4); // v[0] = 4;
v.push_back(1); // v[1] = 1;

vector<int> v(a, a+3); // 将数组放入容器中，可对他进行操作

vector<const char *> v[2];  // 申请二维未知大小字符串型数组
v[0].push_back("asd"); 		// 第一行为“adc”
v[1].push_back("qwer"); 	// 第一行为“qwer”
for(int i=0;i<2;i++){
    for(int j =0;j<v[i].size();j++) {
        cout<<v[i][j]<<' ';
    }
}

v.insert(v.begin(),10);     //在向量最前端插入数据10
v.insert(v.begin(),5,20);   //在向量最前端插入5个数据20

vector<int> k(2,50);   //创建一个新的向量k,其拥有2个元素内容均为50
v.insert(v.begin(),k.begin(),k.end());  //在向量v最前端插入向量K的全部内容

v.erase(v.begin());     //删除第一个元素
v.erase(v.begin(),v.begin()+4); //删除从第一个开始后4个元素（包括第一个）
```
##set(去重、排序)


#面试常问
##虚函数
如果sizeof一个类D的对象，会发现比类C的对象大4个字节。多出来的这4个字节就是实现虚函数的关键——虚函数表指针vptr。这个指针指向一张名为“虚函数表”（vtbl）的表，而表中的数据则为函数指针，存储了虚函数fun_b()具体实现所对应的位置。
注意，普通函数、虚函数、虚函数表都是同一个类的所有对象公有的，只有成员变量和虚函数表指针是每个对象私有的，sizeof的值也只包括vptr和var所占内存（堆栈）的大小（也是个常出现的问题），并且vptr通常会在对象内存的最起始位置。另外，当类有多个虚函数时，仍然只有一个虚函数表指针vptr，而此时的虚函数表vtbl中会有多个函数指针，分别指向对应的虚函数实现区域。
再重复一遍虚函数实现的过程：通过对象内存中的vptr找到虚函数表vtbl，接着通过vtbl找到对应虚函数的实现区域并进行调用。
构造函数和析构函数可以是虚函数吗？
答案是构造函数不能是虚函数，析构函数可以是虚函数且推荐最好设置为虚函数。
虚函数的实现则是通过对象内存中的vptr来实现的。而构造函数是用来实例化一个对象的，没法在实例化对象前调用这个对象内存中的虚函数表指针。
当我们delete(a)的时候，如果析构函数不是虚函数，那么调用的将会是基类base的析构函数。与我们析构派生类的期望不符。
##类中有哪些默认函数：
构造和析构，
拷贝构造Empty(const Empty& );拷贝构造函数的参数只有一个且必须使用引用传参，使用传值方式会引发无穷递归调用
赋值运算符函数Empty& operator=(const Empty& );
取址运算符函数Empty* operator&();
取址运算符const函数 const Empty* operator&() const;
但是，只创建类不实例化时，就不会有这些默认函数。
##move构造函数
拷贝构造函数中，对于指针，我们一定要采用深层复制，而移动构造函数中，对于指针，我们采用浅层复制。
Str(Str &&)move使用浅拷贝，为了减少开销，将参数对象地址赋值给新对象，参数指针消亡。
```
// 用对象a初始化对象b，以后不用a了
string a = "I love xing";
vector<string> b ;
b.push_back(move(a));
```

##智能指针
对于编译器来说，智能指针实际上是一个栈对象，并非指针类型，在栈对象生命期即将结束时，智能指针通过析构函数释放有它管理的堆内存。
+ 行为表现的像指针实际是个对象
+ 方便管理堆内存，防止忘记释放内存和二次释放
+ 在头文件<memory>中，shared_ptr、unique_ptr、weak_ptr
	1. shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。shared_ptr内部的引用计数是线程安全的，但是对象的读取需要加锁。
	2. unique_ptr对于所指向的对象，正如其名字所示，是*独占*的。所以，不可以对unique_ptr进行拷贝、赋值等操作，但是可以通过release函数在unique_ptr之间转移控制权。

智能指针|语义|区别|用法
:---|:---|:---|:---
unique_ptr|move独占|指针不能拷贝构造|`unique_ptr<A> a = make_unique<A>();<br>unique_ptr<A> b = a; // 错<br>unique_ptr<A> C = move(a);`
shared_ptr|copy共享|引用计数|`unique_ptr<A> a = make_unique<A>();<br>unique_ptr<A> b = a;`
weak_ptr||`return unique_ptr<X>{new X};`|

##stl.vector.push_back()内部原理
判断以开辟最大容量caoacity，不够就增加分配的内存（翻倍）。
```
vector<int> v{1, 2, 3};
cout << v.capacity(); // 输出3
v.push_back(4);
cout << v.capacity(); // 输出6
```
string和vector clear()后内存不回收，要swap()
list,set,map clear()后内存回收

#一个典型的程序运行步骤：
1. 操作系统在创建进程后，把控制权交到了程序的入口，这个入口往往是运行库的中的某个入口函数。
2. 入口函数对运行库和程序运行环境进行初始化，包括堆、I/O、线程、全局变量构造，等等。
3. 入口函数在完成初始化之后，调用main函数，正式开始执行程序主体部分。
4. main函数执行完毕之后，返回到入口函数，入口函数进行清理工作，包括全局变量西沟、堆销毁、关闭I/O等，然后进行系统调用结束进程。
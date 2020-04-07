[TOC]
# Python3中有六个标准数据类型
+ 不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）
+ 可变数据（3 个）：List[列表]、Dictionary{字典}、Set（集合）
+ 赋值直接用，del删除
+ 在 python 中，类型属于对象，变量是没有类型的：
`a=[1,2,3];a="Nowcoder"`
以上代码中，[1,2,3] 是 List 类型，"Nowcoder" 是 String 类型，而变量 a 是没有类型，她仅仅是一个对象的引用（一个指针），可以是指向 List 类型对象，也可以是指向 String 类型对象。

## 数字
Python3 支持 int、float、bool、complex（复数）
```
var = 1
var2 = 10
```
不同类型的数混合运算时会将整数转换为浮点数。
*Python逻辑运算符、成员运算符、身份运算符*
```
a = 10
b = 20
list = [1, 2, 3, 4, 5 ];
if ( a and b ):
   print ("a和b都为真")
elif ( a or b ):
   print ("a和b有一个为真")
elif ( not b ):
   print ("b不为真")
elif ( a in list ):
   print ("a 在给定的列表中 list 中")
elif ( a not in list ):
   print ("a 不在给定的列表中 list 中")
if ( a is b ):					#类似 id(x) == id(y), id() 函数用于获取对象内存地址
   print ("a 和 b 有相同的标识")	#is 与 == 区别：is 用于判断两个变量引用对象是否为同一个， == 用于判断引用变量的值是否相等
elif ( a is not b ):
   print ("a 和 b 不具有相同的标识")
```

## 字符串
Python中的字符串用单引号 ' 或双引号 " 括起来
```
str = 'Nowocder'
print(str[2:5])            # 输出woc
```
Python中的字符串有两种索引方式，从左往右以0开始，从右往左以-1开始。
Python字符串运算符
* +(连接) *(重复) [](索引) [:](截取) in/not in(成员) r/R(原始) %(格式化)

## 列表
1. 列表是写在方括号 [] 之间、用逗号分隔开的元素列表,元素类型可以是数字、字符串、列表
```
list = [ 'abcd', 786 , 2.23, 'nowcoder', 70.2 ]
print (list[1:3])          # 输出[786, 2.23]
```
与Python字符串不一样的是，列表中的元素是可以改变的
`list[1] = 100`
Python 列表截取可以接收第三个参数，参数作用是截取的步长(间隔)
`prinr (list[0:3:2])		#输出['abcd', 2.23]`
2. 嵌套列表
```
a=['a','b','c']
n=[1,2,3]
x=[a,n]
print(x)		#输出[['a','b','c'],[1,2,3]]
print(x[0][1])	#输出b
```
3. 列表函数
len(list),max(list),min(list),list(seq)将元组转换为列表

## 元组
1. 元组与列表类似，不同之处在于元组的元素不能修改。元素写在小括号 () 里
```
tuple = ( 'abcd', 786 , 2.23, 'nowcoder', 70.2)
print (tuple[1:3])			#输出(786 , 2.23)
```
虽然tuple的元素不可改变，但它可以包含可变的对象，比如list列表。
2. 元组内置函数
len(tuple),max(tuple),min(tuple),tuple(seq)将列表转换成元组

## 字典
1. 列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
字典是一种映射类型，字典用 { } 标识，它是一个无序的 键(key) : 值(value) 的集合。
```
dict = {}
dict['one'] = "1 - 牛客教程"
dict[2]     = "2 - 牛客工具"
tinydict = {'name': 'nowcoder','code':1, 'site': 'www.nowcoder.com'}
print (dict['one'])       # 输出键为 'one' 的值
print (dict[2])           # 输出键为 2 的值
print (tinydict)          # 输出{'name': 'nowcoder','code':1, 'site': 'www.nowcoder.com'}
print (tinydict.keys())   # 输出所有键dict_keys(['name', 'code', 'site'])
print (tinydict.values()) # 输出所有值dict_values(['nowcoder', 1, 'www.nowcoder.com'])
```
2. 字典键的特性
不允许同一个键出现两次。创建时如果同一个键被赋值两次，后一个值会被记住；
键必须不可变，所以可以用数字，字符串或元组充当，而用列表就不行。

## 集合
集合是由一个或数个形态各异的大小整体组成的，构成集合的事物或对象称作元素或是成员。
基本功能是进行成员关系测试和删除*重复*元素。
可以使用大括号 {} 或者 set() 函数创建集合.
*注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。*
```
student = {'Tom', 'Jim', 'Mary', 'Tom', 'Jack', 'Rose'}
print(student)   	# 输出集合，重复的元素被自动去掉
# 成员测试
if 'Rose' in student :
    print('Rose 在集合中')
else :
    print('Rose 不在集合中')

# set可以进行集合运算
a = set('abracadabra')
b = set('alacazam')
print(a)
print(a - b)     	# a 和 b 的差集
print(a | b)     	# a 和 b 的并集
print(a & b)     	# a 和 b 的交集
print(a ^ b)     	# a 和 b 中不同时存在的元素
```

##Python数据类型转换
`float(x),str(x),tuple(x),list(s),set(s),dict(s)`

##循环语句
1. 在 while … else 在条件语句为 false 时执行 else 的语句块：
```
count = 0
while count < 5:
   print (count, " 小于 5")
   count = count + 1
else:
   print (count, " 大于或等于 5")
```
2. for循环可以遍历任何序列的项目，如一个列表或者一个字符串
```
languages = ["C", "C++", "Perl", "Python"]
for x in languages:
	print (x)
```
3. range()函数
如果你需要遍历数字序列，可以使用内置range()函数，它会生成数列。

## 迭代器与生成器
迭代器是访问集合元素的一种方式，它可以可以记住遍历的位置，迭代器对象从集合的第一个元素开始访问，直到所有的元素被访问完结束。迭代器只能往前不会后退。
迭代器有两个基本的方法：iter() 和 next()
```
list=[1,2,3,4]
it = iter(list)    		#创建迭代器对象
for x in it:
    print (x, end=" ")	#输出1 2 3 4
```

## 函数
1. 语法
def 函数名（参数列表）:
    函数体
2. python 函数的参数传递
不可变类型：类似 c++ 的值传递；
可变类型：类似 c++ 的引用传递
3. 匿名函数
python 使用 lambda 来创建匿名函数。
```
sum = lambda arg1, arg2: arg1 + arg2
print ("相加后的值为 : ", sum( 10, 20 ))
```
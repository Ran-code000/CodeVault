# c++ 中的 while(cin) 问题

## C++当中的 IO 流介绍 - operator 类型（）的特殊用法

C 语言中的 I/O 流
C 语言中的 I/O 流是基于 标准库函数 实现的，主要通过 stdio.h 头文件中的函数来操作。这些函数通常都是基于文件描述符来处理 I/O 操作。

常用的标准输入输出函数：
标准输入/输出流：

stdin: 标准输入流，通常是键盘。
stdout: 标准输出流，通常是屏幕。
stderr: 标准错误流，通常用于错误信息输出。
常用函数：

printf()：格式化输出到标准输出（通常是屏幕）。
scanf()：从标准输入（通常是键盘）读取输入。
getchar()：从标准输入读取一个字符。
putchar()：向标准输出写入一个字符。
fgets()：从文件或标准输入流读取一行字符串。
fputs()：向文件或标准输出流写入一行字符串。
fread() 和 fwrite()：用于从文件中读取和写入二进制数据。
fopen()：打开一个文件以进行读取、写入或追加。
fclose()：关闭文件。
fprintf()：格式化输出到文件。
fscanf()：从文件读取格式化数据。

注意：宽度输出和精度输出控制。C语言借助了相应的缓冲区来进行输入与输出。

https://i-blog.csdnimg.cn/blog_migrate/14ace60dea8fd85d3832fbafe983d8b8.png


C++ 语言中的 I/O 流
C++ 继承了 C 的 I/O 系统，但 C++ 引入了更先进的面向对象的 I/O 流。C++ 的 I/O 基于 流（stream）概念，通过标准库中的 iostream 和 fstream 提供了更强大的功能。

常用的 I/O 流类：
标准输入/输出流类：

std::cin：标准输入流，通常与键盘关联。
std::cout：标准输出流，通常与屏幕关联。
std::cerr：标准错误流，通常用于输出错误信息。
std::clog：标准日志流，用于输出日志信息（比 std::cerr 更适合用于日志）。
文件 I/O 流类：

std::ifstream：输入文件流，用于从文件读取数据。
std::ofstream：输出文件流，用于向文件写入数据。
std::fstream：文件流，既可以读取也可以写入文件。
常用成员函数：

std::cin >>：读取数据。
std::cout <<：输出数据。
std::getline()：读取一行字符串。
std::ifstream 和 std::ofstream 类提供了文件的读写操作。

关于 C 当中输入输出函数，对应 C++ 当中的输入输出流如下所示：

https://i-blog.csdnimg.cn/blog_migrate/5eb47cc47053bb20d96e79566ad3e75d.png


C++为什么要设计自己的IO 
C当中的输入输出就已经很够用了，C++为什么要自己设计 IO流呢？

原因就是，为了自定义类型的输入和输出。

C++ 是 面向对象的语言，就会诞生出很多自定义类型的输入和输出，而对于 自定义类型的输入和输出，普通的 printf 和 scanf 已经不够用了，比如 日期类的输入和输出，我们手动去用 printf 和 scanf 的话非常的麻烦，所以，C++ 当中就可以支持对  operator<<()  和 operator>>() 这两个流提取 和 流插入 操作符进行 重载。使用者可以根据自己的写的自定义类型，自定义这个类型的输入方式和输出方式

还有，如使用 printf 和 scanf 函数来输入输出自定义类型当中的成员的话，如果成员是 public 修饰的就还好，如果是 private私有的，在外部如何访问？

从而，C++ 为了能更好的 和控制台进行交互，就自己实现了一套 IO流。

 而在我们看来，cout 和 cin 对内置类型和已经重载的自定义类型，进行自动识别 从而进行 输出 或者输入，在本质上就是每一个 类型 都重载了 operator<<()  和 operator>>() 所以，从我们使用上来看，就好像是自动识别一样。

 而且，operator<<()  和 operator>>()   更形象化，比如 cout << n ; 就是把 n 这个变量流入到 屏幕上。

C++ while（cin >> n）返回值问题（operator（）的一种特殊用法）
string str;
while( cin >> str )
{
    cout << str << endl;
}
AI助手
相信你在写 OJ 题当中经常遇见这种情况，这种情况，当你输入任何一个字符串，回车都会输出这个字符串，然后紧接着你还可以输入字符串给 str：



 如果你想退出的话，可以输出 ctrl + z 然后 回车，就可以退出了。注意不能使用 ctrl + c 的方式退出，因为 这种方式退出的是程序的直接退出，不是正常的退出。

究竟是怎么实现的，就可以看 cin >> str 这个表达式的返回值是什么了。

cin >> str 本质是是调用 operator>>(cin , str) 这个函数，所以，我们要看这个函数的返回的值：
 



返回值是一个 istream 对象，istream 在这个其实就是这个 cin，因为 cin 是通过 传引用传入函数的，所以，返回值还是这个 cin；

cin 在本质上是不能给 while 循环 判断的。 但是有一个操作是可以进行判断：

在 C++98 当中是使用 opeartor！（）这个函数来实现的，但是在 C++11 当中是使用          operator bool（）这个函数来实现的。

 你可能有疑问，bool 是可以重载的吗？答案是肯定的。

先看下述例子：
 

class A
{
public:
	A(int a)
	{
		_a = a;
	}
private:
	int _a = 1;
};
 
int main()
{
	A aa1(1);
	A aa2(2);
	
	// 内置类型转换为 自定义类型 （隐式类型转换，可以使用构造+拷贝构造实现对 aa1的赋值）
	aa1 = 2;
 
	// 自定义类型转换为 内置类型（因为类型不相似，不能发生隐式类型转换）
	int n = aa2; // 报错
 
	return 0;
}

AI助手
上述的 int n = aa2 这个操作是不行的，此处要发生类型的转换，要是用C++ 的四种类型转换之一的 reinterpret_cast 来转换。

如果我们想使用 （int）aa2 的方式强制转换的话，需要重载 operator（）这个运算符函数。C语言当中能强转的运算符是 "()" ,所以我们期望对这个 operator（）重载。但是，此处的  （）不能当中是 用于强转的运算符，此时这个运算符（operator（））已经被 仿函数当中的用法给占用了：

class Less
{
public:
	int operator() (int x, int y)
	{
		return x < y;
	}
};
 
int main()
{
	Less less;
	int x = 10, y = 20;
 
	cout << less(x, y) << endl;
 
	return 0;
}

AI助手


此时，operator（）重载的是上述 "()" 小括号的使用方式，但是我们现在想使用的方式是在 (int)x ，在变量前使用的方式，这样的话两者就冲突了，所以，C++在这里进行了特殊处理，也就是一种特殊用法：
 

	operator int()
	{
		return _a;
	}
AI助手
上述看似是重载了 类型 int 其实是重载了 在变量左边使用的 "()" 。

完整代码：
 

class A
{
public:
	A(int a)
	{
		_a = a;
	}
 
	operator int()
	{
		return _a;
	}
 
private:
	int _a = 1;
};
 
int main()
{
	A aa1(1);
	A aa2(2);
	
	// 内置类型转换为 自定义类型 （隐式类型转换，可以使用构造+拷贝构造实现对 aa1的赋值）
	aa1 = 2;
 
	// 自定义类型转换为 内置类型 （因为重载了 左括号 “（）”所以可以执行）
	int n = (int)aa2; 
 
	return 0;
}

'AI助手
运行运行
此时，我们就重载了 在变量左边使用的 “（）”运算符。

 注意：上述的 operator int () 并不是没有指定返回值，int 就是这个函数的返回值，当然，你还可以写成 operator double () 各种类型的模式，代表的就是 不同类型的强转的返回值。 

此时你应该就理解了，operator bool () 这个函数的实现意义了，在while（表达式），这个式子当中，表达式的返回值必须是 bool 类型，或者是 0 表示 假，非零表示真；但是while的表达式 接收还是一个 bool 类型。

所以 while(cin >>str ) 就发生了像上述的强转，因为 在 istream 的 父类 ios 类 当中重载 了 operator bool（）函数，可以发生强转。



 但是如上所示，在库当中实现的 operator bool () 函数，使用 explicit 关键词修饰的，我们知道，explicit 关键字修饰的函数，是不能发生 类型转换的。但是，operator bool () 是可以转换的（但是必须是显示的进行转换）：
 



 如上所示，程序正常运行。

其实在这个地方，加上 explicit 就是限制了 operator int ()  这个函数的隐式类型转换，如下所示，进行隐式类型转化的时候会报错，也 operator int （）加上了 explicit 修饰：



但是，如果是进行显示类型转换（强制转换）的话，还是可以调用到 opeartor int () 进行强转的：
 



 这个你就需要注意了，我相信你现在可能有疑问，这个 (int)aa1 不是C 当中的强制类型转换吗 ？和 operator int（ ）函数有什么关系呢？

如果我们没有 operator int （）这个函数的话，直接 (int) aa1 是会报错的：



具体原因请看上述对于为什么要重载 operator int （）介绍。

 还需要注意 operator bool () 和 其他类型的 operator 类型 () 可能会冲突，比如 operator bool （）和 operator int （）：



这是为什么呢？我们现在先只用 operator bool （）函数来做强转试试：



 发现，aa1 当中的 _a 成员变量此时的值应该是 10， 但是 n 却输出了1，注意，n不是 bool 类型的，而是  double 类型的。

我们调试查看，n 和 aa1 当中的 _a 成员变量的值是多少：

 



发现只是 n 的值接收为 1，aa1 当中 _a 的值就是 10 。因为 是按照bool 输出的，0 即为假，非0 即为真。

对于 operator int （）的例子，这里不在做演示，直接告诉结果，n 输出就是 10，和 aa1 当中的 _a 成员变量输出结果是一样的。

 这里举例说明是要让读者清楚，operator bool （）和 operator int （） 是会使用冲突的，如果你两个函数都实现了，当前情况下，指向使用 其中某一个函数的话，可以考虑使用 explicit 修饰其中一个你不想用的函数。

 还需要注意的是，在 IO 当中，有四个类是 菱形继承的关系：



 这也是 C++ 的搞出 菱形继承之后，大胆的在自己的官方库当中使用 这个大坑。

C++ 的文件 IO流 
 C 当中，根据文件不同的数据格式分为二进制文件 和 文本文件，同样具有 二进制的输入方式和 文件的输入文件的方式。

下面是一个日期类以二进制访问输出到文件当中：
 

	Date d(2023, 10, 14);
	FILE* fin = fopen("file.txt", "w");
	fwrite(&d, sizeof(Date), 1, fin);
	fclose(fin);
AI助手
但是以二进制的方式输入到文件当中是不好的方式，因为 输入到文件当中，我们是看不懂的，所以我们还是要以 文本的方式输入的到文件当中：
 

class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
 
	// 简单实现一个 把日期类当中的数据写到 一个 string当中
	operator string()
	{
		string str;
		str += to_string(_year);
		str += ' ';
		str += to_string(_month);
		str += ' ';
		str += to_string(_day);
		return str;
	}
 
	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}
private:
	int _year;
	int _month;
	int _day;
};
 
istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
 
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}
 
int main()
{
	Date d(2023, 10, 14);
	FILE* fin = fopen("file.txt", "w");
	string str = d;
	fputs(str.c_str(), fin);
	return 0;
}

AI助手
像上述，我们简单的实现了一个 operator string （ ）函数，把 日期当中的成员 强转为 string 的时候，就把 成员的内容尾插到 string 当中存储。

但是，上述的 用C 解决方式还是太麻烦了。

C++根据 文件内容的数据格式 分为 二进制文件 和 文本文件 。采用文件流对象操作文件的一般步
骤：

 定义一个文件流对象（ifstream ifile(只输入用)
                                     ofstream ofile(只输出用)
                                     fstream iofile(既输入又输出用））
 使用文件流对象的成员函数打开一个磁盘文件，使得文件流对象和磁盘文件之间建立联系
 使用提取和插入运算符对文件进行读写操作，或使用成员函数进行读写
 关闭文件
我们更多的是使用 fstream 这个流，因为这个既可以输入又可以输出。 

 C++ 当中关键的两个文件输入输出流，ifsream 和 ofstream 都是都是各自继承了 istream 和 ostream：



文件 IO流使用介绍
我们这里就直接使用 fstream 来演示了。

要使用 fsream 就要引入头文件：

#include<fstream>
AI助手
 C++ 当中使用 fstream 有两种使用方式：

open 函数：


 这种方式就和 C语言当中的使用方式是类似的，open（）函数的第一个参数是 文件名，支持用 C 当中的字符串的形式传入，也支持使用 string 对象的方式传入；第二个参数 是 文件使用的方式，这个就和  C 当中的使用方式是一样的了：

除了可以使用 C当中 类似 'r'  'w' 这样的方式来确定读取文件的方式，还可以使用 C++ 当中独有的方式，具体请看下面一种方式 当中的详细介绍。

构造函数的方式使用：
其实上述的open 函数的使用方式和 C 当中差别不大，看不出 C++ IO流的提升，所以，我们更多使用的方式是使用构造函数的方式来使用：
 

	fstream ofs("text.txt", ios_base::out | ios_base::in);
AI助手


 同样支持 字符创 和 string 两种方式的文件名传入，第二个参数也是 文件的读取操作，文件读取方式，默认缺省值是  out 也就是 覆盖写的方式读取文件。

在C++当中，对于文件的读取方式有做了进一步的 修改，有一下几种文件的读取方式：



成员常量	代表	access
in	input	文件打开读取：内部流缓冲区支持输入操作。（读文件）
out	output	文件打开写入：内部流缓冲区支持输出操作。（覆盖写文件）
binary	binary	操作以二进制模式而不是文本模式执行。（以二进制的方式操作文件）
ate	at end	输出位置从文件末尾开始。（追加写文件）
app	append	所有输出操作都发生在文件的末尾，并附加到其现有内容。
trunc	truncate	文件打开之前存在的任何内容都将被丢弃。
 上述的操作同样的是可以一起使用的，如果你想把多个 操作一起使用的话，可以在不同操作之间加 "|" 来连接。

那么，向上述的 out ，ate ， app 这些操作，是如何实现用 "|" 来区分的呢？

实际上是使用 1,2,4,8 这样的方式来区分的：



 这样的话，每一个操作代表一个 二进制位为1 的值，那么两者 的 "|" 的结果，不同的操作 "|" 出来时不一样的结果。

 IO流对象的释放
fstream 当中是支持了 fclose （）这个文件关闭的函数的，但是，实际使用方式我们是不用显示的写 fclose 这个函数的。

因为 fstream 是一个类，这个类当中是有析构函数的，在这个析构函数当中就调用了 fclose（）函数，当 这 fstream 类对象出了自己的作用之后，就会自动地调用析构函数。



写入文件
 fstream 当中就有 write（）这个函数，用于写入文件内存：

	Date d(2023, 1, 1);
 
	fstream ofs("text.txt", ios_base::out|ios_base::binary);
	ofs.write( (const char*) &d, sizeof(d));
AI助手
如下就是以 二进制的方式写。

但是，如果是使用文本大方式来写的话，不用像上述一样使用 write（）函数，可以直接使用 "<<":

	Date d(2023, 1, 1);
 
	fstream ofs("text.txt", ios_base::out|ios_base::binary);
 
	ofs << d;
AI助手
这里的 Date 能使用 "<<" 的原因是，Date 当中重写了 operator<<() 这个函数：如果，没有重写这个函数是不能使用 "<<" 的方式写入文件的：

istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
 
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}
AI助手
这里，是 ostream 类 的 out 传给了 fstream 类的 ofs，其实使用使用多态的原理，我们在上述也介绍过，ifsream 和 ofstream 都是都是各自继承了 istream 和 ostream的。



一个二进制 和 文本方式 读写的  简单IO类实现
#include<fstream>
 
class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
 
	// 简单实现一个 把日期类当中的数据写到 一个 string当中
	operator string()
	{
		string str;
		str += to_string(_year);
		str += ' ';
		str += to_string(_month);
		str += ' ';
		str += to_string(_day);
		return str;
	}
 
	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}
private:
	int _year;
	int _month;
	int _day;
};
 
istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}
 
ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}
 
struct ServerInfo
{
	// 注意这里 不建议 用 string vector 这样的自定义对象
	char _address[32];
	
	int _port;
	Date _date;
};
 
// 整个类都是以二进制方式书写的
struct ConfigManager
{
public:
	// 构造函数
	ConfigManager(const char* filename)
		:_filename(filename)
	{}
 
	// 往文件当中以 二进制方式 书写的函数
	// 二进制书写往往是非常快的，因为如果是以文本形式书写的话，还需要按编码形式来进行转换
	void WriteBin(const ServerInfo& info)
	{
		ofstream ofs(_filename, ios_base::out | ios_base::binary);
		ofs.write((const char*)&info, sizeof(info));
	}
 
	// 从文件当中以 二进制方式 读取数据 到内存 的函数
	void ReadBin(ServerInfo& info)
	{
		ifstream ifs(_filename, ios_base::in | ios_base::binary);
		ifs.read((char*)&info, sizeof(info));
	}
 
	// 以文本的方式往 文件当中写输入
	void WriteText(const ServerInfo& info)
	{
		ofstream ofs(_filename);
		ofs << info._address << " " << info._port << " " << info._date;
	}
 
	// 以文本的方式从文件当中读数据
	void ReadText(ServerInfo& info)
	{
		ifstream ifs(_filename);
		ifs >> info._address >> info._port >> info._date;
	}
 
private:
	string _filename; // 配置文件
};
 
int main()
{
	ServerInfo winfo = { "192.0.0.1", 80, { 2022, 4, 10 } };
 
	// 二进制读写
	ConfigManager cf_bin("test.bin");
	cf_bin.WriteBin(winfo);
	ServerInfo rbinfo;
	cf_bin.ReadBin(rbinfo);
	cout << rbinfo._address << " " << rbinfo._port << " "
		<< rbinfo._date << endl;
 
	// 文本读写
	ConfigManager cf_text("test.text");
	cf_text.WriteText(winfo);
	ServerInfo rtinfo;
	cf_text.ReadText(rtinfo);
 
	cout << rtinfo._address << " " << rtinfo._port << " " <<
		rtinfo._date << endl;
 
	return 0;
}

AI助手
上述是，往文件当中，或者是从文件当中 以 二进制 和 文本的两种方式 写入 和 读取 ServerInfo 类的类对象。

在ServerInfo类当中，有三个成员，一个是 主体数据 Date 类的数据，还有 point ，和 地址。

实现也非常简单，就是实现四个函数分别是 二进制的 读写 和 文本形式的读写。

其中需要注意的点是，关于地址 adress 这个字符串，我们输入的是 ip 地址，是一个字符串，你可以发现，我们使用 一个 字符数组的形式存储的，为什么不用 string  vector 这些容器存储呢？

因为，

用这个例子就是想体现出 C++ 当中的 IO流 文件输入和输出，对于 C当中的文件输入输出函数 两者之间的对比。

很明显是 C++ 当中更加方便，我们可以发现，对于文本输入输出，在拿到 文件对象之后（fstream），如果是内置类型，和已经重载了 operator<<() 和 operator>>() 的自定义类型 都可以直接使用 流插入 和 流提取 来 从提取数据 或者 输入 数据到 文件当中，但是对于没有重载  operator<<() 和 operator>>() 的自定义类型 就不能使用了；老老实实的使用 write（）和 read（）函数吧。

但是一般来说，一个类 对于 operator<<() 和 operator>>() 函数的需求还是挺大的，这也是 C++ 要单独设计 IO流 的初衷。

还需要注意的是，不管是 C++ 当中的 fstream 的读取，还是 C 当中的 fsacnf（），他们读取文件当中的数据都是按照 空格 "\n" "EOF" 这些进行区分数据的，也就是作为本次读取 结束标志。所以，我们在 往文件当中输入 数据的时候，一定要记得对 不同的数据 要用 空格分隔开（按照上述例子当中是文件输入一样），这样，不仅仅我们可以更方便的区分数据，对于读取文件当中的数据也是非常好的。

使用 ifstream 当中的 get（）函数快速读取数据


 get（）函数可以一次读取一个字符，我们可以用一个 char 变量，传入 get（）函数，get（）当中是用 & 的方式接收的，在其中就会对这个 char 变量进行赋值，赋值成当前取出的字符。

get（）函数返回值是一个 istream对象的引用，那么我们就可以利用这个特性，也 istream 继承了 ios ，在 ios 当中重载 operator bool （）这个函数，此时就会发生，如果 在get（）返回时候 有是有 不同类型的 接收的话，就会进行 隐式类型转换。在文件当中如果没有读到 EOF结束的话，都是返回 非0 ，也就是bool 当中的 true。当访问到 EOF的话，就会返回0 ，强转为 bool 的话 0 就是 false 了。

int main()
{
	ifstream ifs("text.cpp");
	char ch;
	while (ifs.get(ch))
	{
		cout << ch;
	}
 
	return 0;
}
AI助手
此时，在屏幕上打印的就是文件当中的内容啦：



 sstream （stringstream）流介绍和使用
 因为 string  和 字符串 这些使用的频率非常高，所以，在C++ 的流当中对 字符串 也单独写了一个IO流出来：

sstream 当中的 流也是直接从 控制台流当中 直接继承过来的：



 其中的 istringstream 和 ostringstream 就分别对应了 输入 和 输出。

ostringstream 
ostringstream 就是 string 的流插入，把一个string 对象插入到 string 流当中。 

我们先来简单使用一下 ostringstream ：

#include<sstream>
 
int main()
{
	Date d1(2023, 3, 3);
	ostringstream oss;
	oss << d1;
 
	string str = oss.str();
	cout << str << endl;
 
	return 0;
}
AI助手
ostringstream 当中有一个 str 函数可以帮助我们 取出 oss 这个 ostringstream 对象当中的 string 对象存储的内容，返回值就是一个 string 对象。

像上述就是 因为 在 Date 类当中我们实现了 opeartor<<() 这个函数，所以，可以直接使用 我们实现的 ostream& operator << () 这个函数来实现 流插入，因为 ostringstream 是 ostream 的派生类，所以，oss << d1 发生了多态，oss 传参，但是 函数当中使用 ostream& 这个形式来接收的，发生向下转型，子类进行切片。

Date 当中的 ostream& operator << ()  这个函数就把 Date 当中的成员变量的数据转化为 string 返回给 一个 ，函数当中 ostream& 的这个形参，也就是现在传入的 oss 的引用。

在 Ostringstream 类的 oss 当中有一个 string对象，用于存储 接收到的 在函数当中返回的 string 对象。

所以，我们才在下面使用 str（）函数接收到 返回的 string类的对象。

其实无论是 控制台流 istream，文件流 fstream ，还是字符串流 sstream，都是把 要输出输入的数据转化成字符串来输出输入的：



 只不过在上述 函数当中的 out 形参接收的是 控制台流 istream 对象，就输出到 控制台当中，是 文件流 fstream 就输出到文件当中 ，是 字符串流 sstream 就输出到这个 ostringstream 类对象当中的string 当中存储。

后面两种之所以能接收，是因为后面两种都是第一种 控制台流 istream 的派生类，所以，当传入的 流 是后两种的时候，就会发生多态，切片。

 

istringstream
istringstream，就是 流提取，把 istringstream 当中存储的 string 对象提取出来，可以放到 一个 string 当中，也可以用其他存储，比如字符串，还可以直接输出：
 

	Date d(2023, 3, 3);
	string str("2023 3 3");
	istringstream iss(str);
	iss >> d;
	cout << d << endl;
AI助手
输出：

2023 3 3
AI助手
如上所示，我们用一个 string 构造到一个 istringstram 当中，然后把 istrigstream 当中存储的string 提取出来 放到 Date类对象 d 当中。

流提取也是和 从文件当中 提取内容是一样的，首次提取是 "2023 3 3" 这个string对象，是按照 空格 "\n" 来进行分割的。

序列化和反序列化 
其实上述的 istringstream 和 ostringstream 做的事情叫做 序列化和反序列化。

序列化就是把，日常当中使用的不同类型的值转换为 字符串（或者说是文本表示的字节流的值）。
反序列化，就是从 字符串当中提取出来，解析成 不同类型的值。
 为什么要实行上述一样的 序列化和反序列化呢？

因为 在高级语言在内存当中 变量的不同类型的值，是非常复杂的，对值的表达是非常复杂的，比如 在C++ 当中 整形 用 补码存储；浮点型分为 整形部分和 浮点数部分；bool 类型 又是 0 就是假，非零就是真；enum 又是整形常量；

而像上述举的各个例子，都是内置类型，还有在内置类型基础之上 写出 的自定义类型，甚至还有自定义类型 和 内置类型 写出 的 自定义类型。

之所以在内存当中有这么多复杂的类型存储，是因为 在内存当中的值不仅仅要描述数据，还有进行很多简单或者复杂的逻辑运算，算法支持。不同数据存储的 类型当中有什么关系，我们要这些关系来实现出什么结果，这些都是我们想要内存当中所实现的功能。而不仅仅是为了方便我们查看，如果只是为了方便我们查看的话，一个字符串类型就够我们进行查看了，因为字符串可以表示出任意的类型。

但是这是在内存当中需要进行复杂逻辑运算需要这么复杂，但是在其他地方我们可能不需要我们复杂的运算，也就不需要这么复杂的数据类型。

比如在网络传输，只是为了传输，那么只要控制好数据的传输协议，目的地址等等的信息，当要传输的数据是不需要网络层面进行逻辑运算的，只需要传输，那么就按照一个比特位基础的 一组报文，甚至还可以分成更小的组来进行传输。

又或者是在文件，数据库当中存储，只是为了方便我们查看，或者是存储数据，那么需要向内存当中这么多 的类型进行存储吗？肯定是不需要的。

但是，在其他地方流入到内存当中进行逻辑操作，又或者是内存当中进行逻辑操作之后的结果要进行存储或者是查看，这两者之间就需要进行 同一类型的转换，或者是 进行类型的解析。

这就是我们为什么要进行 序列化 和 反序列化操作的原因。 

比如下面这个例子：

struct ChatInfo
{
	string _name; // 名字
	int _id; // id
	Date _date; // 时间
	string _msg; // 聊天信息
};
int main()
{
	// 结构信息序列化为字符串
	ChatInfo winfo = { "张三", 135246, 
		{ 2022, 4, 10 }, 
		"晚上一起看电影吧"};
 
	ostringstream oss;
	oss << winfo._name << " " << winfo._id << " " << winfo._date << " "
		<< winfo._msg;
 
	string str = oss.str();
	cout << str << endl << endl;
	// 我们通过网络这个字符串发送给对象，实际开发中，信息相对更复杂，
	// 一般会选用Json、xml等方式进行更好的支持
	// 字符串解析成结构信息
	ChatInfo rInfo;
	istringstream iss(str);
	iss >> rInfo._name >> rInfo._id >> rInfo._date >> rInfo._msg;
 
 
	cout << "-------------------------------------------------------"
		<< endl;
	cout << "姓名：" << rInfo._name << "(" << rInfo._id << ") ";
	cout << rInfo._date << endl;
	cout << rInfo._name << ":>" << rInfo._msg << endl;
	cout << "-------------------------------------------------------"
		<< endl;
	return 0;
}

AI助手
stringstream
stringstream 其实就是  ostringstream 和 istringstream 的结合体，他同时具有 两个流多功能。

也就是说 stringstream 既可以进行 输出 又可以 进行输入。

 

向上述在  序列化和 反序列化 当中给出的例子使用 istringstream  和 ostringstream  实现的，那么我们就 用 stringstream 来实现一下上面的例子：
 

struct ChatInfo
{
	string _name; // 名字
	int _id;      // id
	Date _date;   // 时间
	string _msg;  // 聊天信息
};
 
int main()
{
	ChatInfo winfo = { "张三", 135246, { 2023, 10, 16 }, "晚上一起看电影吧" };
	stringstream oss;
	oss << winfo._name << " " << winfo._id << " " << winfo._date << " " << winfo._msg;
	string str = oss.str();
 
	//send(str);
	cout << str << endl;
 
	// json xml  实现更好，但是不是这篇博客的重点，所以不过多阐述
	ChatInfo rInfo;
	stringstream iss(str);
	iss >> rInfo._name >> rInfo._id >> rInfo._date >> rInfo._msg;
	cout << "-------------------------------------------------------" << endl;
	cout << "姓名：" << rInfo._name << "(" << rInfo._id << ") ";
	cout << rInfo._date << endl;
	cout << rInfo._name << ":>" << rInfo._msg << endl;
	cout << "-------------------------------------------------------" << endl;
	return 0;
}













在 C++ 中，标准输入流 (std::cin) 提供了多种不同的输入函数，常用的包括 cin, cin.get(), getline(), cin >>, cin.read() 等。这些函数在行为上有所不同，适用于不同的输入场景。

以下是一些常见的输入函数以及它们的特点和区别：

1. std::cin（流对象）
std::cin 是 C++ 标准库中的输入流对象，常用于从标准输入（通常是键盘）读取数据。它与流插入运算符（>>）结合使用来读取不同类型的数据。

代码示例：
特点：
std::cin 通过流插入运算符（>>）从输入流中提取数据。
会跳过空白字符（如空格、换行符等），这意味着它在读取字符串时，遇到空格会停止。
对于整数、浮点数等类型的输入，它会自动跳过空格并解析相应的数据。
2. std::cin.get()
cin.get() 是 C++ 输入流对象的成员函数，用于从标准输入流中读取一个字符（包括空格、换行符等）。它会读取一个字符，并将其作为返回值。cin.get() 不跳过任何字符，包括空格和换行符。

代码示例：
特点：
读取单个字符。
不跳过任何空白字符（空格、换行符等）。
使用 std::cin.get() 时，换行符 \n 也会被读取并返回，适合逐个字符地读取输入。
3. std::getline()
std::getline() 是一个用于从输入流中读取一行文本的函数。它会读取直到遇到换行符为止的所有字符，并将其存储在给定的字符串中。与 std::cin >> 不同，std::getline() 会将整个输入行（包括空格）读取到一个字符串中。

代码示例：
特点：
读取一整行，直到遇到换行符（\n）。
会读取空格，整个行会被包含在字符串中。
不会跳过换行符，因此读取后 \n 会被丢弃。
4. std::cin >>（流插入运算符）
流插入运算符 >> 用于从 std::cin 中读取数据并将其存储到指定变量中。它在输入时跳过空白字符（空格、换行符、制表符等），适用于读取常规类型（如整数、浮点数、字符串等）。

代码示例：
特点：
std::cin >> 适用于读取单个数据项。
它会跳过空白字符并读取直到下一个空白字符或换行符。
如果输入的类型与预期类型不匹配（如输入了非数字字符给整数变量），会导致输入失败。
5. std::cin.read()
std::cin.read() 用于从输入流中读取指定数量的字符，并将其存储到指定的缓冲区中。它不同于 std::cin.get()，因为它一次可以读取多个字符。

代码示例：
特点：
读取固定数量的字符（可以不以空白字符为分隔）。
一次读取多个字符，适合读取二进制数据或大量文本。
不会跳过空白字符，直接读取指定数量的字符。
6. std::cin.peek()
std::cin.peek() 用于查看下一个输入字符，而不从流中移除该字符。它返回下一个字符的值，但不改变输入流的状态。

代码示例：
特点：
查看下一个字符而不从输入流中取出。
适用于预读下一个字符，之后可以决定是否处理它。
7. std::cin.ignore()
std::cin.ignore() 用于忽略输入流中的指定数量的字符，或者忽略直到遇到特定字符为止。它常常用于跳过不需要的输入字符（如换行符）。

代码示例：
特点：
跳过输入流中的某些字符。
常用于跳过换行符或缓冲区中剩余的字符。
总结与比较
输入函数	用途	是否跳过空白字符	是否支持多字符
std::cin >>	读取单个数据项（整数、浮点数、字符串等）	是	否
std::cin.get()	读取单个字符（包括空格和换行符）	否	否
std::getline()	读取一行文本（包含空格）	否	是
std::cin.read()	读取指定数量的字符	否	是
std::cin.peek()	查看下一个字符但不从流中移除	否	否
std::cin.ignore()	忽略输入流中的字符	是	否
这些输入函数各有其适用的场景，选择合适的输入函数可以帮助你更有效地处理用户输入。


```txt
查找出现了k次的字符
 实时评测
 2024-12-31 00:00
 1000 ms
 32 MB
 苏卓 (suzhuo3@mail.sysu.edu.cn)
题目描述
给定一个ASCII字符串，查找字符串中，出现了k次的字符。比如，字符串"This is a good day!"中，出现了2次的字符为'a','d','i','o', 's'，出现了4次的字符为' '。

Input
第一行是一个正整数n(1<=n<=100)，表示下面要进行查找的字符串的数量。

其后n行，每行是一个字符串(这里确保字符串的结尾不是空格)，和一个数字k，字符串和数字k之间由一个空格隔开，字符串的长度l不超过100000，(1<=k<=l)。

Output
对于每一行输入，输出要求按照ASCII码从小到大的顺序输出字符，每个字符用单引号括起来，字符间用逗号隔开。
如果对于某行输入没有满足的字符，直接换行。

Sample Input
2
This is a good day! 2
This is a good day! 4
​
Sample Output
'a','d','i','o','s'
' '


```

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    cin.ignore(); //

    while (n--) {

        unordered_map<char, int> umap;

        char ch;
        while(cin.get(ch)){
            if(isspace(ch) && isdigit(cin.peek())) //
                break;
            umap[ch]++;
            //cout << "ch: " << ch << "  i: " << umap[ch] << endl;
        }
        
        int op;
        cin >> op;

        vector<char> v;
        for (const auto& i : umap) {
            if (i.second == op) {
                v.push_back(i.first);
            }
        }

        if (!v.empty()) {
            sort(v.begin(), v.end());  
            for (size_t i = 0; i < v.size() - 1; i++) {
                cout << "'" << v[i] << "',";
            }
            cout << "'" << v[v.size() - 1] << "'" << endl;
        }
        cout << endl;

        cin.ignore();
    }

    return 0;
}

```

有问题，改正

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    
    cin.ignore();

    while(n--){
        vector<int> v(96);

        char ch;
        int op;
        while(cin.get(ch)){
            if(isspace(ch) && isdigit(cin.peek()))
                break;
            v[ch - ' ']++;
        }

        cin >> op;

        vector<pair<int, char>> v1;

        for(size_t i = 0; i < v.size(); i++){
            if(v[i]){
                v1.push_back({v[i], ' ' + i});
            }
        }

        sort(v1.begin(), v1.end(), [](const pair<int, char>& a, const pair<int, char>& b){
            if(a.first != b.first)
                return a.first < b.first;
            else 
                return a.second < b.second;
        });

        auto it = equal_range(v1.begin(), v1.end(), [&](const pair<int, char>& a){
            return a.first == op;
        });

        auto i = it.first;
        for(; i + 1 != it.second; i++){
            cout << "'" << (*i).second << "'" << ",";
        }
        cout << "'" << (*i).second << "'" << ",";
        cout << endl;

        cin.ignore();
    }

    return 0;
}
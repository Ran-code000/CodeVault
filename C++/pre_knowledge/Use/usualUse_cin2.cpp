# include <iostream>
using namespace std ;

int main()
{
    const int SIZE = 20;
    char buf[SIZE];

    cin.ignore(7);
    //cin.ignore(); 
    // 忽略换行符，以便后续getline正常工作
    cin.getline(buf,10); 
    //输入遇到换行符 '\n' 为止，丢弃换行符
    //与字符数组一起使用时，需指定数组大小，以防缓冲区溢出

    //cin.read(buf,20); 
    //达到指定数量,不在读取到换行符时停止，也不会丢弃换行符
    //输入流中没有足够的字符，它将导致输入流进入错误状态
    cout << "字符串收集到的字符数:" << cin.gcount() << endl;
    //cout.write(buf,20); 
 
    cout << buf << endl;
    return 0;
}
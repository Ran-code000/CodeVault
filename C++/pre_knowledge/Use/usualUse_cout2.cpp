# include <iostream>
# include <iomanip>

using namespace std ;

int main()
{
    int width = 4;
    char str[20];

    cin.width(5);
    //读取的宽度为5，cin在下一次读取至多4个字符
    //第5个位置添加字符串结束符\0

    while( cin >> str )
    {
        //cout.width(width++);
        
        cout << setw(width++) << setfill('*') << endl;
        //这个宽度设置只对紧接着的下一次输出有效
        cout << str << endl;
        cin.width(5);
        
    }
    return 0;
}
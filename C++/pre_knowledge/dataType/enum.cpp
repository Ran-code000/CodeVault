# include <iostream>

enum weekdays{ Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday};

int main()
{
    weekdays today;

    today = Saturday;
    std::cout << today << std::endl;

    today = Monday;
    std::cout << today << std::endl;

    /*switch (today)
    {
        case Monday:
        ......
    }  enum常与switch case 搭配使用，case后不能用字符串但可以用enum定义后的量 */

    return 0;
}
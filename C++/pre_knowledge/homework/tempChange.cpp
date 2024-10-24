# include <iostream>
# include <limits>

using namespace std;

/*运用到函数的重载*/

void convertTemperature( double tempIn , char typeIn )
{
    const unsigned short ADD_SUBTRACT = 32;
    const double RATIO = 9.0 / 5.0;
    double tempOut;
    char typeOut;

    switch ( typeIn )
    {
        case 'C':
        case 'c':
            tempOut = tempIn * RATIO + ADD_SUBTRACT;
            typeOut = 'F';
            break;
        case 'F':
        case 'f':
            tempOut = tempIn - ADD_SUBTRACT / RATIO;
            typeOut = 'C';
            break;
        default:
            typeOut = 'E';
            break;
    }

    if( typeOut != 'E' )
    {
        cout << tempIn << typeIn << " = " << tempOut << typeOut << endl;
    }else
    {
        cout << "输入错误" << endl;
    }

    cout << "请输入任何字符结束程序!" << endl;
    cin.get();
}

void convertTemperature( int tempInint , char typeIn )
{
    const unsigned short ADD_SUBTRACT = 32;
    const double RATIO = 9.0 / 5.0;
    int tempOut;
    char typeOut;

    switch ( typeIn )
    {
        case 'C':
        case 'c':
            tempOut = tempInint * RATIO + ADD_SUBTRACT;
            typeOut = 'F';
            break;
        case 'F':
        case 'f':
            tempOut = tempInint - ADD_SUBTRACT / RATIO;
            typeOut = 'C';
            break;
        default:
            typeOut = 'E';
            break;
    }

    if( typeOut != 'E' )
    {
        cout << tempInint << typeIn << " = " << tempOut << typeOut << endl;
    }else
    {
        cout << "输入错误" << endl;
    }

    cout << "请输入任何字符结束程序!" << endl;
    cin.get();
}

int main()
{
    double tempIn;
    int tempInint;
    char typeIn;

    cout << "请以【xx.x C】/【xx.x F】的格式输入字符 : ";
    cin >> tempIn >> typeIn;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    convertTemperature( tempIn , typeIn );

    cout << "请以【xx C】/【xx F】的格式输入字符 : ";
    cin >> tempInint >> typeIn;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    convertTemperature( tempInint , typeIn );

    return 0;
}
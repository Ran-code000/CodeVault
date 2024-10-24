# include <iostream>
# include <fstream>
# include <string>
# include <cctype>
# include <limits>

class Storyquote
{
public:
    std::string quote,speaker;
    std::ifstream infile;
    std::ofstream outfile;

    Storyquote(void);
    ~Storyquote(void);

    bool inputquote(void);
    bool inputspeaker(void);
    bool readfile(void);
    bool writequote(void);
    void clearfile(void);

};

const std::string filename = "quote.txt";

Storyquote::Storyquote(void):infile(filename),outfile(filename,std::ios::app)
{
    if(!outfile)
    {
        std::cerr << "无法打开文件进行追加" << std::endl;
    }
}

Storyquote::~Storyquote(void)
{
    outfile.close();
}

bool validinput(std::string &information);

bool Storyquote:: inputquote(void)
{
    return validinput(quote);
}

bool Storyquote::inputspeaker(void)
{
    return validinput(speaker);
}

bool validinput(std::string &information)
{
    std::getline(std::cin,information);

    if(information.empty())
    {
        std::cout << "输入的信息不能为空" << std::endl;
        return false;
    }else if(std::cin.eof())
    {
        std::cerr << "处理文件结束或没有更多输入" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        return false;
    }else if(std::cin.fail())
    {
        std::cerr << "其他原因失败(如输入类型不匹配)" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        return false;
    }

    return true;
}

bool Storyquote::readfile(void)
{
    if(infile.is_open())
    {
        infile.close();
    }
    infile.open(filename);
    infile.clear();
    infile.seekg(0);

    if(!infile)
    {
        std::cerr << "无法成功打开并读取文件" << std::endl;

        return false;
    }

    std::string line;

    while(std::getline(infile,line))
    {
        std::cout << line <<std::endl;
    }
    
    infile.close();

    return true;
}

bool Storyquote::writequote(void)
{
    std::cout << "请输入一句名言 : ";
    bool result1 = inputquote();

    std::cout << "请输入该名言的作者 : ";
    bool result2 = inputspeaker();

    if( result1 && result2 )
    {
        std::cout << "成功录入信息!!" << std::endl;
    }else
    {
        std::cerr << "录入信息失败!!";

        return false;
    }

    std::cout << "请问是否需要保存文件(Y/N)" << std::endl;

    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    if( toupper(choice) == 'N')
    {
        return false;
    }else if( toupper(choice) == 'Y')
    {
        if(!outfile)
        {
            std::cerr << "文件无法正常打开并保存!" << std::endl;
            return false;
        }else
        {
            outfile << "名言 : " << quote << "作者 : " << speaker << std::endl;
            outfile.close();
            return true;
        }
    }else
    {
        std::cout << "输入不合法，请输入(Y/N)" << std::endl;
        return false;
    }
    
}

void Storyquote::clearfile(void)
{
    if(outfile.is_open())
    {
        outfile.close();
    } 

    std::ofstream clearOutfile(filename,std::ios::trunc);

    if(!(clearOutfile.is_open()))
    {
        std::cerr << "无法成功打开文件并清空" << std::endl;
    }
    clearOutfile.close();
}

int main()
{
    Storyquote quote;
    int number;
    char choice;

    while(true)
    {
        std::cout << "请选择输入1234 : \n" << "1.读取文件\n" << "2.写入文件\n" << "3.清空文件\n" << "4.结束程序\n";

        while(!(std::cin >> number))
        {
            std::cerr << "请输入有效的数字" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
           // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        switch (number)
        {
            case 1:
                if(quote.readfile())
                {
                    std::cout << "读取文件成功" << std::endl;
                }else{
                
                    std::cout << "读取文件失败" << std::endl;
                }
                break;
            case 2:
                while(true)
                {
                    if(quote.writequote())
                    {
                        std::cout << "写入文件成功" << std::endl;
                    }else
                    {
                        std::cout << "写入文件失败" << std::endl;
                    }

                    std::cout << "是否继续写入信息(Y/N)" ;
                    std::cin >> choice;
                    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

                    if( toupper(static_cast<unsigned char>(choice)) == 'N')
                    {
                        break;
                    }
                };
                break;
            case 3:
                quote.clearfile();
                break;
            case 4:
                return 0;
        }

        std::cout << "是否继续(Y/N)" ;
        std::cin >> choice;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        if( toupper(static_cast<unsigned char>(choice)) == 'N')
        {
            break;
        }else if( toupper(static_cast<unsigned char>(choice)) == 'Y')
        {
            continue;
        }else
        {
            std::cout << "输入不合法，请输入(Y/N)" << std::endl;
        }
    }
    

    return 0;
}

/*    
1.std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
可能需要在以下情况下使用这段代码:
a.当你先读取了一个值（如整数、浮点数或字符），然后打算读取一行文本时。如果不忽略留在输入缓冲区中的换行符，
下一个读取行的操作（如 std::getline(std::cin, line);）将会立即读取到这个换行符并认为是空行，结果就是你得到的字符串会是空的。

b.当你要清除之前的输入错误或非预期的输入时。例如，如果用户输入了非法的数据，你可能希望在提示用户重新输入之前清除输入流。

并非每次使用 std::cin >> value; 后都需要 std::cin.ignore()。
如果接下来的读取操作也是用 std::cin >> anotherValue; 这样的格式读取单个值，通常不需要忽略换行符，
因为 std::cin 会跳过任何的空白字符（空格、换行等），直到找到下一个有效的值。

总结起来，std::cin.ignore() 主要是用来处理混合读取单个值和字符串的情况，或者当输入流中可能存在异常数据需要被清除时。
*/
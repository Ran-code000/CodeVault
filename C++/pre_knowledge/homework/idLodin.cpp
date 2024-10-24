# include <iostream>
# include <fstream>
# include <string>
# include <windows.h>
# include <limits>

struct Identity
{
    std::string name;
    std::string id;
    char sex;

}identity;

const std::string filename = "identity.txt";

bool Initinformation()
{
    std::ifstream infile(filename);
    return infile.good();
}

bool Readinformation()
{
    std::ifstream infile(filename);

    if(!infile)
    {
        std::cerr << "无法打开文件进行读取";
        return false;
    }

    infile.seekg(0);
    
    std::string line;
    while(getline(infile,line))
    {
        std::cout << line << std::endl;
    }

    return true;
}

bool Recordinformation()
{

    while(1)
    {
        std::cout << "请输入姓名 : ";
        std::cin >> identity.name;

        std::cout << "请输入账号 : ";
        std::cin >> identity.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        while(1)
        {
            std::cout << "请输入性别 (F指女性,M指男性) : ";
            std::cin >> identity.sex;
            if(toupper(identity.sex) == 'F'|| toupper(identity.sex) == 'M')
            {
                break;
            }else
            {
                std::cerr << "输入错误！！请按要求输入" << std::endl;
            }

        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "信息录入成功，请问是否需要保存(是填Y,否填N) : ";

        char choice;
        std::cin >> choice;
        
        if( toupper(choice) == 'Y')
        {
            std::ofstream outfile(filename,std::ios::app);

            if(!outfile)
            {
                std::cerr << "无法打开文件进行写入";
                return false;

            }

            outfile << "姓名 : " << identity.name << " 账号 : " << identity.id << " 性别 : " << identity.sex << std::endl;

            outfile.close();
            std::cout << "信息已成功保存" << std::endl;

        }else if( toupper(choice == 'N') )
        {
            std::cout << "信息保存失败" << std::endl;
        }else
        {
            std::cerr << "未知的命令，信息未保存" << std::endl;
        }

        std::cout << "是否需要录入新的信息(是填Y,否填N) : " << std::endl;

        std::cin >> choice;

        if( toupper(choice) == 'N') break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    }

    return true;
   
}

void Clearinformation()
{
    std::ofstream outfile(filename,std::ios::trunc);

}

int main()
{
    int number;

    if(Initinformation())
    {
        std::cout << "文件初始化完成" << std::endl;
    }else
    {
        std::cerr << "文件初始化失败" << std::endl;
        return 1;
    };

    while(1)
    {
        std::cout << "请选择需要进行的操作 : " << std::endl 
        << "1.打印数据到屏幕" << std::endl 
        << "2.录入数据" << std::endl 
        << "3.清空文件" << std::endl
        << "4.退出程序" << std::endl;

        
        while(std::cin >> number)
        {
            if(std::cin.fail())
            {
                std::cout << "请输入合法的数字(1或2或3)!!!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max() ,'\n');
            }else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max() ,'\n');
                break;
            }
        }
        

        switch (number)
        {
            case 1 :
                if( Readinformation())
                {
                    std::cout << "成功读取文件" << std::endl;
                }else
                {
                    std::cerr << "读取文件失败" << std::endl;
                };
                break;
            case 2 : 
                Recordinformation();
                break;
            case 3 :
                Clearinformation();
                break;
            case 4 : 
                return 0;

        }
    }   
    std::cerr << "初始化失败" << std::endl;

    return 0;

}
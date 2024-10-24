# include <iostream>
# include <string>
# include <cctype>

bool isAlpha(const std::string& str)
{
    for(char const &c:str)
    {
        if( std::isalpha(c) == 0 )
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::string str;
    std::cout << "Enter a word : ";
    std::cin >> str;

    if(isAlpha(str))
    {
        std::cout << "You entered a valid words" << std::endl;
    }else
    {
        std::cout << "Not valid ! Not a words ! " << std::endl;
    }
    
    return 0;
}

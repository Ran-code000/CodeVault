# include <iostream>
# include <cctype>
# include <string>

bool isNumber( const std::string& str )
{
    for( char const &c : str )
    {
         if(std::isdigit(c)==0)
         {
            return false;
         }

    }
    return true;
}

int main()
{
    std::string input;
    std::cout << "Enter a number : ";
    std::cin >> input;

    if(isNumber(input))
    {
        std::cout << "You entered a valid number !" << std::endl;
    }else
    {
        std::cout << "Not valid ! Not a number ! " << std::endl;
    }

    return 0;

}
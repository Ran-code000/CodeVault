# include <iostream>
# include <limits>

/*cin特殊的输入检查机制的运用*/

int main()
{
    const unsigned short ITEM = 10;
    int arr[ITEM];
    int sum = 0;

    std::cout << "请输入" << ITEM << "个数字" << std::endl; 

    for(int i = 0 ; i < ITEM ; i++)
    {
        std::cout << "请输入第" << i+1 << "个数字: ";

        //cin特殊的输入检查机制的运用
        //std::cin >> arr[i];
        
        while(!(std::cin >> arr[i]))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "请输入一个合法的值" << std::endl;
        }

        sum+=arr[i];

    }
    std::cout << "这些数字的和为 : " << sum << std::endl;
    std::cout << "这些数字的平均值为 : " << (double) sum/10 << std::endl;

    return 0;
    
}
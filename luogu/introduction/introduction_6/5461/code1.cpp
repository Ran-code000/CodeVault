#include <iostream>
#include <vector>

//用递归来做

void pardonCheaters(std::vector<std::vector<int>> &matrix,int x,int y,int size)
{
    if( size == 1)
    {
        matrix[0][0] = 0;
        return ;
    }

    int newSize = size/2;

    for( int i = x; i < x + newSize ; i++)
    {
        for( int j = y; j < y + newSize ; j++)
        {
            matrix[i][j] = 0;
        }
    }

    pardonCheaters( matrix , x + newSize , y , newSize);
    pardonCheaters( matrix , x , y + newSize , newSize);
    pardonCheaters( matrix , x + newSize , y + newSize , newSize);
}

void printMatrix(const std::vector<std::vector<int>> &matrix)
{
    for(const auto&row : matrix)
    {
        for(int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    int n;
    std::cin >> n;

    int size;
    size = 1 << n;

    std::vector<std::vector<int>> matrix(size,std::vector<int>(size,1));
    //二维数组

    pardonCheaters(matrix,0,0,size);

    printMatrix(matrix);
    
    return 0;
}

/*
在 C++ 中，std::vector 是一个序列容器，可以动态地存储元素，自动管理存储空间的分配和扩展。

vector 本质上就是一个可以动态增长的数组。

1.实现一个数组

#include <iostream>
#include <vector>

int main() 
{
    // 创建一个vector，初始包含5个元素，每个元素都是0
    std::vector<int> array(5, 0);

    // 初始化vector的元素
    for (int i = 0; i < array.size(); ++i) 
    {
        array[i] = i * i; // 存储平方数
    }

    // 打印vector的元素
    for (int i = 0; i < array.size(); ++i) 
    {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

2.实现一个矩阵!!!
要使用 vector 实现一个矩阵，你可以创建一个 vector 的 vector。
这就是说，你的外层 vector 将包含多个 vector，每个内层的 vector 代表矩阵的一行。


#include <iostream>
#include <vector>

int main() 
{
    // 创建一个3x4的矩阵，初始值为0
    // 这意味着有3个内部向量，每个内部向量包含4个元素
    std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));

    // 填充矩阵
    for (int i = 0; i < matrix.size(); ++i) 
    { // 遍历行
        for (int j = 0; j < matrix[i].size(); ++j) 
        { // 遍历列
            matrix[i][j] = i * j; // 以行索引和列索引的乘积来赋值
        }
    }

    // 打印矩阵
    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int j = 0; j < matrix[i].size(); ++j) 
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
这段代码会创建一个3行4列的矩阵，并打印出来。注意，所有的操作都是通过 vector 的接口进行的，
比如使用 size() 方法来获取行数和列数，使用下标操作符 [] 来访问元素。
这使得动态管理和操作这些数据结构变得非常简单和直观。

std::vector 是一种非常灵活的数据结构，它提供了很多内置的方法来管理动态数组，如插入、删除、遍历和访问元素等。
它的内存管理是自动的，因此你不需要担心内存分配和释放的问题，这是 std::vector 相对于原始数组的一个重要优势。*/
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> vec(n, std::vector<int> (n, 0));

    int size = (int)std::pow(n, 2);

    int i = 0, j = n / 2;
    vec[i][j] = 1;

    //注意操作矩阵的方法，(i + 1 + n) % n 类似的表达式常被用来解决数组越界问题，它能够实现数组的环形遍历
    //不可将 else if 改为 if
    for(int k = 2; k <= size; k++)
    {
        if(i == 0 && j != n - 1)
        {
            i = n - 1;
            j++;
        }else if(i != 0 && j == n - 1)
        {
            i = (i - 1 + n) % n;
            j = 0;
        }else if(i != 0 && j != n - 1)
        {
            if(!vec[i - 1][j + 1])
            {
                i = (i - 1 + n) % n;
                j = (j + 1 + n) % n;
            }else
            {
                i = (i + 1 + n) % n;
            }
        }else if(i == 0 && j == n - 1)
        {
            i = (i + 1 + n) % n;
        }
        
        vec[i][j] = k;
    }


    for(const auto &row : vec)
    {
        for(int val : row)
        {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    //若将 else if 更改为 if，每个条件判断都是独立的，这意味着一个循环迭代中可能会有多个条件被评估为真，并且执行多个代码块。这样会导致 i 和 j 被不正确地更新多次，破坏了算法的逻辑，从而产生错误的结果
    /*
数组越界问题的解决方法

(i + 1 + n) % n 类似的表达式常被用来解决数组越界问题，它能够实现数组的环形遍历。
这种技巧不仅适用于魔方阵的生成，还有多种情况下的应用，如：

1. 环形数组的遍历：
在处理环形结构，如循环队列、循环缓冲区时，经常使用模运算来实现索引的环绕。

int arr[] = {0, 1, 2, 3, 4};
int n = sizeof(arr) / sizeof(arr[0]);
int start = 3; // 假设从索引3开始遍历
for(int i = 0; i < n; ++i) {
    std::cout << arr[(start + i) % n] << " ";
}

2. 在矩阵中模拟方向移动：
在处理游戏开发或模拟问题时，可能需要模拟实体在二维空间中的上下左右移动，而这个空间可能是“环形”的。

// 假设有一个环形的二维网格，尝试向上移动一格
int x = 5, y = 5; // 当前位置
int dx[4] = {0, 0, -1, 1}; // 方向数组，对应上下左右
int dy[4] = {-1, 1, 0, 0};
int gridSize = 10; // 网格大小
// 向上移动
x = (x + dx[0] + gridSize) % gridSize;
y = (y + dy[0] + gridSize) % gridSize;

3. 处理字符串的环形模式：
当处理字符串时，尤其是在查找子字符串或实现某种循环移位操作时，也可能使用类似的技术。

std::string s = "hello";
int shift = 2; // 向右移动2位
std::string result;
for(int i = 0; i < s.length(); ++i) {
    result += s[(i - shift + s.length()) % s.length()];
}
std::cout << result << std::endl; // "lohel"
*/
    
    
    return 0;
}
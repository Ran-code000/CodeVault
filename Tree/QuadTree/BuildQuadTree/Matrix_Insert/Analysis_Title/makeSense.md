# 四叉树的简单构建(基础方法 + 优化方法) + 例题精讲

## 方法一：递归(自底向上) better

首先判定这一部分是否均为 0 或 1，

（1）如果是 1，这一部分对应的是一个叶节点，构造出对应的叶节点并结束递归；

（2）如果是 0，这一部分对应的是一个非叶节点，需要将其分成四个部分 
​
递归地调用 dfs 函数得到四个部分对应的树，再将它们对应地挂在非叶节点的四个子节点上

```cpp
/*
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
*/
Node *construct(vector<vector<int>> &grid) {
    Node* construct(vector<vector<int>>& grid) {
    // dfs 函数定义：通过传入的行列范围进行递归
    function<Node*(int, int, int, int)> dfs = [&](int rowMin, int colMin, int rowMax, int colMax) -> Node* {
        bool isLeaf = true;
        int firstValue = grid[rowMin][colMin]; // 选取矩阵的第一个元素
        
        //判断是否是叶节点
        for (int i = rowMin; i < rowMax && isLeaf; ++i) 
            for (int j = colMin; j < colMax && isLeaf; ++j) 
                if (grid[i][j] != firstValue) 
                    isLeaf = false; // 如果发现有不同的元素，标记不是叶节点
        
        // 如果是叶节点，直接返回一个叶节点
        if (isLeaf) 
            return new Node(firstValue, true);
        // 如果不是叶节点，递归地分割区域并构建四个子节点
        else
        {
            
            int rowMid = (rowMin + rowMax) / 2;
            int colMid = (colMin + colMax) / 2;
            return new Node(
                true, 
                false,
                dfs(rowMin, colMin, rowMid, colMid),     // 左上角子矩阵
                dfs(rowMin, colMid, rowMid, colMax),     // 右上角子矩阵
                dfs(rowMid, colMin, rowMax, colMid),     // 左下角子矩阵
                dfs(rowMid, colMid, rowMax, colMax)      // 右下角子矩阵
            );
        }  
    };

    // 调用 dfs 函数，初始化分割的矩阵范围
    return dfs(0, 0, grid.size(), grid[0].size());
    }
}
```

### 对lamba表达式部分有另一种写法

```cpp
Node* construct(vector<vector<int>>& grid) {
    auto dfs = [&](auto self, int rowMin, int colMin, int rowMax, int colMax) -> Node*{
    
    ......
    self(self, rowMin, colMin, (rowMin + rowMax) / 2, (colMin + colMax) / 2),
    .......
   
};
return dfs(dfs, 0, 0, grid.size(), grid.size());
}
```

- [lambda表达式用法见附录](#附录)

## 方法二：递归 + 二维前缀和优化 good(对本题优化效果一般但是是一个优化的思路)

当某一部分均为 0 时，它的和为 0；
某一部分均为 1 时，它的和为这一部分的面积大小。

因此我们可以使用二维前缀和（参考「304. 二维区域和检索 - 矩阵不可变」）进行优化。

当我们需要判定某一部分是否均为 0 或 1 时，可以在 O(1) 的时间内得到这一部分的和，从而快速地进行判断。

```cpp
/*
class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}
*/
Node *construct(vector<vector<int>> &grid) {
    int n = grid.size();

    //创建一个大小为 (n + 1) x (n + 1) 的前缀和数组 pre，用于存储子矩阵的和。
    //为什么这里多一个维度呢？见代码后的片段解析
    vector<vector<int>> pre(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + grid[i - 1][j - 1];
        }
    }

    //Lambda 表达式 getSum，用于计算 grid 中任意矩形区域的和。它接受四个参数，表示区域的边界，并利用之前构建的前缀和数组快速计算区域和
    auto getSum = [&](int rowMin, int colMin, int rowMax, int colMax) {
        return pre[rowMax][colMax] - pre[rowMax][colMin] - pre[rowMin][colMax] + pre[rowMin][colMin];
    };

    //定义了一个 Lambda 表达式 dfs，用于深度优先搜索（DFS）构建四叉树。self 是用于递归调用自身的参数，后面的参数表示当前处理的矩形区域的边界
    auto dfs = [&](auto self, int rowMin, int colMin, int rowMax, int colMax) -> Node*{
        //调用 getSum 计算当前矩形区域的元素总和，并将结果存储在 total 中
        int total = getSum(rowMin, colMin, rowMax, colMax);

        //叶子节点的情况
        //如果当前区域的总和为 0
        if (totafl == 0) {
            return new Node(false, true);
        }
        //如果当前区域的总和等于该区域的面积，说明该区域全为 1
        if (total == (rowMax - rowMin) * (colMax - colMin)) {
            return new Node(true, true);
        }

        //非叶子节点的情况
        //如果当前区域既不是全 0 也不是全 1，说明它包含混合的值，因此创建一个新的非叶子节点。这个节点的子节点是通过递归调用 dfs 函数构建的
        int rowMid = (rowMin + rowMax) / 2;
        int colMid = (colMin + colMax) / 2;
        return new Node(
            //第一个参数 true 表示这个节点是一个内部节点；
            true,
            //第二个参数 false 表示该节点不是叶子节点
            false,
            self(self, rowMin, colMin, rowMid, colMid),     // 左上角子矩阵
            self(self, rowMin, colMid, rowMid, colMax),     // 右上角子矩阵
            self(self, rowMid, colMin, rowMax, colMid),     // 左下角子矩阵
            self(self, rowMid, colMid, rowMax, colMax)      // 右下角子矩阵
        );
    };

    return dfs(dfs, 0, 0, n, n);
}
```


### 前缀和算法

前缀和数组：

首先，我们构建一个前缀和数组，这使得能够在 **O(1)** 时间内计算任意子矩形区域的和(**相比与每次直接循环遍历时间复杂度降低**)

### 片段解析

`pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + grid[i - 1][j - 1];`

例如：

```cpp
grid = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]
```

我们想计算 pre[2][2]（即从 (1, 1) 到 (2, 2) 的矩阵区域和）。按照公式计算：

pre[2][2] = pre[1][2] + pre[2][1] - pre[1][1] + grid[1][1]

其中：

pre[1][2] = 1 + 2 = 3

pre[2][1] = 1 + 4 = 5

pre[1][1] = 1

grid[1][1] = 5

为什么

pre[1][1] = 1； grid[1][1] = 5

because

`vector<vector<int>> pre(n + 1, vector<int>(n + 1));`: 

**pre 数组下标从 1 开始，grid 数组下标从0 开始** 


## 改版错误解释

***旧版错误解释***

### 省留版

*无需使用动态规划优化这段构造四叉树的代码，因为每个递归子问题都是唯一且独立的，没有重叠计算。*

### 详细解释

#### 其实在旧版中的动态规划方法是起不到优化作用的（半夜灵光一现）

因为我们构造四叉树的代码的**工作原理**是

    1. dfs 函数被定义为一个 lambda 函数，接受当前处理的子矩阵的行和列的最小值与最大值 (rowMin, colMin, rowMax, colMax)

    2. 检查当前子矩阵是否为叶节点（即所有元素是否相同）

    3. 如果是叶节点，返回一个新的叶节点。

    4. 如果不是叶节点，递归地将当前子矩阵划分为四个子矩阵，并为每个子矩阵构建相应的子节点。

这种递归过程确保 ***每个子矩阵只被处理一次*** ，因为每个划分步骤都会 ***将矩阵分成不重叠的四个部分***。

#### 本质上这种划分方式类似于 ***分治算法***，每个子问题（子矩阵）都是独立的，没有重叠或共享部分。

而谈到动态规划：

#### 为什么不需要动态规划

**动态规划**主要用于解决具有**重叠子问题**和**最优子结构**的问题。

在此代码中：

（1）***重叠子问题***：每个子矩阵在递归过程中只被访问和处理一次，没有重复处理相同的子矩阵。因此，没有需要通过存储中间结果来避免重复计算的情况。

（2）***最优子结构***：虽然递归过程本身具有最优子结构的性质（即可以通过子问题的解决方案构建整个问题的解决方案），但由于没有重叠子问题，动态规划的主要优势（避免重复计算）并不适用。

（ps: 此后我会写一章比较学习分治算法和动态规划的博客来重点探究这个问题）
<!-- ## 方法三：动态规划优化 best ！！！！！！！！！

```cpp
Node* construct(vector<vector<int>>& grid) {
    int n = grid.size();
    
    // 用来缓存子矩阵是否为叶节点的结果
    vector<vector<int>> memo(n, vector<int>(n, -1)); 
    // -1 表示未计算，1 表示是叶节点，0 表示不是叶节点需要分裂
    
    function<Node*(int, int, int, int)> dfs = [&](int rowMin, int colMin, int rowMax, int colMax) -> Node* {
        // 如果这个子矩阵已经计算过了，直接返回缓存的结果
        if (memo[rowMin][colMin] != -1) 
            return memo[rowMin][colMin] == 1 ? new Node(grid[rowMin][colMin], true) : nullptr;
        
        
        bool isLeaf = true;
        int firstValue = grid[rowMin][colMin];
        
        // 遍历当前子矩阵，检查是否所有元素相同
        for (int i = rowMin; i < rowMax && isLeaf; ++i)
            for (int j = colMin; j < colMax && isLeaf; ++j) 
                if (grid[i][j] != firstValue) 
                    isLeaf = false;
        

        if (isLeaf) {
            memo[rowMin][colMin] = 1;  // 记住这个子矩阵是叶节点
            return new Node(firstValue, true);
        }else
        {
            return new Node(
            //第一个参数 true 表示这个节点是一个内部节点；
            true,
            //第二个参数 false 表示该节点不是叶子节点
            false,
            dfs(rowMin, colMin, (rowMin + rowMax) / 2, (colMin + colMax) / 2),
            dfs(rowMin, (colMin + colMax) / 2, (rowMin + rowMax) / 2, colMax),
            dfs((rowMin + rowMax) / 2, colMin, rowMax, (colMin + colMax) / 2),
            dfs((rowMin + rowMax) / 2, (colMin + colMax) / 2, rowMax, colMax)
            );
            // 如果是非叶节点，缓存其状态
            memo[rowMin][colMin] = 0;

        }
        
    };

    return dfs(0, 0, n, n);
}
```

### 代码详解Q&A

` memo[rowMin][colMin] = 0; `

#### 1.为什么 `memo[rowMin][colMin] = 0;` 标记当前节点的状态要放到递归调用的后面？

因为只有在所有子节点（所有的状态）都计算完成后，这一标记才是有意义的。

假设矩阵为

```cpp
int matrix[4][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1}
};
```

假设的调用流程：

（1）dfs(0, 0, 4, 4) 被调用。 
    这个范围不是叶子节点，
    接下来会调用：

（2）dfs(0, 0, 2, 2) 处理左上象限。

（3）dfs(0, 2, 2, 4) 处理右上象限。

（4）dfs(2, 0, 4, 2) 处理左下象限。

（5）dfs(2, 2, 4, 4) 处理右下象限。

但由于此时已经标记 `memo[rowMin][colMin] = 0;` ，

那么就会在递归调用子矩阵 ` dfs(rowMin, colMin, (rowMin + rowMax) / 2, (colMin + colMax) / 2),`的时候

遇到```if (memo[rowMin][colMin] != -1) return memo[rowMin][colMin] == 1 ? new Node(grid[rowMin][colMin], true) : nullptr;```，

命中缓存从而返回 nullptr（表示已处理故返回完整的内部节点），

但实际上内部并没有处理完整：

右上角区域 `{{1，1}，{1， 0}} ` 应该再执行一次递归调用，但此时已经结束了右上角区域的递归调用了

```cpp
int matrix[4][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1}
};
```

#### 2. ` memo[rowMin][colMin] `为什么标记用rowmin和colmin?

唯一性：

通过使用 rowMin 和 colMin 作为索引，我们能够唯一标识一个特定的**子矩阵**
（注意是唯一的**子矩阵**，因为父矩阵也就是父节点也就是非叶子节点，是在所有的子矩阵也就是子节点也就是叶子节点构建完毕后才构建，所以不会出现唯一性冲突）

如

```cpp
memo[0][0]  // 表示子矩阵 A
memo[0][2]  // 表示子矩阵 B
memo[2][0]  // 表示子矩阵 C
memo[2][2]  // 表示子矩阵 D
``` -->

---

## 例题详解

例题来源 [力扣 四叉树交集](https://leetcode.cn/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/description/)

***注意：四叉树求交集 ———> 用逻辑或运算***

```cpp
Node *intersect(Node *quadTree1, Node *quadTree2)
{   
    //如果 quadTree1 是叶节点，那么它要么是一个全 true 的区域，要么是一个全 false 的区域
    if (quadTree1->isLeaf)
    {   
        //如果 quadTree1 是叶节点且其值为 true（表示该区域全为 true）
        //则交集结果也应该是全 true 的区域。因此，返回一个新的叶节点，值为 true，并且标记为叶节点
        if (quadTree1->val)
            return new Node(true, true);
        //如果 quadTree1 是叶节点且其值为 false（表示该区域全为 false）
        //则交集结果完全取决于 quadTree2。此时，返回 quadTree2 本身的结构，作为交集的结果（因为 false 与任何值的交集仍然是 false）
        else 
            return new Node(quadTree2->val, quadTree2->isLeaf, quadTree2->topLeft, quadTree2->topRight, quadTree2->bottomLeft, quadTree2->bottomRight);
    }
    //如果 quadTree1 不是叶节点（即它有子节点），但 quadTree2 是叶节点，
    //那么通过交换 quadTree1 和 quadTree2，递归调用交集函数。
    //这个交换操作是为了简化处理，因为我们总是先处理叶节点
    else if (quadTree2->isLeaf)
    {
        return intersect(quadTree2, quadTree1);
    }
    else
    {
        //递归地计算 quadTree1 和 quadTree2 的四个子区域的交集
        Node *o1 = intersect(quadTree1->topLeft, quadTree2->topLeft); //左上
        Node *o2 = intersect(quadTree1->topRight, quadTree2->topRight); //右上
        Node *o3 = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft); //左下
        Node *o4 = intersect(quadTree1->bottomRight, quadTree2->bottomRight); //右下
        
        //判断四个子树的交集是否都可以合并为一个叶节点

        //如果所有子树值相同，返回一个新的叶节点
        if (o1->isLeaf && o2->isLeaf && o3->isLeaf && o4->isLeaf && o1->val == o2->val && o1->val == o3->val && o1->val == o4->val)
            return new Node(o1->val, true);
        //如果四个子树的交集不能合并为一个叶节点，
        //则返回一个新的四叉树节点，值为 false，且该节点不是叶节点。新的四叉树节点有四个子节点：o1、o2、o3 和 o4，它们分别是交集的四个子树
        else
            return new Node(false, false, o1, o2, o3, o4);
    }
}
```

## 附录

### Lambda 表达式的基本语法

` [capture](parameters) -> return_type { body }; `

#### capture（捕获列表）

指定外部变量的捕获方式，可以是

[]：不捕获任何外部变量。
[&]：按引用捕获外部作用域的所有变量。
[=]：按值捕获外部作用域的所有变量。
[x]：按值捕获变量 x。
[&x]：按引用捕获变量 x

可以混合使用，例如 [=, &x]：按值捕获所有变量，但 x 通过引用捕获。

#### parameters（参数列表）

定义 Lambda 表达式的输入参数，可以省略，如果没有参数可以用 () 表示。

#### return_type（返回类型）

可选，通常可以省略，编译器会自动推断返回类型。如果需要明确指定，可以使用 -> 来定义。

#### body（函数体）

Lambda 表达式的主体，其中包含执行的代码。

### 用法示例

#### 递归

在 C++ 中，递归 Lambda 表达式的使用可以通过一些技巧来实现。
由于 Lambda 表达式本身没有名称，因此直接在其内部调用自己是不可行的。
不过，我们可以使用一个 std::function 来存储 Lambda 表达式，从而实现递归调用。下面是详细的介绍和示例。

递归 Lambda 表达式的实现

##### 方法 1: 使用 std::function

我们可以使用 std::function 来定义一个可调用的 Lambda 表达式，然后在其内部调用自己。以下是一个计算阶乘的示例：

```cpp
// 定义递归 Lambda 表达式
std::function<int(int)> factorial = [](int n) -> int {
    if (n <= 1) return 1; // 基本情况
    return n * factorial(n - 1); // 递归调用
};
```

##### 方法 2: 使用捕获列表

另一种方法是通过捕获自己来实现递归，但这种方式有些复杂。以下是一个使用捕获列表的例子：

```cpp
// 定义递归 Lambda 表达式
auto factorial = [](auto self, int n) -> int {
    if (n <= 1) return 1; // 基本情况
    return n * self(self, n - 1); // 递归调用
};
// 调用 Lambda 表达式
std::cout << factorial(factorial, 5) << std::endl;

```

代码解析
auto self:  我们在 Lambda 的参数中定义了一个 auto self，它代表 Lambda 自身。

递归调用: 在 Lambda 的主体中，我们通过 self(self, n - 1) 来递归调用自身。

调用: 当我们调用 factorial(factorial, num) 时，将 Lambda 自身作为参数传入。


#### 排序的 Lambda 表达式

```cpp
[](int a, int b) {
    return a < b;
}
```

捕获列表：[]，没有捕获任何外部变量。
参数：int a, int b，表示两个整数。
返回类型：省略，编译器会自动推断为 bool。
函数体：比较 a 和 b，返回 true 如果 a 小于 b，用于升序排序。

#### 查找大于 5 的数字的 Lambda 表达式

```cpp
[](int num) {
    if (num > 5) {
        std::cout << num << " ";
    }
}
```

捕获列表：[]，没有捕获外部变量。

参数：int num，表示一个整数。

返回类型：省略，返回类型为 void。

函数体：检查 num 是否大于 5，若是，则输出该数字。

#### 计算总和的 Lambda 表达式

```cpp
[](int total, int num) {
    return total + num;
}
```

捕获列表：[]，没有捕获外部变量。
参数：int total 和 int num，total 是累计值，num 是当前遍历到的元素。
返回类型：省略，返回类型为 int。
函数体：返回 total 和 num 的和。

#### 求和（STL函数）

在 C++ 中，Lambda 表达式可以用来定义匿名函数

用于需要函数作为参数的场合，例如排序、过滤、映射等操作。

Lambda 能够捕获上下文中的变量

```cpp
int sum = std::accumulate(numbers.begin(), numbers.end(), 0, [](int total, int num) {
        return total + num;
    });
```

#### Lambda 表达式的捕获示例

为了更好地理解捕获机制，下面给出一个示例，展示如何捕获外部变量。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int threshold = 5; // 外部变量
    std::vector<int> numbers = {10, 5, 8, 12, 3, 7};

    // 使用 Lambda 表达式，捕获外部变量 threshold
    std::cout << "Numbers greater than " << threshold << ": ";
    std::for_each(numbers.begin(), numbers.end(), [threshold](int num) {
        if (num > threshold) {
            std::cout << num << " ";
        }
    });
    std::cout << std::endl;

    return 0;
}
```

##### 代码解析

在这个示例中，threshold 是一个外部变量，我们通过 [threshold] 捕获它。
这样我们就可以在 Lambda 表达式中使用 threshold 变量。
输出结果将显示所有大于 threshold（5）的数字。

# 二叉查找树 BST

## 概念

  二叉查找树/二叉搜索树 (Binary Search Tree, ***BST***): 

      左子树的所有节点值 < 根节点值
      
      右子树的所有节点值 > 根节点值

![](https://images0.cnblogs.com/i/497634/201403/270932052801072.jpg)


## 例题解析

### 例 1 ：插入法建立二叉搜索树（极易）

#### 题目描述

```txt
插入法建立二叉搜索树

题目描述：
      下面所给的是二叉搜索树节点的结构，你的任务是写一个插入函数void insert(treeNode* &root, int x)。

  struct treeNode{
      int val;
      treeNode* lchild;
      treeNode* rchild;
      treeNode():val(0),lchild(NULL),rchild(NULL){}
  };
​
      上述结构定义在头文件treeNode.h中（即你需要使用#include"treeNode.h"）。

注意事项：
      你只需写出void insert(treeNode* &root, int x)函数实现即可，不用提交main函数。


```

#### 实现思路


***递归判断***


由于我们针对的是正则二叉树，忘了见[对应知识点--正则二叉树](#1概念介绍)

     1. 设置递归终止条件
   
          空节点：新建节点

     2. 递归判断左右子树
          
          插入值小于节点值 ，递归遍历左子树

          插入值大于节点值，递归遍历右子树

#### 实现代码

```cpp
#include<iostream>
using namespace std;

//节点定义
struct node
{
    int val;
    node *lchild;
    node *rchild;
    node(int val) : val(val), lchild(NULL), rchild(NULL) {}
};

//建树
void insert(node *&root, int val)
{
    if (root == NULL)
        root = new node(val);
    if (val <= root->val)
        insert(root->lchild, val);
    else
        insert(root->rchild, val);
}
```

### 例 2 ：二叉搜索树的路径长度（易）

#### 题目描述

```txt
二叉搜索树的路径长度

问题描述
二叉搜索树是这样的一棵二叉树:

要么是一棵空树。
要么由一个根结点和左右子树组成，且根结点key值大于或等于左子树中所有结点key值并且小于右子树中所有结点key值，左右子树同样是二叉搜索树。

我们定义二叉搜索树的root-to-leaf路径长度为：路径上所有结点key值之和。

现在给定一个由n个元素组成的序列和路径长度m，请先根据序列构造出来一棵二叉搜索树，然后找出所有root-to-leaf路径等于m的路径。

输入
有多个测试案例，以EOF结束

每个测试案例有两行：

第一行由n和m组成，n和m之间以空格隔开，n (0<=n<=1000)代表序列中元素个数，m (INT_MIN<=m<=INT_MAX)代表要找到的路径的长度。
第二行是输入的序列，由n个整数组成，以空格隔开。

输出
对于每个测试案例，每一行按序输出一条路径；如果没有符合条件的路径就输出NULL，单独占一行，例如：

13->7->3->5
13->7->8
13->15
​
路径的顺序类似于字符串的的比较。

样例输入
7 28
13 15 7 3 8 -2 5
7 -10
13 15 7 3 8 -2 5
​
样例输出
13->7->3->5
13->7->8
13->15
NULL


```

#### 实现思路


***递归判断***


由于我们针对的是二叉查找树（BST），忘了见[对应知识点--BST](#1概念介绍)

     1. 设置递归终止条件BST
   
          空节点 ： 新建节点并返回

     2. 递归判断左右子树
          
          插入值小于节点值 ，递归遍历左子树

          插入值大于节点值，递归遍历右子树

#### 实现代码

```cpp
#include <iostream>
#include <vector>
#include <sstream> // for ostringstream
#include <string>
using namespace std;

//节点定义
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};
//建树
void insert(TreeNode *&root, int val)
{
    if (root == nullptr)
        root = new TreeNode(val);
    else if (val < root->val)
        insert(root->left, val);
    else
        insert(root->right, val);
}
//寻找长度为 m 且终点为叶子节点的路径
void findPaths(TreeNode *node, int target, vector<int> &currentPath, vector<string> &results)
{    
     //递归终止条件：遍历到叶节点（叶节点的子树为空）
    if (node == nullptr)
        return;

     //将当前路径加入到路径序列中
    currentPath.push_back(node->val);

     //条件判断
     //条件 1 ：如果终点是叶子节点
    if (node->left == nullptr && node->right == nullptr)
    {

        // 计算当前路径和
        int sum = 0;
        for (int val : currentPath)
            sum += val;

        //条件 2 ：如果路径和等于要找的路径长度 m 
        if (sum == target)
        { 
            // 将路径格式化后保存在结果数组中
            ostringstream oss;
            for (size_t i = 0; i < currentPath.size(); ++i)
            {
                oss << currentPath[i];
                if (i < currentPath.size() - 1)
                {
                    oss << "->";
                }
            }
            results.push_back(oss.str()); // 保存路径
        }
    }
     
    //递归遍历左右子树
    findPaths(node->left, target, currentPath, results);
    findPaths(node->right, target, currentPath, results);

    //回溯恢复路径
    currentPath.pop_back();
}

//测试函数
int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        if (n == 0)
        {
            cout << "NULL" << endl;
            continue;
        }

        TreeNode *root = nullptr;
        for (int i = 0; i < n; ++i)
        {
            int val;
            cin >> val;
            insert(root, val);
        }

        vector<string> results;
        vector<int> currentPath;
        findPaths(root, m, currentPath, results);

        if (results.empty())
        {
            cout << "NULL" << endl;
        }
        else
        {
            for (const string &path : results)
            {
                cout << path << endl;
            }
        }
    }

    return 0;
}
```

#### 递归优化

***我们发现，我们每次判断路径和的时候都需要重新计算一次，导致多次的重复计算***

***优化目标：减少在每个叶节点处计算路径和的开销***

     优化步骤：
          1. 添加累加和参数：在递归函数中添加一个参数currentSum，用于跟踪当前路径的累加和。
          2. 更新累加和：在将当前节点加入路径时，更新currentSum。
          3. 叶节点判断：到达叶节点时，直接比较currentSum与目标值，而不需要遍历currentPath。
          4. 递归调用时传递累加和：在递归调用左右子树时，传递更新后的currentSum。

#### 优化代码实现

```cpp
// 优化的findPaths函数
void findPaths(TreeNode *node, int target, vector<int> &currentPath, int currentSum, vector<string> &results)
{    
    // 递归终止条件：节点为空
    if (node == nullptr)
        return;

    // 将当前节点加入路径，并更新当前路径和
    currentPath.push_back(node->val);
    currentSum += node->val;

    // 判断是否为叶节点
    if (node->left == nullptr && node->right == nullptr)
    {
        // 如果当前路径和等于目标值，则将路径加入结果
        if (currentSum == target)
        { 
            // 将路径格式化为字符串
            ostringstream oss;
            for (size_t i = 0; i < currentPath.size(); ++i)
            {
                oss << currentPath[i];
                if (i < currentPath.size() - 1)
                {
                    oss << "->";
                }
            }
            results.push_back(oss.str());
        }
    }
    else
    {
        // 递归遍历左右子树
        findPaths(node->left, target, currentPath, currentSum, results);
        findPaths(node->right, target, currentPath, currentSum, results);
    }

    // 回溯，移除当前节点
    currentPath.pop_back();
}
```
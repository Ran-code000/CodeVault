# 判断正则二叉树

***递归判断***

## 概念

    正则二叉树 (Regular Binary Tree): 

    但每个节点要么有两个子节点，要么是叶子节点。

![](https://i-blog.csdnimg.cn/blog_migrate/b5c9d54b3caa145b98c94f37335f7b23.png#pic_center)

## 实现思路

     1. 设置递归终止条件
   
          （1）空节点

          （node == nullptr） ————> return true;

          （2）只有一个子树

          （!root->left && root->right || root->left && !root->right） ————> return false;

     2. 递归判断左右子树
          
          return isRegular(root->left) && isRegular(root->right);

## 例 ：判断正则查找树

### 题目描述

```txt
正则二叉树

问题
给定一颗二叉查找树，其中结点上存储整数关键字，请你判断它是否一棵正则二叉树，即每个内部结点均有两个子结点。

输入
第一行是测试样例数，接下来是若干测试样例。对于每个测试样例，第一行是二叉树结点个数n，第二行是n个关键字序列，表示二叉树的先序遍历结果。假定关键字均不相同。

输出
如果二叉查找树是正则的，则输出“YES”, 否则输出"NO",每个输出占一行。

输入样例
5
2
10 5
3
1 4 7
3 
5 3 2
3
10 4 23
5
10 6 5 8 20
​
输出样例
NO
NO
NO
YES
YES
​

```


### 实现代码

```cpp
#include <iostream>
using namespace std;
//节点定义
struct node
{
    int val;
    node *left;
    node *right;
    node(int val, node *left = nullptr, node *right = nullptr) : val(val), left(left), right(right) {}
};
//建树
void insert(node *&root, int x)
{
    if (root == nullptr)
    {
        root = new node(x);
        return;
    }
    else if (root->val > x)
        insert(root->right, x);
    else
        insert(root->left, x);
}
//判断是不是正则二叉树
bool isRegular(node *root)
{    
     //空节点
    if (root == nullptr)
        return true;
     //正则二叉树的满足条件：左右子树均存在或均不存在————> 不满足：左右子树只有一个存在
    if (!root->left && root->right || root->left && !root->right)
        return false;
     //递归判断左右子树
    return isRegular(root->left) && isRegular(root->right);
}
//测试函数
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        node *root = nullptr;
        while (m--)
        {
            int x;
            cin >> x;
            insert(root, x);
        }
        if (isRegular(root))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---


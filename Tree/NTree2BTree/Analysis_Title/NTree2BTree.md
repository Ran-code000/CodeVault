# 多叉树转二叉树

***问题引入*** ： 

***question 1***：我们是否知道树有几种表示方法？

***question 2***：我们是否可以在不同的表示方法之间进行进行转换？

---

***answer1 : 两种 ———> 左孩子右兄弟表示法 和 双亲表示法***

这里我们通过图可以直观的理解这两种树的表示方法

1. ***左孩子右兄弟表示法***
   
![左孩子右兄弟表示法](https://i-blog.csdnimg.cn/blog_migrate/c6d6323e77d554e223e11fdb5fa84d4c.jpeg)

2. ***双亲表示法***
 
![双亲表示法](https://i-blog.csdnimg.cn/blog_migrate/84066ce1b6349fec9f47a08da56d2e3e.jpeg)

***answer2 : 可以 ———> 例如我们可以将用双亲表示法输入的节点信息，转换为左孩子右兄弟表示法的二叉树形式，也就是实现多叉树转二叉树***
直接说有点抽象，后面我们通过例题详细介绍

---
---

”那么什么叫实现多叉树转二叉树“

```txt
  我们看这个图不难发现

  左半部分是多叉树的形式，右半部分是二叉树的形式
```
![左孩子右兄弟表示法](https://i-blog.csdnimg.cn/blog_migrate/c6d6323e77d554e223e11fdb5fa84d4c.jpeg)

---
---
***现在我们有了树的两种表示方法的基本知识，也对多叉树转二叉树有了直观大致的了解，现在我们通过一道例题详细剖析转换的过程***
---
---

### 题目描述

---
省流版：用多叉树的双亲表示法输入节点，转换成左儿子右兄弟的二叉树形式，用层序遍历输出
---

```txt
多叉树与二叉树

题目描述
给出一棵有n个点的以1为根节点的有根多叉树，请把它转成左儿子右兄弟的二叉树形式，并输出其层次遍历顺序。

注意，每个节点的左儿子一定使用它的所有儿子中的编号最小的，右兄弟一定使用比它编号大的兄弟中最小的兄弟的编号。层次遍历需严格按照自上而下，自左而右访问树的节点。

输入描述
第1行，有根多叉树的节点数n (1<=n<=100,000)

第2行到第n行，第i行表示i号节点的父亲节点f[i]，(1<=f[i]<i)

输出描述
一行，用空格分开，层次遍历顺序

输入样例
5
1
1
1
2
​
输出样例
1 2 5 3 4
​
```


### 代码实现

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//节点定义
struct TreeNode
{
  int leftChild;
  int rightSibling;

  TreeNode() : leftChild(-1), rightSibling(-1) {}
};

class Tree
{
private:
  vector<TreeNode> nodes;

public:
  //n + 1 是因为节点下标从 1 开始（节点 0 不使用）
  Tree(int n) : nodes(n + 1) {} 

  void addParent(int child, int parent)
  {
    //如果 parent 节点没有左儿子（即 leftChild == -1），就直接将 child 作为左儿子
    if (nodes[parent].leftChild == -1)
    {
      nodes[parent].leftChild = child; 
    }
    //如果 parent 节点已经有左儿子，就需要找到这个左儿子的右兄弟链
    else
    {
      // 左儿子（也是兄弟链的链头）
      int sibling = nodes[parent].leftChild;
      //通过循环遍历 parent 节点的所有右兄弟，直到找到一个没有右兄弟的节点
      while (nodes[sibling].rightSibling != -1)
        sibling = nodes[sibling].rightSibling;
      //直到找到一个没有右兄弟的节点，然后将 child 设置为该节点的右兄弟
      nodes[sibling].rightSibling = child; 
    }
  }

  vector<int> levelOrderTraversal()
  {
    vector<int> result;
    queue<int> q;
    q.push(1); // 从根节点开始

    while (!q.empty())
    {
      int nodeIndex = q.front();
      q.pop();
      result.push_back(nodeIndex);

      // 如果当前节点有左儿子（leftChild != -1），则将左儿子入队
      if (nodes[nodeIndex].leftChild != -1)
      {
        q.push(nodes[nodeIndex].leftChild);
      }
      // 如果当前节点有右兄弟（rightSibling != -1），则将右兄弟入队
      if (nodes[nodeIndex].rightSibling != -1)
      {
        q.push(nodes[nodeIndex].rightSibling);
      }
    }
    //返回存储层次遍历结果的 result 数组
    return result;
  }
};

//test function
int main()
{
  int n;
  cin >> n; // 读取节点数

  Tree tree(n); // 创建树

  // 读取父节点信息，并构建树
  for (int i = 2; i <= n; ++i)
  {
    int parent;
    cin >> parent;
    tree.addParent(i, parent);
  }

  // 进行层次遍历并输出结果
  vector<int> result = tree.levelOrderTraversal();
  for (size_t i = 0; i < result.size(); ++i)
  {
    if (i > 0)
      cout << " ";
    cout << result[i];
  }
  cout << endl;

  return 0;
}

```

### 关键代码解释

由于 ***模块化和封装性*** 所以我们将转换方法封装成了类方法，具体可以根据需要调整

现在再看一遍这个图
![左孩子右兄弟表示法](https://i-blog.csdnimg.cn/blog_migrate/c6d6323e77d554e223e11fdb5fa84d4c.jpeg)

代码中详细注释了第一次添加节点的过程，后续过程以此类推
```cpp
void addParent(int child, int parent)
{
  //B 设置为 A 的左儿子
  if (nodes[parent].leftChild == -1)
  {
    nodes[parent].leftChild = child; 
  }
  //已经有了 B 做 A 的左儿子
  else
  {
    // sibling 现在为 B，作为右兄弟链的开头
    int sibling = nodes[parent].leftChild;
    // 循环遍历 B 所有右兄弟，直到找到一个没有右兄弟的节点，找到了 C
    while (nodes[sibling].rightSibling != -1)
      sibling = nodes[sibling].rightSibling;
    //将 C 设置为 B 的右兄弟
    nodes[sibling].rightSibling = child; 
  }
}

```


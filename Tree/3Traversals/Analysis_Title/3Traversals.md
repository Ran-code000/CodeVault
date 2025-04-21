# **二叉树的增删改查** and **3 + 1 种遍历方式** and **内存清理方法**

## **二叉树的增删改查**

### 节点定义

```cpp
struct Treenode
{
    int val; //节点值
    Treenode* lc; //左孩子指针（指向左子树根节点）
    Treenode* rc; //右孩子指针（指向右子树根节点）
    Treenode(const int& val) : val(val), lc(nullptr), rc(nullptr){}
};
```

### 增

```cpp
void insert(Treenode *&node, const int &val)
{
    //找到插入的位置
    if (node == nullptr)
        node = new Treenode(val);
    //定义：左子树上所有的值均小于根节点的值
    else if (val < node->val)
        insert(node->lc, val);
    //定义：右子树上所有的值均大于根节点的值
    else if (val > node->val)
        insert(node->rc, val);
    //保证书中元素的唯一性，若有相等的值直接返回
    else
        return;
}
```

### 删

```cpp
void remove(Treenode*& node, const int& val)
{
    if(node == nullptr) return;
    //定义：左子树上所有的值均小于根节点的值
    else if(val < node->val) remove(node->lc, val);
    //定义：右子树上所有的值均大于根节点的值
    else if(val > node->val) remove(node->rc, val);
    //找到待删除的节点
    else
    {
        if(node->lc == nullptr && node->rc == nullptr)
        {
            delete node;
            node = nullptr;
        }
        //若待删除的节点只有右子树，用待删除节点的父节点的右孩子指针指向待删除节点的右孩子
        else if(node->lc == nullptr)
        {
            Treenode* temp = node;
            node = node->rc;
            delete temp;
        }
        //若待删除的节点只有左子树，用待删除节点的父节点的左孩子指针指向待删除节点的左孩子
        else if(node->rc == nullptr)
        {
            Treenode* temp = node;
            node = node->lc;
            delete temp;
        }
        //若待删除的节点左右子树均有
        /*
            法一：

                用左子树中值最大的节点作为根节点（即用左子树中最大的节点的值覆盖待删除节点（即当前根节点）的值）————> 递归删除左子树中最大的节点（为了保证唯一性：因为已经将其作为根节点了）

            法二：
            
                用右子树中值最小的节点作为根节点（即用右子树中最小的节点的值覆盖待删除节点（即当前根节点）的值）————> 递归删除右子树中最小的节点（为了保证唯一性：因为已经将其作为根节点了）
        */
        else
        {   
            //法一：
            Treenode* maxNode_of_lc = findMax(node->lc);
            node->val = maxNode_of_lc->val;
            remove(node->lc, maxNode_of_lc->val);

            //法二：
            // Treenode* minNode_of_rc = findMin(node->rc);
            // node->val = minNode_of_rc->val;
            // remove(node->rc, minNode_of_rc->val);
        }
    }
}
```

**findMin 和 findMax 辅助函数见**[辅助函数](#辅助函数)

### 改

```cpp
//改
bool change(Treenode *node, const int &oldval, const int & newval)
{
    if (node == nullptr)
        return false;
    if (node->val == oldval)
    {
        node->val = newval;
        return true;
    }
    else if (oldval < node->val)
        return change(node->lc, oldVal, newVal);
    else if (oldval > node->val)
        return change(node->rc, oldVal, newVal);
    return false;
}

```

### 查

```cpp
bool find(Treenode *node, const int &val)
{
    if (node == nullptr)
        return false;
    // ！！！！！！！！致命 bug！！！
    // 不 return ：即使递归调用找到了目标值，结果也不会被传递回上一级调用，最终返回的是默认值 false，即使中间某一级找到了目标值。
    // 返回结果：递归调用的结果会被传递给上一级调用，最终返回正确的结果
    else if (val < node->val)
        return find(node->lc, val);
    else if (val > node->val)
        return find(node->rc, val);
    else 
        return true;
    return false;
}
```
---

### **非常重要的小细节！！！！！！！！！！**

对比这两句代码

`insert(node->lc, val);`  

`return find(node->lc, val);`

**为什么 insert 不需要 return 而 find 需要 return 呢** 

because:

**insert 函数**：

其逻辑是通过指针修改树的结构。由于在这个过程中直接修改了指针，当递归到合适的位置并成功插入节点后，函数自然结束，不需要再返回值给调用者。

**find 函数**：

其目的是在树中查找某个值并返回查找结果（布尔值），结果需要在多个递归调用之间传递，返回值显得尤为重要。

如果不 return ：即使递归调用找到了目标值，结果也不会被传递回上一级调用，最终返回的是默认值 false，即使中间某一级找到了目标值。

### 辅助函数

```cpp
Treenode *findMin(Treenode *node) const
{
    while (node && node->lc)
        node = node->lc;
    return node;
}
Treenode *findMax(Treenode *node) const
{
    while (node && node->rc)
        node = node->rc;
    return node;
}
```

## **3 + 1 种遍历方式**

### 前序遍历

```cpp
void preOrder(Treenode *node) const
{
    if (node == nullptr)
        return;
    cout << node->val << " ";
    preOrder(node->lc);
    preOrder(node->rc);
}
```

### 中序遍历

```cpp
void inOrder(Treenode *node) const
{
    if (node == nullptr)
        return;
    inOrder(node->lc);
    cout << node->val << " ";
    inOrder(node->rc);
}
```

### 后续遍历

```cpp
void postOrder(Treenode *node) const
{
    if (node == nullptr)
        return;
    postOrder(node->lc);
    postOrder(node->rc);
    cout << node->val << " ";
}
```

### 层序遍历

```cpp
#include <queue>
void levelOrder(Treenode* node) const
{
    if (node == nullptr)
        return;
    queue<Treenode*> q;
    q.push(node);

    while(!q.empty())
    {
        Treenode* temp = q.front();
        q.pop();

        cout << temp->val << " ";
        //注意需要先判空再入队，避免解空指针引发错误
        if(temp->lc) q.push(temp->lc);
        if(temp->rc) q.push(temp->rc); 
    }
}
```

## 内存清理方法**

```cpp
void clear(Treenode *&node)
{
    if (node == nullptr)
        return;
    clear(node->lc);
    clear(node->rc);
    delete node;
    node = nullptr; //将当前节点指针置为空，避免悬空指针
}
```

---
---

**到目前为止我们已经学会了二叉树基本的增删改查和四种常用的遍历方式了**，不想往下看的可以划走喽！！！！

**下面是方法接口的简单介绍** and **遍历例题介绍**

上面介绍的方法一般具体实现会封装为私有成员函数，那么如果我们需要从外部调用就需要提供外部接口

## 外部接口

```cpp
void insertRandom(int n)
{   
    //可以采用随机数种子生成插入的值
    while (n--)
    {
        //这里
        int val = rand() % 100;
        insert(root, val);
    }
}
void insert(const int& val)
{   
    insert(root, val);
}
void remove(const int &val)
{
    remove(root, val);
}
bool change(const int &oldval, const int& newval)
{
    return change(root, oldVal, newVal);
}
bool find(const int &val)
{
    return find(root, val);
}

void clear() 
{ 
    clear(root); 
}
void inOrder() const 
{ 
    inOrder(root);
    cout << endl; 
}
void preOrder() const 
{ 
    preOrder(root); 
    cout << endl; 
}
void postOrder() const 
{ 
    postOrder(root);
    cout << endl; 
}
void levelOrder() const 
{ 
    levelOrder(root); 
    cout << endl;
}
void Display() const 
{ 
    inOrder(root); 
    cout << endl; 
}

```

### 例题

**提要**

        我们都知道我们存储一颗二叉树一般要么是链表存储，要么是用数组存储

        前面已经介绍了用链表构建一颗二叉树，以及对二叉树进行一些操作

        为了拓宽知识面，这道例题采用了数组存储的方式，用索引查找（链表通过指针）

#### 题目描述

```txt
二叉树的三种遍历

题目描述

给定一棵大小为n的二叉树，其结点名称使用字符串标识。每个结点的字符串由大写字母构成，且长度不超过6。

现在，你要输出这棵二叉树的先序、中序和后序遍历结果。

输入描述

第一行包含一个整数n (1≤n≤10^4)，表示节点个数。

接下来n行，每行包含3个用空格分隔的字符串si, li, ri 表示节点的名称和左右子节点。

如果子节点为空，则用-（减号）表示。

输入保证节点的字符串名称是两两不同，并且名称是长度不超过6的大写字母序列。

输入保证二叉树的形态是合法的。

输出描述

三行，每行是n个用空格隔开的字符串，分别表示先序、中序和后序遍历结果。

输入样例1

6

A B C 

B D E 

C - - 

D - - 

E - F

F - -
​

输出样例1

A B D E F C

D B E F A C

D F E B C A
​

提示1

树的根节点编号未必为第一个节点。

提示2

样例1的树如下所示。

```txt
             A
        ____/\____
       /          \
      B            C
   __/\__
  /      \
 D        E
           \
            F
```

### 实现代码

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

//定义节点的方式，简化数据结构
struct Node 
{
  string val;
  size_t lc; //左孩子节点索引
  size_t rc; //右孩子节点索引
};
//储存所有节点
vector<Node> nodes; 

//三种遍历方式
//规范性；结果不直接输出，而是存在一个结果数组vector<string>& result里
void preorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  result.push_back(nodes[root].val);
  preorder(nodes[root].lc, result);
  preorder(nodes[root].rc, result);
}

void inorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  inorder(nodes[root].lc, result);
  result.push_back(nodes[root].val);
  inorder(nodes[root].rc, result);
}

void postorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  postorder(nodes[root].lc, result);
  postorder(nodes[root].rc, result);
  result.push_back(nodes[root].val);
}

int main()
{
  int n;
  cin >> n;

  // 节点编号从1开始，0作为空节点
  nodes.resize(n + 1);
  unordered_map<string, size_t> name2id; // 用于将节点名称映射到节点索引

  // 用法见附录
  auto get_node = [&](const string &name) -> size_t
  {
    if (name == "-")
      return 0; // 空子树
    //若当前节点名称还未分配索引
    if (name2id.find(name) == -1)
    {
      //分配索引
      size_t newid = name2id.size() + 1;
      //创建节点名称与索引的映射
      name2id[name] =  nameid;
      //用索引在nodes中保存节点
      nodes[newid].name = name;     
    }
    // 若当前节点名称 y 已经分配了索引
    else
    { //返回已经创建的索引
      return name2id[name];
    }
  };

  //像创建根节点指针一样，创建根节点的索引
  size_t root = 0;

  for (int i = 1; i <= n; ++i)
  {
    string name, lc_name, rc_name;
    cin >> name >> lc_name >> rc_name;
    size_t node = get_node(name);        // 获取当前节点编号
    size_t lc = get_node(lc_name);   // 左子节点编号
    size_t rc = get_node(rc_name); // 右子节点编号
    nodes[node].lc = lc;
    nodes[node].rc = rc;
    //找根，详见附录
    root ^= node ^ lc ^ rc;
  }

  // 三种遍历的结果数组
  vector<string> pre, in, post;
  preorder(root, pre);
  inorder(root, in);
  postorder(root, post);

  for (const string &s : pre)
    cout << s << " ";
  cout << endl;
  for (const string &s : in)
    cout << s << " ";
  cout << endl;
  for (const string &s : post)
    cout << s << " ";
  cout << endl;
}
```

[题目代码解析见附录](#附录)

# 附录

## 异或

`root ^= node ^ lc ^ rc;`

### 1. 状态切换

#### 通过异或操作，可以在多个值之间快速切换状态

```cpp
#include <iostream>

int main()
{
    int state = 0; // 初始状态为关（0）

    // 切换状态
    state ^= 1;                                                // 切换为开（1）
    std::cout << "State after toggle: " << state << std::endl; // 输出 1

    state ^= 1;                                                // 切换为关（0）
    std::cout << "State after toggle: " << state << std::endl; // 输出 0

    return 0;
}
```

### 2. 使用异或操作实现求单一出现的元素

```cpp
#include <iostream>
#include <vector>

int findUnique(const std::vector<int> &nums)
{
    int unique = 0;
    for (int num : nums)
    {
        unique ^= num; // 通过异或操作进行组合
    }
    return unique; // 返回唯一的元素
}

int main()
{
    std::vector<int> nums = {2, 3, 5, 4, 5, 3, 2}; // 2, 3, 5 出现两次，4 出现一次
    int unique = findUnique(nums);
    std::cout << "The unique element is: " << unique << std::endl; // 输出 4

    return 0;
}
```

## 例题另解（比较好理解）

区别：

不用引入索引

直接通过节点名称分别建立父节点与左节点和右节点的 ***哈希映射***

话不多说，上代码！！！！

## 代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// unordered_map<string, pair<string, string>> tree;
// 更为清晰
unordered_map<string, string> lc;
unordered_map<string, string> rc;

// 标记是否为子节点便于去寻找根节点(这里其实原方案的异或操作比较好)
unordered_map<string, bool> ischild;
//存储所有节点
vector<string> nodes;

void preOrder(string root)
{
    if (root == "-")
        return;

    cout << root << " ";
    preOrder(lc[root]);
    preOrder(rc[root]);
}
void inOrder(string root)
{
    if (root == "-")
        return;

    inOrder(lc[root]);
    cout << root << " ";
    inOrder(rc[root]);
}
void postOrder(string root)
{
    if (root == "-")
        return;

    postOrder(lc[root]);
    postOrder(rc[root]);
    cout << root << " ";
}

int main()
{
    int n;
    cin >> n;
    nodes.resize(n + 1);

    for (int i = 0; i < n; i++)
    {
        string root, l, r;
        cin >> root >> l >> r;

        nodes[i] = root;
        // tree[root] = {l, r};
        lc[root] = l;
        rc[root] = r;

        if (l != "-")
            ischild[l] = true;
        if (r != "-")
            ischild[r] = true;
    }

    string root;
    for (int i = 0; i < n; i++)
    {
        if (!ischild[nodes[i]])
        {
            root = nodes[i];
            break;
        }
    }

    preOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    postOrder(root);
    cout << endl;

    return 0;
}
```
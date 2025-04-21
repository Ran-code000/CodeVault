# 判断是否为对称二叉树 + 最大对称子二叉树

## 判断对称二叉树

***给定一个二叉树的根节点 root ， 检查它是否轴对称***

如果一个树的左子树与右子树镜像对称，那么这个树是对称的。

因此，该问题可以转化为：两个树在什么情况下互为镜像？ 

答：

它们的两个根结点具有相同的值，即每个树的右子树都与另一个树的左子树镜像对称

### 方法一：递归

1. 实现这样一个递归函数，通过 ***同步移动*** 两个指针的方法来遍历这棵树, p 指针和 q 指针分别指向这棵树左右子树的根节点

2. 递归终止条件：
   
    （1）如果说左右子树为空，那么必然是对称子树，直接 return true

    （2）如果说左右子树其中一个为空且不都为空，那么必然不是对称子树，直接 return false 

3. 递归判断前先检查 p 和 q 节点的值是否相等，如果相等再递归判断左右子树是否对称（p 右移时，q 左移，p 左移时，q 右移）



```cpp
bool check(TreeNode *p, TreeNode *q) 
{
    //如果说左右子树为空，那么必然是对称子树，直接 return true
    if (!p && !q) 
        return true;
    //如果说左右子树其中一个为空且不都为空，那么必然不是对称子树，直接 return false 
    if (!p || !q) 
        return false;
    //先检查 p 和 q 节点的值是否相等，如果相等再递归判断左右子树是否对称
    return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
}

bool isSymmetric(TreeNode* root) 
{
    //从根节点的左右子树开始检查
    return check(root->left, root->right);
}
```

### 方法二：迭代

方法一中我们用递归的方法实现了对称性的判断，那么如何用迭代的方法实现呢？

1. 首先我们引入一个 ***队列***，这是把递归程序改写成迭代程序的常用方法。

2. 初始化时我们把  ***根节点入队两次***，每次提取两个结点并比较它们的值

（队列中每两个连续的结点应该是相等的，而且它们的子树互为镜像）

3. 然后将两个结点的左右子结点按相反的顺序插入队列中。

4. 当队列为空时，或者我们检测到树不对称（即从队列中取出两个不相等的连续结点）时，该算法结束。


```cpp
#include <queue>
using namespace std;

bool check(TreeNode *u, TreeNode *v)
{
    queue<TreeNode *> q;
    q.push(u);
    q.push(v);
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        v = q.front();
        q.pop();
        if (!u && !v)
            continue;
        if ((!u || !v) || (u->val != v->val))
            return false;

        q.push(u->left);
        q.push(v->right);

        q.push(u->right);
        q.push(v->left);
    }
    return true;
}

bool isSymmetric(TreeNode *root)
{
    return check(root, root);
}
```

## 最大对称子二叉树

题目描述：

```txt
最大对称子二叉树

问题描述:
一棵有点权的有根树如果满足以下条件，则被我们称为对称二叉树：

将这棵树所有节点的左右子树交换，新树和原树对应位置的结构相同且点权相等。
现在给出一棵二叉树，希望你找出它的一棵子树，该子树为对称二叉树，且节点数最多。请输出这棵子树的节点数。

输入格式：
第一行一个正整数n，表示给定的树的节点的数目，规定节点编号1∼n，其中节点1是树根。
第二行n个正整数，用一个空格分隔，第i个正整数v_i代表节点i的权值。

接下来n行，每行两个正整数l_i, r_i，分别表示节点i的左右孩子的编号。如果不存在左右孩子，则以-1表示。两个数之间用一个空格隔开。

输出格式：
共一行，包含一个整数，表示给定的树的最大对称二叉子树的节点数。

输入样例
2
1 3
2 -1
-1 -1
​
输出样例
1
```

### 完整代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int val;
    int left;
    int right;
};

// 辅助函数————检查是否为对称子树
bool check(int ld, int rd, const vector<node> &t)
{
    // 如果两个子节点都是空，返回对称
    if (ld == -1 && rd == -1)
        return true; 
    // 如果一个子节点为空，另一个不为空，返回不对称
    if (ld == -1 || rd == -1)
        return false; 
    // 对称子树条件
    return (t[ld].val == t[rd].val && check(t[ld].left, t[rd].right, t) &&
            check(t[ld].right, t[rd].left, t));
}
// 检查是否为对称子树
bool isSymmetric(int ld, int rd, const vector<node> &t)
{
    return check(ld, rd, t);
}
int maxSymmetricSubtree(int root, const vector<node> &tree, int &maxsize)
{
    // 递归终止条件，如果当前节点为空，返回 0
    if (root == -1)
        return 0; 

    // 递归获取左子树的对称子树节点数
    int leftSubtree_nodeNumber = maxSymmetricSubtree(tree[root].left, tree, maxsize);
    // 递归获取右子树的对称子树节点数
    int rightSubtree_nodeNumber = maxSymmetricSubtree(tree[root].right, tree, maxsize);

    // 当前节点算作一个节点
    int nodeNumber = 1;

    // 判断当前节点的左右子树是否对称，如果对称，累加左右子树的节点数
    if (isSymmetric(tree[root].left, tree[root].right, tree))
        nodeNumber += (leftSubtree_nodeNumber + rightSubtree_nodeNumber);
    maxsize = max(maxsize, nodeNumber); // 更新最大对称子树节点数

    // 返回当前节点对应的对称子树的节点数
    return nodeNumber;
}
int main()
{
    int n;
    cin >> n;
    vector<node> tree(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> tree[i].val;
    for (int i = 1; i <= n; i++)
        cin >> tree[i].left >> tree[i].right;
    int maxsize = 1;
    maxSymmetricSubtree(1, tree, maxsize);
    cout << maxsize << endl;
    return 0;
}
```

可以参照这个图思考

```txt
       0
      / \
     1   1
    / \ / \
   2  3 3  2
```


```txt
  节点
    2 ： 1 + 0 + 0 = 1;
    3 ： 1 + 0 + 0 = 1;

    1 ： 1 + 1 + 1 = 3;

    3 ： 1 + 0 + 0 = 1;
    2 ： 1 + 0 + 0 = 1;

    1 ： 1 + 1 + 1 = 3;

    0 ： 1 + 3 + 3 = 7;
```
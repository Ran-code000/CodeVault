# AVL 树

---

AVL树 (***AVL*** Tree): 

     一种自平衡的二叉查找树，任何节点的两个子树的高度最大差为1。
     
所有的 AVL树 都是 二叉查找树 （BST）
![](https://i-blog.csdnimg.cn/blog_migrate/c6571d7a46ab1237dde42275cddc053d.png)

AVL（任何节点的两个子树的高度最大差为1）
![](https://i-blog.csdnimg.cn/direct/441e85cae55245d196b770492dc8cb51.png)


---

## 例题详解（判断二叉查找树是否平衡 + 将二叉搜索树变平衡）

---

### 例 1 ：判断二叉查找树是否平衡（中）
---
#### 题目描述

```txt
判断二叉查找树是否平衡 2

问题
给定一颗二叉查找树，其中结点上存储整数关键字，请你判断它是否一棵平衡的二叉查找树，即每个内部结点的两颗子树高度差小于等于1。

输入
第一行是测试样例数，接下来是若干测试样例。对于每个测试样例，第一行是二叉树结点个数n，第二行是n个关键字序列，表示二叉树的先序遍历结果。假定关键字均不相同。

输出
如果二叉查找树是平衡的，则输出“YES”, 否则输出"NO",每个输出占一行。

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
YES
NO
NO
YES
YES
YES
NO
NO
YES
YES
```
---
#### 实现思路


***递归判断***
AVL

由于我们针对的是 AVL 树，忘了见[对应知识点--AVL](#1概念介绍)

     1. 设置递归终止条件
   
          空节点：返回 true

     2. 递归判断当前节点左右子树是否平衡并得到左右子树的高度
          
     3. 计算当前节点的左右子树高度差的绝对值是否超过 1
---
#### 实现代码

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 定义结点
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 构建二叉查找树的插入函数
TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
        return new TreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
}

// 检查二叉树是否平衡，并返回树的高度
bool isBalanced(TreeNode *root, int &height)
{
    if (!root)
    {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool leftBalanced = isBalanced(root->left, leftHeight);
    bool rightBalanced = isBalanced(root->right, rightHeight);

    // 当前结点平衡的条件是：左右子树高度差不超过1，且左右子树都是平衡的
    height = max(leftHeight, rightHeight) + 1;
    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}

int main()
{
    int t;
    cin >> t; // 输入测试用例数

    while (t--)
    {
        int n;
        cin >> n; // 输入结点个数
        vector<int> preorder(n);
        for (int i = 0; i < n; i++)
        {
            cin >> preorder[i]; // 输入先序遍历结果
        }

        // 构建二叉查找树
        TreeNode *root = NULL;
        for (int i = 0; i < n; i++)
        {
            root = insert(root, preorder[i]);
        }

        // 判断树是否平衡
        int height = 0;
        if (isBalanced(root, height))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}
```
---
#### 易出现的错误解释：

***观察这两段代码的区别在哪里***

正确：
```cpp
bool isBalanced(TreeNode *root, int &height)
{
    if (!root)
    {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool leftBalanced = isBalanced(root->left, leftHeight);
    bool rightBalanced = isBalanced(root->right, rightHeight);

    height = max(leftHeight, rightHeight) + 1;

    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}
```

---

错误：
```cpp
bool isBalanced(TreeNode* root, int& height) {
    if (!root) {
        height = 0;
        return true;
    }
    
    int leftHeight = 0, rightHeight = 0;

    height = max(leftHeight, rightHeight) + 1;
    
    return isBalanced(root->left, leftHeight) && isBalanced(root->right, rightHeight) && abs(leftHeight - rightHeight) <= 1;
}
```
---
思考：为什么出错？错在哪里？

解答：

     第一段正确代码：

          先递归判断左右子树的平衡性 isBalanced(root->left, leftHeight) 和 isBalanced(root->right, rightHeight)，
          
          并将左右子树的高度分别保存在 leftHeight 和 rightHeight 中。
          
          只有在子树的平衡性已经确认后，才计算当前节点的高度，并判断当前节点是否平衡。
          
          这样，左右子树的高度计算是在递归调用之后进行的，确保了当前节点的平衡性是基于已经计算出的左右子树高度的
          

     第二段错误代码：
          递归判断左右子树的平衡性之前，先计算了当前节点的高度。
          
          也就是说，左右子树的高度（leftHeight 和 rightHeight）在递归调用时仍然是初始值 0，
          
          这会导致在判断当前节点的平衡性时，左右子树的高度总是为 0，从而无法正确判断树的实际平衡状态。
---


---

朋友们，我们光会判断是否是平衡二叉树不行啊，如果是一棵平衡二叉树当然最好，如果不是呢，如果我就要一棵平衡二叉树呢，怎么搞？

让我们一起看例题 2，将二叉搜索树变平衡

---

### 例 2 ： 将二叉搜索树变平衡

#### 题目描述

```txt
题目描述

将二叉搜索树变平衡

给你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，请你返回任意一种。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就称这棵二叉搜索树是 平衡的 。

 

示例 1：
输入：root = [1,null,2,null,3,null,4,null,null]
输出：[2,1,3,null,null,null,4]
解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。
```

![tu](https://assets.leetcode.com/uploads/2021/08/10/balance1-tree.jpg)

```txt

示例 2：
输入: root = [2,1,3]
输出: [2,1,3]
```

![tu](https://assets.leetcode.com/uploads/2021/08/10/balanced2-tree.jpg)

```txt
提示：

树节点的数目在 [1, 104] 范围内。
1 <= Node.val <= 105
```

---
#### 实现思路


***递归重建树***

由于我们针对的是二叉搜索树转成 AVL 树，忘了见[对应知识点--AVL](#1概念介绍)

所以我们先要明确二叉搜索树有什么特点？ ————> 显然二叉搜索树元素有序 ————> 所以我们可以用这本来就有序的元素重建树即可

     1. 用中序遍历得到一个递增的有序序列

     2. 每次用中间的节点作为根节点，划分为左右两个区间
          
     3. 分别递归重建左右两个子树

#### 实现代码

```cpp

vector<int> inorderSeq;

// 用中序遍历得到一个递增的有序序列
void getInorder(TreeNode *node)
{
    if (node == nullptr)
        return;
    getInorder(node->left);
    inorderSeq.push_back(node->val);
    getInorder(node->right);
}

TreeNode *build(int l, int r)
{    
     //每次用中间的节点作为根节点
    int mid = (l + r) >> 1;
    TreeNode *root = new TreeNode(inorderSeq[mid]);

    // 递归重建左右两个子树
    if (l <= mid - 1)
        root->left = build(l, mid - 1);
    if (mid + 1 <= r)
        root->right = build(mid + 1, r);
     // 返回重建得到的平衡二叉树
    return root;
}

TreeNode *balanceBST(TreeNode *root)
{
    getInorder(root);
    return build(0, inorderSeq.size() - 1);
}
```

---
如果钻牛角尖的话，我们或许会纠结 ———— 我给出了这个方法 你直接用了这个方法，但是不知道这个方法为什么可行

***如果需要深入了解下面的数学证明，不感兴趣的可以直接跳过***
---
---
#### 数学证明

[自行查看力扣官网题解证明](https://leetcode.cn/problems/balance-a-binary-search-tree/solutions/241897/jiang-er-cha-sou-suo-shu-bian-ping-heng-by-leetcod/)
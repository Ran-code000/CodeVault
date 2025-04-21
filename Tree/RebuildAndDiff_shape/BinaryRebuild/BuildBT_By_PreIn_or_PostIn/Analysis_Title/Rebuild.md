# 二叉树的重建

***提要***： 建议看这篇之前先去了解二叉树的四种遍历方式[前序遍历，中序遍历，后序遍历和层序遍历](https://blog.csdn.net/2301_81373791/article/details/144098071?spm=1001.2014.3001.5501)

***问题引入***：

通过给定我们一颗二叉树，我们可以实现对这颗二叉树的遍历

question 1 ： 我们已知哪几种遍历方式可以 ***唯一*** 的确定一颗二叉树？ 并且我们怎么确定这颗二叉树？

question 2 ： 如果我们已知的遍历方式 ***不能唯一***的确定一颗二叉树， 那么可以有几种 ***不同形态***的二叉树？

## 解决question 1

answer : 我们若已知中序遍历，前/后序遍历即可唯一的确定一颗二叉树

至于为什么唯一确定我们这里不深入探讨，只做简单说明：

***唯一性***:

    前序遍历：唯一确定根节点的值 （前序遍历的第一个元素始终是当前子树的根节点）

    中序遍历：唯一确定根节点的位置

    so 这颗二叉树的每一步的划分都是唯一的，因此，从前序和中序遍历可以唯一确定出二叉树的结构。（后序和中序的组合也是同样道理）

下面给出两种代码实现

核心思想：

给出两种遍历方式 ——> 通过每次递增/减索引得到根节点从而新建一个节点 ——> 通过映射找到根节点在中序遍历中的位置

——> 递归构建 ***左右（前序遍历）/ 右左（后序遍历）** 子树

### 通过前序遍历和中序遍历递归构建二叉树

```cpp
// 通过前序遍历和中序遍历递归构建二叉树

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// 用模板定义树节点
template <typename T>
struct node
{
    T val;
    node<T> *left;
    node<T> *right;
    node(T val) : val(val), left(nullptr), right(nullptr) {}
};

// 根据前序和中序遍历构造二叉树
// preIndex: 记录当前在前序遍历中的索引
// inStart 和 inEnd : 确定当前递归的中序遍历子数组的范围
// inMap : 用来快速查找元素在中序遍历中的位置
node<int> *buildTree_by_preAndIn(const vector<int> &preorder, const vector<int> &inorder, int &preIndex, int inStart, int inEnd, unordered_map<int, int> &inMap)
{
    // 如果当前子树的中序范围无效（即开始索引大于结束索引），则返回空指针，表示没有子树
    if (inStart > inEnd)
        return nullptr;

    // 获取当前根节点的值并新建一个节点
    int rootVal = preorder[preIndex++]; // 前序遍历的第一个元素总是树的根。
    node<int> *root = new node<int>(rootVal);

    // 在中序遍历中找到根节点的位置
    int index = inMap[rootVal];

    // 递归构建左子树和右子树
    // 前序遍历————先构建左子树，后构建右子树！！！！！！！
    root->left = buildTree_by_preAndIn(preorder, inorder, preIndex, inStart, index - 1, inMap);
    root->right = buildTree_by_preAndIn(preorder, inorder, preIndex, index + 1, inEnd, inMap);

    return root;
}

// 遍历
void levelOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    queue<node<int> *> q;
    q.push(root);

    while (!q.empty())
    {
        node<int> *frt = q.front();
        q.pop();

        cout << frt->val << " ";

        if (frt->left != nullptr)
            q.push(frt->left);
        if (frt->right != nullptr)
            q.push(frt->right);
    }
    cout << endl;
}
void inOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// 清理内存函数
void deleteTree(node<int> *root)
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 测试函数
int main()
{
    // 输入前序遍历和中序遍历和后序遍历(可以根据需要改变输入)
    vector<int> preorder = {1, 2, 4, 5, 3, 6, 7}; // 前序遍历
    vector<int> inorder = {4, 2, 5, 1, 6, 3, 7};  // 中序遍历

    // 使用哈希表(unordered_map<int, int>)记录中序遍历元素的索引，快速查找元素的位置
    unordered_map<int, int> inMap;
    for (int i = 0; i < inorder.size(); i++)
        inMap[inorder[i]] = i;

    // 根据前序遍历和中序遍历构造二叉树
    int preIndex = 0;
    node<int> *root = buildTree_by_preAndIn(preorder, inorder, preIndex, 0, inorder.size() - 1, inMap);

    // 输出结果
    //中序遍历
    cout << "inOrder: ";
    inOrder(root);
    cout << endl;
    //层序遍历
    cout << "levelOrder: ";
    levelOrder(root);
    cout << endl;

    // 清理内存
    deleteTree(root);

    return 0;
}
```

### 通过后序遍历和中序遍历递归构建二叉树

```CPP
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// 模板定义树节点
template <typename T>
struct node
{
    T val;
    node<T> *left;
    node<T> *right;
    node(T val) : val(val), left(nullptr), right(nullptr) {}
};

// 根据后序和中序遍历构造二叉树
// postIndex: 记录当前在后序遍历中的索引
// inStart 和 inEnd : 确定当前递归的中序遍历子数组的范围
// inMap : 用来快速查找元素在中序遍历中的位置
node<int> *buildTree_by_postAndIn(const vector<int> &postorder, const vector<int> &inorder, int &postIndex, int inStart, int inEnd, unordered_map<int, int> &inMap)
{
    // 如果当前子树的中序范围无效（即开始索引大于结束索引），则返回空指针，表示没有子树
    if (inStart > inEnd)
        return nullptr;

    // 获取当前根节点的值并新建一个节点
    int rootVal = postorder[postIndex--]; // 后序遍历的最后一个元素总是树的根。
    node<int> *root = new node<int>(rootVal);

    // 在中序遍历中找到根节点的位置
    int index = inMap[rootVal];

    // 递归构右子树和左子树
    // 后序遍历————先构建右子树，后构建左子树！！！！！！！！！
    root->right = buildTree_by_postAndIn(postorder, inorder, postIndex, index + 1, inEnd, inMap);
    root->left = buildTree_by_postAndIn(postorder, inorder, postIndex, inStart, index - 1, inMap);

    return root;
}

//遍历
void levelOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    queue<node<int> *> q;
    q.push(root);

    while (!q.empty())
    {
        node<int> *frt = q.front();
        q.pop();

        cout << frt->val << " ";

        if (frt->left != nullptr)
            q.push(frt->left);
        if (frt->right != nullptr)
            q.push(frt->right);
    }
    cout << endl;
}
void inOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// 清理内存函数
void deleteTree(node<int> *root)
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    // 输入前序遍历和中序遍历和后序遍历(可以根据需要改变输入)
    vector<int> postorder = {4, 5, 2, 6, 7, 3, 1}; // 后序遍历
    vector<int> inorder = {4, 2, 5, 1, 6, 3, 7};   // 中序遍历

    // 使用哈希表(unordered_map<int, int>)记录中序遍历元素的索引，快速查找元素的位置
    unordered_map<int, int> inMap;
    for (int i = 0; i < inorder.size(); i++)
        inMap[inorder[i]] = i;

    // 根据前序遍历和中序遍历构造二叉树
    int postIndex = postorder.size() - 1;
    node<int> *root = buildTree_by_postAndIn(postorder, inorder, postIndex, 0, inorder.size() - 1, inMap);

    // 输出结果
    cout << "inOrder: ";
    inOrder(root);
    cout << endl;

    cout << "levelOrder: ";
    levelOrder(root);
    cout << endl;

    // 清理内存
    deleteTree(root);

    return 0;
}
```

#### 细心阅读代码的朋友可能已经发现一个容易出错的小细节

我们用前序遍历和中序遍历递归构建二叉树时是 ***先左子树后右子树***

我们用后序遍历和中序遍历递归构建二叉树时是 ***先右子树后左子树***

原因就在于：

    前序遍历（Postorder）：根节点 -> 左子树 -> 右子树 
    后序遍历（Inorder）：左子树 <- 右子树 <- 根节点

![遍历](https://i-blog.csdnimg.cn/blog_migrate/55876a3ed345d10ae18930a3440bd087.png)

---
...

---
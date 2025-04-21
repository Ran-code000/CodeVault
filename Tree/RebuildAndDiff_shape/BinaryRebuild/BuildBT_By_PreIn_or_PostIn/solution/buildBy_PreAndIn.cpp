// 通过前序遍历和中序遍历递归构建二叉树

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// 定义树节点
template <typename T>
struct node
{
    T val;
    node<T> *left;
    node<T> *right;
    node(T val) : val(val), left(nullptr), right(nullptr) {}
};

// 根据前序和中序遍历构造二叉树
// preIndex 用来记录当前在前序遍历中的索引，inStart 和 inEnd 用来确定当前递归的中序遍历子数组的范围，inMap 用来快速查找元素在中序遍历中的位置。
node<int> *buildTree_by_preAndIn(const vector<int> &preorder, const vector<int> &inorder, int &preIndex, int inStart, int inEnd, unordered_map<int, int> &inMap)
{
    // 如果当前子树的中序范围无效（即开始索引大于结束索引），则返回空指针，表示没有子树
    if (inStart > inEnd)
        return nullptr;

    // 获取当前根节点的值
    int rootVal = preorder[preIndex++]; // 前序遍历的第一个元素总是树的根。
    node<int> *root = new node<int>(rootVal);

    // 在中序遍历中找到根节点的位置
    int index = inMap[rootVal];

    // 递归构建左子树和右子树
    // 前序遍历————先构建左子树，后构建右子树
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
void preOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}
void postOrder(node<int> *root)
{
    if (root == nullptr)
        return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
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
    cout << "preOrder: ";
    preOrder(root);
    cout << endl;
    cout << "inOrder: ";
    inOrder(root);
    cout << endl;
    cout << "postOrder: ";
    postOrder(root);
    cout << endl;

    cout << "levelOrder: ";
    levelOrder(root);
    cout << endl;

    // 清理内存
    deleteTree(root);

    return 0;
}
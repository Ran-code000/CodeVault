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
// 两个指针分别指向对应子树的根节点，递归检查
bool check(int ld, int rd, const vector<node> &t)
{
    if (ld == -1 && rd == -1)
        return true; // 如果两个子节点都是空，返回对称
    if (ld == -1 || rd == -1)
        return false; // 如果一个子节点为空，另一个不为空，返回不对称
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
    // 递归终止条件
    if (root == -1)
        return 0; // 如果当前节点为空，返回 0

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
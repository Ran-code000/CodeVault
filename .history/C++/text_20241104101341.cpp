#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int value;  // 节点权值
    int left;   // 左孩子索引
    int right;  // 右孩子索引
};

// 检查两个子树是否对称
bool isSymmetric(TreeNode* left, TreeNode* right, const vector<TreeNode>& tree) {
    if (!left && !right) return true;  // 都为空
    if (!left || !right) return false;  // 只有一个为空
    return (tree[left->value].value == tree[right->value].value) &&
           isSymmetric(tree[left->value].left == -1 ? nullptr : &tree[tree[left->value].left],
                       tree[right->value].right == -1 ? nullptr : &tree[tree[right->value].right],
                       tree) &&
           isSymmetric(tree[left->value].right == -1 ? nullptr : &tree[tree[left->value].right],
                       tree[right->value].left == -1 ? nullptr : &tree[tree[right->value].left],
                       tree);
}

// 计算最大对称子树的节点数
int maxSymmetricSubtree(TreeNode* node, const vector<TreeNode>& tree) {
    if (!node) return 0;

    int leftSize = maxSymmetricSubtree(tree[node->left == -1 ? -1 : node->left].left == -1 ? nullptr : &tree[tree[node->left].left], tree);
    int rightSize = maxSymmetricSubtree(tree[node->right == -1 ? -1 : node->right].right == -1 ? nullptr : &tree[tree[node->right].right], tree);

    int totalSize = 1; // 计算当前节点
    if (isSymmetric(node, node, tree)) {
        totalSize += leftSize + rightSize; // 如果当前节点的子树对称
    }

    return totalSize;
}

int main() {
    int n;
    cin >> n;
    vector<TreeNode> tree(n + 1); // 索引从 1 开始

    // 输入权值
    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].value;
    }

    // 输入左右子节点
    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].left >> tree[i].right;
    }

    int maxNodes = 1; // 至少有一个节点
    for (int i = 1; i <= n; ++i) {
        maxNodes = max(maxNodes, maxSymmetricSubtree(&tree[i], tree));
    }

    cout << maxNodes << endl;

    return 0;
}
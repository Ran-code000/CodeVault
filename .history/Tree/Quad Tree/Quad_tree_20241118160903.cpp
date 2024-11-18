#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// 定义哈夫曼树节点结构
struct Node {
    char ch;       // 字符
    int freq;      // 频率
    Node* left;    // 左子树
    Node* right;   // 右子树
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}  // 构造函数
    // 为了在优先队列中能按频率和字符排序，重载比较运算符
    bool operator>(const Node& other) const {
        if (freq == other.freq) return ch < other.ch;  // 如果频率相同，按字符逆序
        return freq > other.freq;  // 频率小的优先
    }
};

// 后序遍历输出字符
void postOrder(Node* root, vector<char>& result) {
    if (root == nullptr) return;
    postOrder(root->left, result);
    postOrder(root->right, result);
    if (root->ch != '#')  // 只输出叶子节点
        result.push_back(root->ch);
}

int main() {
    int K;
    cin >> K;  // 输入字符个数
    priority_queue<Node, vector<Node>, greater<Node>> pq;  // 最小堆（优先队列）

    // 输入字符和频率
    for (int i = 0; i < K; i++) {
        char ch;
        int freq;
        cin >> ch >> freq;
        pq.push(Node(ch, freq));
    }

    // 构建哈夫曼树
    while (pq.size() > 1) {
        // 取出频率最小的两个节点
        Node* left = new Node(pq.top()); pq.pop();
        Node* right = new Node(pq.top()); pq.pop();

        // 创建新节点
        Node* parent = new Node('#', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        // 将新节点加入优先队列
        pq.push(*parent);
    }

    // 最终剩下的节点是根节点
    Node* root = new Node(pq.top()); pq.pop();

    // 后序遍历并输出叶子节点的字符
    vector<char> result;
    postOrder(root, result);

    // 输出结果
    for (char c : result) {
        cout << c << endl;
    }

    return 0;
}
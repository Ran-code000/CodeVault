#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin >> n; // 读取节点数

    vector<int> parent(n + 1);           // 存储父节点信息
    vector<vector<int>> children(n + 1); // 存储每个节点的子节点

    // 读取父节点信息，并构建多叉树的子节点列表
    for (int i = 2; i <= n; ++i)
    {
        cin >> parent[i];
        children[parent[i]].push_back(i);
    }

    // 将多叉树转换为左儿子右兄弟形式
    // 为了方便，使用数组表示每个节点的"左儿子"和"右兄弟"
    vector<int> leftChild(n + 1, -1);    // 存储左儿子
    vector<int> rightSibling(n + 1, -1); // 存储右兄弟

    // 为每个节点设置左儿子和右兄弟
    for (int i = 1; i <= n; ++i)
    {
        if (children[i].empty())
            continue;
        // 第一个子节点是左儿子
        leftChild[i] = children[i][0];
        for (int j = 0; j < children[i].size() - 1; ++j)
        {
            // 当前节点的下一个子节点是当前子节点的右兄弟
            rightSibling[children[i][j]] = children[i][j + 1];
        }
    }

    // 层次遍历
    queue<int> q;
    q.push(1);          // 从根节点开始
    vector<int> result; // 用于保存层次遍历的结果

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        result.push_back(node);

        // 将左儿子加入队列
        if (leftChild[node] != -1)
        {
            q.push(leftChild[node]);
        }

        // 将右兄弟加入队列
        if (rightSibling[node] != -1)
        {
            q.push(rightSibling[node]);
        }
    }

    // 输出结果
    for (int i = 0; i < result.size(); ++i)
    {
        if (i > 0)
            cout << " ";
        cout << result[i];
    }
    cout << endl;

    return 0;
}
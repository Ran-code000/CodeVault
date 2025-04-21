#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class TreeNode
{
public:
  int leftChild;
  int rightSibling;

  TreeNode() : leftChild(-1), rightSibling(-1) {}
};

class Tree
{
private:
  vector<TreeNode> nodes;

public:
  Tree(int n) : nodes(n + 1) {} // 初始化树节点

  void addParent(int child, int parent)
  {
    if (nodes[parent].leftChild == -1)
    {
      nodes[parent].leftChild = child; // 设置左儿子
    }
    else
    {
      // 找到右兄弟
      int sibling = nodes[parent].leftChild;
      while (nodes[sibling].rightSibling != -1)
      {
        sibling = nodes[sibling].rightSibling;
      }
      nodes[sibling].rightSibling = child; // 设置右兄弟
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

      // 添加左儿子
      if (nodes[nodeIndex].leftChild != -1)
      {
        q.push(nodes[nodeIndex].leftChild);
      }
      // 添加右兄弟
      if (nodes[nodeIndex].rightSibling != -1)
      {
        q.push(nodes[nodeIndex].rightSibling);
      }
    }

    return result;
  }
};

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

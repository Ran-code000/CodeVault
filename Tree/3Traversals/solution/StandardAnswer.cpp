#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 标准定义节点的方式，简化数据结构
struct Node
{
  string name;
  size_t left;
  size_t right;
};
// 储存所有节点
vector<Node> nodes;

// 三种遍历方式
// 与MYAnswer.cpp不同的是，规范性；结果不直接输出，而是存在一个结果数组vector<string>& result里
void preorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  result.push_back(nodes[root].name);
  preorder(nodes[root].left, result);
  preorder(nodes[root].right, result);
}

void inorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  inorder(nodes[root].left, result);
  result.push_back(nodes[root].name);
  inorder(nodes[root].right, result);
}

void postorder(size_t root, vector<string> &result)
{
  if (root == 0)
    return;
  postorder(nodes[root].left, result);
  postorder(nodes[root].right, result);
  result.push_back(nodes[root].name);
}

int main()
{
  int n;
  cin >> n;

  // 节点编号从1开始，0作为空节点
  nodes.resize(n + 1);
  unordered_map<string, size_t> name2node; // 用于将节点名称映射到节点编号

  // 用法间 makeSense.txt
  auto get_node = [&](const string &name) -> size_t
  {
    if (name == "-")
      return 0; // 空子树
    if (name2node.find(name) == name2node.end())
    {
      name2node[name] = name2node.size() + 1; // 分配新节点编号
      nodes[name2node[name]].name = name;     // 设置节点名称
    }
    return name2node[name];
  };

  size_t root = 0;

  for (int i = 1; i <= n; ++i)
  {
    string name, left_name, right_name;
    cin >> name >> left_name >> right_name;
    size_t node = get_node(name);        // 获取当前节点编号
    size_t left = get_node(left_name);   // 左子节点编号
    size_t right = get_node(right_name); // 右子节点编号
    nodes[node].left = left;
    nodes[node].right = right;
    root ^= node ^ left ^ right;
  }

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
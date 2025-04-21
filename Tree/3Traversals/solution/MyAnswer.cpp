#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// unordered_map<string, pair<string, string>> tree;
// 更为清晰
unordered_map<string, string> lc;
unordered_map<string, string> rc;

// 标记是否为子节点便于去寻找根节点
unordered_map<string, bool> ischild;
vector<string> nodes;

void preOrder(string root)
{
    if (root == "-")
        return;

    cout << root << " ";
    preOrder(lc[root]);
    preOrder(rc[root]);
}
void inOrder(string root)
{
    if (root == "-")
        return;

    inOrder(lc[root]);
    cout << root << " ";
    inOrder(rc[root]);
}
void postOrder(string root)
{
    if (root == "-")
        return;

    postOrder(lc[root]);
    postOrder(rc[root]);
    cout << root << " ";
}

int main()
{
    int n;
    cin >> n;
    nodes.resize(n + 1);

    for (int i = 0; i < n; i++)
    {
        string root, l, r;
        cin >> root >> l >> r;

        nodes[i] = root;
        // tree[root] = {l, r};
        lc[root] = l;
        rc[root] = r;

        if (l != "-")
            ischild[l] = true;
        if (r != "-")
            ischild[r] = true;
    }

    string root;
    for (int i = 0; i < n; i++)
    {
        if (!ischild[nodes[i]])
        {
            root = nodes[i];
            break;
        }
    }

    preOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    postOrder(root);
    cout << endl;

    return 0;
}
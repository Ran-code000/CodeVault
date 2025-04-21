#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int res = 0;
void CountDiffShape(const string &pre, const string &post)
{
    if (pre.length() < 2)
        return;
    if (pre.length() == 2)
    {
        res++;
        return;
    }

    // 左右子树的根节点
    char leftSubTree_Node = pre[1], rightSubTree_Node = post[post.length() - 2];
    // 最终目的：找只有一颗子树的情况（因为此时中序遍历结果不唯一—————有两种情况）
    if (leftSubTree_Node == rightSubTree_Node)
    {
        // 左右子树的根节点相同————>只有一颗子树————>res++————>递归遍历该子树
        res++;
        string nextPre = pre.substr(1, pre.length() - 1), nextPost = post.substr(0, post.length() - 1);
        // 递归遍历子树
        CountDiffShape(nextPre, nextPost);
    }
    else
    { /*
		Q YUIO PAS
		OIUY ASP Q
      */
        // 左右子树的根节点不同————>有左右两颗子树————>将pre，post分割为左右两颗子树的pre,post（4个子段）————>递归遍历所有子树
        string leftSubTree_pre, leftSubTree_post, rightSubTree_pre, rightSubTree_post;
        // 分割为左右两颗子树的pre
        for (int i = 1; i < pre.length(); i++)
        {
            if (pre[i] == rightSubTree_Node)
            {
                leftSubTree_pre = pre.substr(1, ((i - 1) - 1) + 1), rightSubTree_pre = pre.substr(i, ((pre.length() - 1) - i) + 1);
                break;
            }
        }
        // 分割为左右两颗子树的post
        for (int i = post.length() - 2; i >= 0; i--)
        {
            if (post[i] == leftSubTree_Node)
            {
                leftSubTree_post = post.substr(0, (i - 0) + 1), rightSubTree_post = post.substr(i + 1, ((post.length() - 2) - (i + 1)) + 1);
                break;
            }
        }
        // 递归遍历左右两颗子树
        CountDiffShape(leftSubTree_pre, leftSubTree_post);
        CountDiffShape(rightSubTree_pre, rightSubTree_post);
    }
}
int main()
{
    string pre, post;
    cin >> pre >> post;
    CountDiffShape(pre, post);
    cout << (int)pow(2, res) << endl;
    return 0;
}
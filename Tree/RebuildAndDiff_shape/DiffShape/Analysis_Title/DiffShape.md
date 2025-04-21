# 二叉树的重建

***提要***： 建议看这篇之前先去了解二叉树的四种遍历方式[前序遍历，中序遍历，后序遍历和层序遍历](https://blog.csdn.net/2301_81373791/article/details/144098071?spm=1001.2014.3001.5501)

***问题引入***：

通过给定我们一颗二叉树，我们可以实现对这颗二叉树的遍历

question 1 ： 我们已知哪几种遍历方式可以 ***唯一*** 的确定一颗二叉树？ 并且我们怎么确定这颗二叉树？

question 2 ： 如果我们已知的遍历方式 ***不能唯一***的确定一颗二叉树， 那么可以有几种 ***不同形态***的二叉树？

---

......

---

## 解决question 2

***如果我们只是已知前序遍历和后序遍历，而不知道中序遍历，我们肯定无法唯一的确定一颗二叉树，但是二叉树形态肯定是有限的，那究竟有多少个不同形态，怎么求出这些不同的形态呢***

![](https://i-blog.csdnimg.cn/blog_migrate/71b78733e975e2fb6b786c7fce5ec344.png) 
![](https://i-blog.csdnimg.cn/blog_migrate/7c55c04ba26b57f6f2be813be14ffd18.png)

思考过程（非常有助于理解的推导思路）：

    由于我们不知道中序遍历，我们就无法唯一的确定二叉树，那么中序遍历有哪些特别的作用？

    没错，特别的作用就是我们前面提到的它可以唯一确定根的位置，那么现在我们显然不能唯一确定根的位置，也就是说根可能有左右两个位置，也就是说一棵子树的根可能是左子树的根也可能是右子树的根，也就是说此时的根节点只有一个子树，那么我们怎么通过两个遍历序列（前和后）判断此时的根节点 只有一个子树 呢？

    我们又知道构建二叉树时，我们的索引指针前序遍历的顺序是根节点 -> 左子树 -> 右子树，后序遍历的顺序是根节点 -> 右子树 -> 左子树，由于我们前提一直是元素无重复，所以不可能左右根节点值相同，所以如果相同，那么就必然只有一个根节点，即如果 判断 pre[0 + 1] == post[(post.size() - 1) - 1] 为真，就说明左右根节点相同


### 方案一：

特判：

（1） 如果当前序列只有两个元素很明显它满足只有一个子树的条件，直接 res 加 1 返回。

（2） 如果当前序列少于两个元素很明显它没有不同的形态，直接返回

正常情况：

1. ***给出前序和后续遍历序列，从根节点开始，依次查找该节点的左右子树的根节点是否相同（即检查当前根节点是否只有一个子树）***`leftSubTree_Node == rightSubTree_Node`

![遍历](https://i-blog.csdnimg.cn/blog_migrate/55876a3ed345d10ae18930a3440bd087.png)
依旧按照上图所示的例子，就可以发现左子树的根节点就在前序遍历的第二个位置，右子树的根节点就在后序遍历的倒数第二个位置（此时是不相等的情况，即此时有两颗子树）

1. ***如果相同，递归遍历那唯一的一颗子树（前序nextPre和后序nextPost遍历序列）***

2. ***如果不相同，分别递归遍历左右两颗子树（左子树前序leftSubTree_pre和左子树后序leftSubTree_post, 右子树前序rightSubTree_pre, 右子树后序rightSubTree_post）***


```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int res = 0;
void CountDiffShape(const string &pre, const string &post)
{   
    //当前序列少于两个元素很明显它没有不同的形态，直接返回
    if (pre.length() < 2)
        return;
    //当前序列只有两个元素很明显它满足只有一个子树的条件，直接 res 加 1 返回
    if (pre.length() == 2)
    {
        res++;
        return;
    }

    // 左右子树的根节点
    char leftSubTree_Node = pre[1], rightSubTree_Node = post[post.length() - 2];

    // 判断左右子树的根节点是否相同
    // 最终目的：找只有一颗子树的情况（因为此时中序遍历结果不唯一———>有两种情况）

    // 左右子树的根节点相同————>只有一颗子树————>res++————>递归遍历该子树
    if (leftSubTree_Node == rightSubTree_Node)
    {
        res++;
        //nextPre : 唯一的子树的前序遍历序列, newtPost : 唯一的子树的后序遍历序列
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

//test function
int main()
{
    string pre, post;
    cin >> pre >> post;
    CountDiffShape(pre, post);
    cout << (int)pow(2, res) << endl;
    return 0;
}
```

### 方案二：（优化）

#### 1. 我们将算法进一步抽象，由于一棵树的根节点唯一，即前序遍历第一个值和后序遍历的最后一个值必然相同；

#### 2. 我们找的条件是左右子树的根节点相同，也就是前序遍历第二个值和后序遍历的倒数第二个值相同；

#### 3. 综上，如果说前序遍历正序连续两个值和后序遍历逆序连续两个值如果相同，就说明出现了子树唯一的情况

#### 4. 所以我们只需查找字符串即可

话不多说上代码

```cpp
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int res = 0;
int main()
{
    string pre, post;
    cin >> pre >> post;
    for (int i = 0; i < pre.length() - 1; i++)
    {
        string temp;
        //因为是逆序相等，比如说 AB CDRFTG 和 GFTRDC BA
        temp += pre[i + 1], temp += pre[i];
        //如果前序遍历正序连续两个值和后序遍历逆序连续两个值相同
        if (post.find(temp) != -1)
            //结果加一
            res++;
    }
    cout << (int)pow(2, res);
    return 0;
}

```

#### 补充说明

    至于为什么最后结果需要 (int)pow(2, res)，是因为

    我们找到 n 个满足只有唯一子树的节点，有 n 个不同的满足情况节点的话就有 2^n 种不同的树满足给定的前序遍历和后序遍历


# 四叉树的构建（**乱序插入**）

## 题目描述

四叉树的实现
 
问题描述
四叉树将二维空间划分成四个象限，每一个节点最多有四个子节点，表示左上、右上、左下、右下四个子区域，平均划分了父节点的区域范围，每个子节点只包含一个数据。

给定一个二维空间范围x∈[0,10]，y∈[0,10]，给定若干个点，请构造一个四叉树并按照层序遍历的顺序输出每个点。

输入
包含两个部分，第一个整数K表示K个点，接下来K行表示每个点的坐标，在限定的空间范围内，处于分界线上的点水平分界线的归到下方，垂直分界线归到左方。

输出
K行为层序遍历的结果。

样例输入
7
2 5
3 7.5
4.2 6.8
5 2.5
8 5.6
7 3.5
5.5 3.5
​
样例输出
8 5.6
2 5
5 2.5
3 7.5
4.2 6.8
5.5 3.5
7 3.5
​
## 代码实现

**核心思路**

进入**插入**函数：

———>判断插入的节点是否在合规区域内

———>判断是否是叶节点

———>是———>插入节点并返回

———>不是———>分裂为四个子节点———>在子节点序列中**插入**原节点，新节点（递归调用）——>父节点值清空

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//本质：遵循四叉树的定义构造树的结构

// 节点定义
struct NTreeNode
{
    // 渲染范围
    double x_min, x_max, y_min, y_max;
    // 节点值
    pair<double, double> point;
    // 子节点（如果需要分裂）
    NTreeNode *child[4];
    //叶子节点标志（用于找到根节点）
    bool isleafNode;

    NTreeNode(double xmin, double xmax, double ymin, double ymax) : x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), isleafNode(true)
    {
        point = {-1, -1};
        // 子节点指针初始化为空
        fill(begin(child), end(child), nullptr);
    }
    //节点合规性判断
    bool iscontained(double x, double y) 
    {
        return x >= x_min && x <= x_max && y >= y_min && y <= y_max;
    }
    void split()
    {   
        // false:
        // double x_mid = x_min + ((x_max - x_min) >> 1);
        // double y_mid = y_min + ((y_max - y_min) >> 1);
        //true:
        double x_mid = (x_min + x_max) / 2.0;
        double y_mid = (y_min + y_max) / 2.0;

        child[0] = new NTreeNode(x_min, x_mid, y_min, y_mid);
        child[1] = new NTreeNode(x_min, x_mid, y_mid, y_max);
        child[2] = new NTreeNode(x_mid, x_max, y_min, y_mid);
        child[3] = new NTreeNode(x_mid, x_max, y_mid, y_max);
        isleafNode = false;
    }
};
class NTree
{
private:
    NTreeNode *root;
    //插入方法的内部实现（外部提供接口即可）
    void insert(NTreeNode *&node, double x, double y)
    {
        if (!node->iscontained(x, y))
            return;
        if (node->isleafNode) //如果是叶子节点
        {
            if (node->point.first == -1) //如果当前节点没有值
                node->point = {x, y}; //则直接赋值
            else //如果当前节点已经有值
            {
                node->split(); //分裂为四个子节点
                insertTochild(node, node->point.first, node->point.second); //原父节点退化为子节点，将当前父节点插入到子节点序列中
                node->point = {-1, -1}; //清空父节点（本四叉树中所有父节点均为无实值的节点）
                insertTochild(node, x, y); //将当前子节点插入到子节点序列中
            }
        }
        else //如果不是叶子节点（已经分裂过了）
        {
            insertTochild(node, x, y); //将当前子节点插入到子节点序列中
        }
    }
    void insertTochild(NTreeNode *node, double x, double y)
    {
        for (int i = 0; i < 4; i++) //遍历子节点序列
        {
            if (node->child[i]->iscontained(x, y)) //选择包含节点的区域插入
            {
                insert(node->child[i], x, y);
                break;
            }
        }
    }

public:
    NTree()
    {
        //初始化平面范围到全平面范围
        root = new NTreeNode(0, 10, 0, 10);
    }
    //插入方法的接口
    void insert(double x, double y)
    {
        insert(root, x, y);
    }
    //层序遍历
    void levelorder()
    {
        queue<NTreeNode*> q;
        q.push(root); //根节点入队，从根节点开始遍历

        while (!q.empty())
        {
            NTreeNode *currNode = q.front();
            q.pop();

            if (!currNode->isleafNode) //当前的节点不是叶子节点（父节点值无效），需要遍历子节点
            {
                for (int i = 0; i < 4; i++)
                    if (currNode->child[i]) //非空子节点入队
                        q.push(currNode->child[i]);
            }
            else //当前的节点是叶子节点
            {
                if (currNode->point.first != -1) //如果当前节点有值，则直接输出
                    cout << currNode->point.first << " " << currNode->point.second << endl;
            }
        }
    }
};

int main()
{
    int n;
    cin >> n;
    NTree nt;
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        nt.insert(x, y);
    }
    nt.levelorder();
    return 0;
}
```
# ***哈夫曼树***

## 必备知识

哈夫曼树 (Huffman Tree): 
     
     1.一种用于数据压缩的二叉树，基于字符的频率构建。

     2. 是基于一个加权的完全二叉树，树中的每个节点代表一个字符（或数据元素）及其频率（或权重）。
     
     3. 核心思想是：将频率较低的元素放在树的较深位置，而将频率较高的元素放在较浅位置，这样可以实现最短的编码。

     4.哈夫曼树的构建算法主要采用贪心算法

     5. 每个字符的编码长度与其频率成反比，频率越高的字符，编码越短。
---

## 过程图解


（1）全部初始化为叶节点（只有根节点的树）

![1](https://i-blog.csdnimg.cn/blog_migrate/acdb6c5b36b4fb2b58d1c4cbaa176efb.png)

（2）选择字符频率最小的两个造新树

![1](https://i-blog.csdnimg.cn/blog_migrate/57e8026598960f0dbf69e16ac858b428.png)


（3）删除原字符频率最小的两个节点，添加新节点（那两个节点的父节点）

![1](https://i-blog.csdnimg.cn/blog_migrate/7639e165d1b4892de15864e3f2ddac0c.png)

（4）重复（2）（3）直到剩一个节点

![1](https://i-blog.csdnimg.cn/blog_migrate/edea6726e75ed5d793a96ed1a21c9ab5.png)


## 例题详解

---
### 例 1 ：哈夫曼树编码（易）
---

#### 题目描述

```txt
哈夫曼树编码

问题描述
哈夫曼树编码
给定K个不同的字符和它们的频率，建立一棵哈夫曼树对字符进行编码，合并后的节点字符设为#。合并节点时频率小的在右边，频率相同时字符小的在右边，频率和字符都相同时，后生成的节点放右边。节点频率相同的时候优先选取节点字符值大的先进行结合。

要求按照后序遍历的顺序输出哈夫曼树中叶子节点的字符。
输入包含两部分，第一部分一个数字K表示有K个字符，第二部分有K行，每行两个数表示字符和它的频率。

样例输入
7
A 5
F 5
C 7
G 13
E 34
B 24
D 17
​
​
样例输出
E
D
G
B
F
A
C

```
---
#### 实现思路


***递归判断***
AVL

由于我们针对的是 AVL 树，忘了见[对应知识点--AVL](#1概念介绍)

     1. 设置递归终止条件
   
          空节点：返回 true

     2. 递归判断当前节点左右子树是否平衡并得到左右子树的高度
          
     3. 计算当前节点的左右子树高度差的绝对值是否超过 1
---
#### 实现代码

```cpp
#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

// 哈夫曼树节点定义
struct HuffmanNode
{
     char data;
     int freq;
     HuffmanNode *left;
     HuffmanNode *right;
     HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// 排序规则
struct _Compare
{
     bool operator()(HuffmanNode *a, HuffmanNode *b)
     {
          if (a->freq == b->freq)
               return a->data > b->data;
          else
               return a->freq > b->freq;
     }
};
// 哈夫曼树类
class HuffmanTree
{
     // 哈夫曼树根节点
    HuffmanNode *root;

    // 后序遍历输出内部方法实现
    void postOrder(HuffmanNode *root, vector<char> &result)
    {
        if (root == nullptr)
            return;
        postOrder(root->left, result);
        postOrder(root->right, result);
        if (root->data != '~')
            result.push_back(root->data);
    }

     // 内存清理内部方法实现
     void DeleteHuffmanTree(HuffmanNode *node)
    {
     
        if (node)
        {
            DeleteHuffmanTree(node->left);
            DeleteHuffmanTree(node->right);
            delete node;
        }
    }
    

public:
    HuffmanTree() : root(nullptr) {}
    ~HuffmanTree() { DeleteHuffmanTree(root); }

    //建树
    void buildHuffmanTree(const vector<pair<char, int>> &frequencies)
    {
        // 用按给定排序规则建堆
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, _Compare> minHeap;
        // 创建叶节点并加入优先队列
        for (const auto &pair : frequencies)
            minHeap.push(new HuffmanNode(pair.first, pair.second));

        // 构建 HuffmanTree，直到待构造队列中只剩一个节点
        while (minHeap.size() > 1)
        {
            HuffmanNode *r = minHeap.top();
            minHeap.pop();
            HuffmanNode *l = minHeap.top();
            minHeap.pop();
            // 创建新父节点（freq = 左右节点之和）
            HuffmanNode *newnode = new HuffmanNode('~', l->freq + r->freq);
            // 连接节点！！！！！！
            newnode->left = l;
            newnode->right = r;
            minHeap.push(newnode);
        }
        root = minHeap.top();
    }
    // 内存清理
    void DeleteHuffmanTree()
    {
        DeleteHuffmanTree(root);
    }
    //后续遍历
    void postOrder(vector<char> &result)
    {
        postOrder(root, result);
    }
};
// text fun
int main()
{
    int n;
    cin >> n;
    vector<pair<char, int>> frequencies;
    while (n--)
    {
        char ch;
        int x;
        cin >> ch >> x;
        frequencies.push_back({ch, x});
    }
    // 构建哈夫曼树
    HuffmanTree huffmantree;
    huffmantree.buildHuffmanTree(frequencies);
    vector<char> result;
    huffmantree.postOrder(result);
    for (const char ch : result)
        cout << ch << endl;
     huffmantree.DeleteHuffmanTree();
    return 0;
}

```

---
#### 易出现的错误解释：

细心的朋友发现，代码实现和题目描述有两个不同之处


          1. 题目要求的有三个排序逻辑，而我们代码的比较逻辑中只有前两个判断逻辑

          （1）合并节点时频率小的在右边
          （2）节点频率相同的时候优先选取节点字符值大的先进行结合
          （3）频率和字符都相同时，后生成的节点放右边。

          怎么回事？是我们忘记加了侥幸通过了吗？ 

          2. 为什么题目要求的根节点字符是 '#'，而我这里却用了 '~'

问题 1 思考：我们要怎么更高效的判断插入节点的先后顺序而不是多加一个标记节点先后次序的变量？

          显然 ： 后插入的节点的根节点是 '#'，显然与正常插入的字符节点不同，那我们就可以用这个不同之处将 （2）（3）的判断逻辑合并

          即 节点频率相同时，优先选取节点字符值大的或根节点不为 '#' 先进行结合
          
          即 大写字母 < 小写字母，'后加入的根节点字符' > 任意字母

但现在又发现，ascall 码中 大写字母 < 小写字母，但'#' = 35 < 大写字母

简单，用'~'即可

![ascall](https://i-blog.csdnimg.cn/blog_migrate/09cfcbeb6c6e17fddd71c0f134fb68dd.gif#pic_center)

---

我们知道哈夫曼树是基于一个加权的完全二叉树，树中的每个节点代表一个字符（或数据元素）及其频率（或权重）

例题 1 我们用字符比较规则构建了哈夫曼树，

例题 2 我们将为一个已经成功构建的哈夫曼生成前缀哈夫曼编码

（最优的前缀编码，即没有任何一个编码是另一个编码的前缀，避免了编码歧义）

---
相比例题1 ，添加了 ***generateHuffmanCodes，encode，decode 方法***，建树方法前面已讲，重点关注这三个新添加的方法

---

看图直观理解
![tu](https://i-blog.csdnimg.cn/blog_migrate/0eeeeeeb4b19f884edff22dc0aa186c1.png)
#### 实现代码

```cpp

#include <iostream>
#include <chrono>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
//节点定义
struct HuffmanNode
{
    char data;
    int freq;
    HuffmanNode *l;
    HuffmanNode *r;
    HuffmanNode(char data, int freq) : data(data), freq(freq), l(nullptr), r(nullptr) {}
};
// 比较函数
bool COMP(HuffmanNode *a, HuffmanNode *b) { return a->freq > b->freq; }

class HuffmanTree
{
     HuffmanNode *root;

     //生成哈夫曼编码内部方法实现！！
    void generateHuffmanCodes(HuffmanNode *root, const string &code, unordered_map<char, string> &HuffmanCodes)
    {     
        // 递归终止条件
        if (root == nullptr)
            return;
        // 对当前节点的判断，如果是叶节点，则记录其编码
        if (root->l == nullptr && root->r == nullptr)
            HuffmanCodes[root->data] = code;
        // 向左子树递归加 "0"
        generateHuffmanCodes(root->l, code + '0', HuffmanCodes);
        // 向右子树递归加 "1"
        generateHuffmanCodes(root->r, code + '1', HuffmanCodes);
    }

public:
    HuffmanTree() : root(nullptr) {}
    ~HuffmanTree() { DeleteHuffmanTree(root); }
    // 建树（同例 1），可以跳过不看
    void buildHuffmanTree(const vector<pair<char, int>> &frequencies)
    {
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, decltype(&COMP)> minHeap(COMP);
        // 创建叶节点并加入优先队列
        for (const auto &pair : frequencies)
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        // 合并最小频率节点，直到队列中只剩一个节点
        while (minHeap.size() > 1)
        {
            HuffmanNode *l = minHeap.top();
            minHeap.pop();
            HuffmanNode *r = minHeap.top();
            minHeap.pop();
            // 创建新的父节点（freq = 左右节点之和）
            HuffmanNode *newnode = new HuffmanNode('\0', l->freq + r->freq);
            // 连接节点！！！！！！
            newnode->l = l;
            newnode->r = r;
            // 将新创建的父节点插回到队列中
            minHeap.push(newnode);
        }
        root = minHeap.top();
    }
    // 生成哈夫曼编码
    void generateHuffmanCodes(const string &code, unordered_map<char, string> &HuffmanCodes)
    {
        generateHuffmanCodes(root, code, HuffmanCodes);
    }
    //内存清理
    void DeleteHuffmanTree(HuffmanNode *node)
    {
        if (node)
        {
            DeleteHuffmanTree(node->l);
            DeleteHuffmanTree(node->r);
            delete node;
        }
    }
    // 哈夫曼编码！！
    const string encode(const string &a, unordered_map<char, string> huffmanCodes)
    {
        string encodedStr;
        for (const char &c : a)
            encodedStr += huffmanCodes[c];
        return encodedStr;
    }
    // 哈夫曼译码！！
    const string decode(const string &a)
    {
        HuffmanNode *curr = root;
        string decodedStr;
        for (const char &c : a)
        {
            curr = (c == '1') ? curr->r : curr->l;
            if (curr->l == nullptr && curr->r == nullptr)
            {
               decodedStr += curr->data;
               curr = root;
            }
        }
        return decodedStr;
    }
};
// text fun
int main()
{
    auto start = chrono::high_resolution_clock::now();
    // 示例字符频率
    vector<pair<char, int>> frequencies = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    cout << "{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}\n\n";
    // 构建哈夫曼树
    HuffmanTree huffmantree;
    huffmantree.buildHuffmanTree(frequencies);
    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    huffmantree.generateHuffmanCodes("", huffmanCodes);
    // 输出哈夫曼编码
    cout << "Huffman Codes:\n";
    for (const auto &pair : huffmanCodes)
        cout << pair.first << ": " << pair.second << endl;
    // 哈夫曼编码
    const string input = "abcdef";
    cout << input << endl;
    const string encoded = huffmantree.encode(input, huffmanCodes);
    cout << "Encoded: " << encoded << endl;
    // 哈夫曼解码
    const string decoded = huffmantree.decode(encoded);
    cout << "Decoded: " << decoded << endl;

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "runnning time: " << duration << "μs" << endl;
    return 0;
}

```

---

细心读例 1， 例 2 代码的朋友可能注意到我们定义自定义比较函数的方法并不同

这是一个非常考验你 c++ 功底的地方，如果想深入了解请见附录[比较函数问题](#比较函数的定义)

---



# 附录

## 比较函数的定义

（1）比较函数类

```cpp
//函数对象（仿函数）
struct Compare {
    bool operator()(int a, int b) {
        return a > b; // 大顶堆
    }
};

//对应的最小堆构造为
priority_queue<int, vector<int>, Compare> minHeap;

```

（2）普通函数

```cpp

// 普通函数
bool COMP(int a, int b) {
    return a > b; // 大顶堆
}

//对应的最小堆构造为
priority_queue<int, vector<int>, decltype(&COMP)> minHeap(COMP);
```

（3）静态函数
```cpp
// 在类中定义的静态函数
static bool COMP(HuffmanTree::HuffmanNode* a, HuffmanTree::HuffmanNode* b) { return a->freq > b->freq;}

//对应的最小堆构造为
priority_queue<int, vector<int>, decltype(&COMP)> minHeap(COMP); 
```

### 解释

     在标准库的容器和算法中，例如 priority_queue，通常需要一个比较函数或函数对象来定义元素的排序规则

     由于模板参数是类型

     所以
     （1）当构造比较函数是通过函数对象 : 类名本身是自定义的类型名，直接传类名
     （2）构造比较函数是通过函数（静态成员或者非成员） : 函数名不是类型名，所以不能直接串函数名，要传 decltype(&函数名)，还需要传入实体
                    
          为什么要传 decltype(&函数名)？
          
               因为需要使用decltype(&函数名)来获取函数指针的类型
          
          为什么需要函数指针的类型？
          
               因为函数指针是一个具体的类型。
               因此模板参数仍然是类型参数，但这个类型是函数指针类型。
                    
               例如：compare是一个普通函数，其类型为bool(*)(int, int)

# 玩转二叉树（概念 + 图解 + 例题代码详解）

## 一、树的概念

我们知道在计算机什么是树吗？是二月春风似剪刀吗？哈哈哈哈哈哈显然不是

我们看下面这张图，可以观察到树的一些特征

![树](https://i-blog.csdnimg.cn/blog_migrate/8f95571559605bca995ce1e094b95698.png)
（！！！具体层数和树高从 0 开始还是从 1 开始不同的书定义不同，这里统一采用从 1 开始）

### 1、树的特征

(1) 树是非线性的数据结构，是 ***递归***定义的（连通性）

(2) 子树之间不能有任何交集（无环性）

(3) 一颗 N 个节点的树有 N-1 条边（定义）

---

![树](https://i-blog.csdnimg.cn/blog_migrate/75975b72dc916cac94c95d02f61551a6.png)

### 2、树的相关名词术语

1、节点的度：

     一个节点含有的子树的个数称为该节点的度； 
     
     如上图：A的度为6

2、叶节点/终端节点：
     
     度为 0 的节点称为叶节点； 
     
     如上图：B、C、H、I...等节点为叶节点

3、非叶节点/非终端节点/分支节点：

     度不为 0 的节点； 
     
     如上图：D、E、F、G...等节点为分支节点

4、父节点/双亲节点：

     若一个节点含有子节点，则这个节点称为其子节点的父节点； 
     
     如上图：A 是 B 的父节点。

5、子节点/孩子节点：

     一个节点含有的子树的根节点称为该节点的子节点； 
     
     如上图：B 是 A 的孩子节点

6、兄弟节点：

     具有相同父节点的节点互称为兄弟节点； 
     
     如上图：B、C 是兄弟节点

7、树的度：

     一棵树中，最大的节点的度称为树的度； 

     如上图：树的度为 6

8、节点的层次：

     从根开始定义起，根为第 1 层，根的子节点为第 2 层，以此类推；

9、 树的高度或深度：
     
     树中节点的最大层次； 
     
     如上图：树的高度为 4（若定义根为第一层，空树为第 0 层；若定义根节点为第零层，则空树为 -1 层。）

10、堂兄弟节点：

     双亲在同一层的节点互为堂兄弟；
     
     如上图：H、I互为兄弟节点

11、节点的祖先：

     从根到该节点所经分支上的所有节点；
     
     如上图：A是所有节点的祖先

12、子孙：

     以某节点为根的子树中任一节点都称为该节点的子孙。
     
     如上图：所有节点都是A的子孙

13、森林：

     由m（m > 0）棵互不相交的树的集合称为森林；

14、树的高度，深度和层数

     说法不一：

     总结来看有两种说法

     1. 高度就是深度
     2. 看层数：
          （1）如果根结点为第 0 层时，层数 = 深度 = 高度 - 1
          （2）如果根结点为第 1 层时，层数 = 深度 = 高度

说法 2（2）（考研采用，看层数，根节点为 1 的说法）

如图：树的高度和深度都为 4 ( 看层数 )；节点 8 的深度为 3；节点 9 的高度为 2；

![1](https://i-blog.csdnimg.cn/blog_migrate/d39961f7aed0ec6cc06a81a736b90d1b.png)



说法 2 ：根结点为第 0 层时 ------------------------说法 2 ：根结点为第 1 层时

![2](https://i-blog.csdnimg.cn/blog_migrate/ca88585c2cc5c59067d8cc0326946056.jpeg)
![2](https://i-blog.csdnimg.cn/blog_migrate/af828fa7ae7ecb482c2945aae42df55b.jpeg)


---
---

## 二、树的两种表示方法

详细介绍 + 代码讲解见[多叉树转二叉树](https://blog.csdn.net/2301_81373791/article/details/144121530?spm=1001.2014.3001.5501)

### 1. 左孩子右兄弟表示法

![左孩子右兄弟](https://i-blog.csdnimg.cn/blog_migrate/c6d6323e77d554e223e11fdb5fa84d4c.jpeg)

### 2. 双亲表示法

![双亲表示法](https://i-blog.csdnimg.cn/blog_migrate/84066ce1b6349fec9f47a08da56d2e3e.jpeg)

---
---

## 三、特殊二叉树（***敲重点！！！！！！！！！！！***）

***文字概念枯燥，我们结合图来直观理解，后面给出这些特殊的二叉树之间的集合关系，非常有助于理解记忆***

     提前说明：我非常非常非常不喜欢满二叉树这种**叫法！！！

     because:  

     “满二叉树(full)” 的定义在国内和国外完全不同，

     国内指“完美二叉树(perfect)”
     国外指“正则二叉树(strict)”，

     所以处于学术的严谨性，我们将不采用 满二叉树 这个搞笑的叫法，不同的分类采用 完美二叉树 和 正则二叉树 就不容易混淆

### 1.概念介绍

（1）二叉树 (Binary Tree): 

     所有树的基础结构。

![](https://i-blog.csdnimg.cn/img_convert/7698109585209b299a6dd579fbea300d.png)

（2）正则二叉树 (Regular Binary Tree): 

     可能不完全满，但每个节点要么有两个子节点，要么是叶子节点。

（哈夫曼树是一种正则二叉树，后面会涉及有关哈夫曼树的知识点）

![](https://i-blog.csdnimg.cn/blog_migrate/b5c9d54b3caa145b98c94f37335f7b23.png#pic_center)

（3）完全二叉树 (Complete Binary Tree): 
     
     除了最后一层，其他层都是满的，且最后一层的节点从左到右填充。

![](https://i-blog.csdnimg.cn/blog_migrate/76622a05f6839fd47c2224ff013b68a4.png)

（4）完美二叉树 (Perfect Binary Tree): 

     所有内部节点都有两个子节点，且所有叶子节点在同一层。

![](https://i-blog.csdnimg.cn/blog_migrate/1671e89091485241b62244d5a9eb18d3.png#pic_center)

（5）二叉查找树/二叉搜索树 (Binary Search Tree, ***BST***): 

     左子树的所有节点值小于根节点值，右子树的所有节点值大于根节点值。

![](https://i-blog.csdnimg.cn/img_convert/f39cce652427434d415ab68a158b0b89.jpeg)

（6）AVL树 (***AVL*** Tree): 

     一种自平衡的二叉查找树，任何节点的两个子树的高度最大差为1。
     
所有的 AVL树 都是 二叉查找树 （BST）

![](https://i-blog.csdnimg.cn/blog_migrate/c6571d7a46ab1237dde42275cddc053d.png)

AVL
![](https://i-blog.csdnimg.cn/direct/441e85cae55245d196b770492dc8cb51.png)


（7）红黑树（RBT）

     自平衡的二叉查找树，它的节点的颜色为红色和黑色。
     
     它不严格控制左、右子树高度或节点数之差小于等于1。
     
     是一种解决二叉查找树极端情况的数据结构

![](https://i-blog.csdnimg.cn/blog_migrate/e809cee865f34d5ce73016b78e429471.png)

（8）哈夫曼树 (Huffman Tree): 
     
     一种用于数据压缩的二叉树，基于字符的频率构建。

     是基于一个加权的完全二叉树，树中的每个节点代表一个字符（或数据元素）及其频率（或权重）。
     
     核心思想是：将频率较低的元素放在树的较深位置，而将频率较高的元素放在较浅位置，这样可以实现最短的编码。

     哈夫曼树的构建算法主要采用贪心算法

     每个字符的编码长度与其频率成反比，频率越高的字符，编码越短。

![](https://i-blog.csdnimg.cn/blog_migrate/edea6726e75ed5d793a96ed1a21c9ab5.png)

（9）线索化树 (Threaded Binary Tree): 

     在树的空指针中插入指向前驱和后继节点的线索，以便于遍历。

这里展示的是中序线索化
![](https://i-blog.csdnimg.cn/blog_migrate/3533caf79328f1cfcaf42e08b3ac204b.png)

---

***ps: B树/B-树 和 B+树 是独立于二叉树的结构，因此它们不在二叉树的层次结构中***

     B树/B-树 和 B+树 ：

     B树/B-树 (B-Tree): 

          一种自平衡的多路搜索树，适用于存储在外部存储器中的数据。

     B+树 (B+ Tree): 

          B树的一种变种，所有值都在叶子节点上，内部节点只作为索引。

回顾 AVL树
![](https://i-blog.csdnimg.cn/direct/441e85cae55245d196b770492dc8cb51.png)

B树/B-树 可以理解成 AVL 的泛化，把平衡二叉树的核心思想再增强一个档次 绝对平衡 ---所有子树 必须一样高
![](https://i-blog.csdnimg.cn/direct/040f5c31db2b4f5da2669dc0901536a6.png)

     
B+树 B树的一种变种，所有值都在叶子节点上，内部节点只作为索引
![](https://i-blog.csdnimg.cn/direct/97367d053d154e6fbbf081c0673302d1.png)

---

### 2. 二叉树的集合关系表示

```txt
        正则二叉树
       ┌───────────┐
       │           │
       │ 完美二叉树 │
       │           │
       └───────────┘
        完全二叉树


二叉搜索树 (Binary Search Tree, BST)
├── AVL树 (AVL Tree)
└── 红黑树 (Red-Black Tree)
```

---
---
---

# 特殊二叉树有关例题代码详解

## 例题组 1 ：（对应知识点 : ***完全二叉树***）

### 完全二叉树必备知识点：

     完全二叉树索引特点：（例1）
     （1）如果 i = 1，它是根节点
     （2）如果 i > 1，它的父节点编号为 floor(i / 2)
     （3）如果 2i <=  n，它的左子节点编号为 2i
     （4）如果 2i + 1 <= n，它的右子节点编号为 2i + 1
     
     完全二叉树节点个数和树高之间的关系：（例2）
     （1）高度为 h 的完全二叉树，有 2 ^ h - 1 个结点
          
          等比数列推导 1 + 2 + 2 ^ 2 + 2 ^ 3 + ...... + 2 ^ (h - 1) = 1 * (1 - 2 ^ h) / (1 - 2) 
                                                                   = 2 ^ h - 1

     （2）具有 n 个结点的完全二叉树的高度为 ceil(log2 (n+1))，或者 floor(log2 n) + 1 

          高度为 h - 1 的完全二叉树节点个数最多为 2 ^ (h - 1) - 1
          高度为 h 的完全二叉树节点个数最多为 2 ^ h - 1，最少为 2 ^ (h - 1)

          推导：2 ^ (h - 1) - 1 < n <= 2 ^ h - 1 或 2 ^ (h - 1) <= n < 2 ^ h;
               两边取对数得 ceil(log2 (n+1)) 或 floor(log2 n) + 1

      (3) 第 k 层(从上往下)至多有 2 ^（k - 1）个结点

      (4) 深度和高度

![树的深度和高度](https://i-blog.csdnimg.cn/blog_migrate/d39961f7aed0ec6cc06a81a736b90d1b.png)
     
          如图：树的高度和深度都为 4 ( 看层数 )；
          节点 8 的深度为 3；节点 9 的高度为 2；

---
### 例 1 ：完全二叉树-最近公共祖先（易）
---
#### 题目描述

```txt
完全二叉树-最近公共祖先

如下图，由正整数1，2，3，...组成一棵无限大的完全二叉树。

从某一个结点到根结点（编号是1的结点）都有一条唯一的路径，
比如10到根节点的路径是(10,5,2,1)，由4到根节点的路径是(4,2,1)，从根结点1到根结点的路径上只包含一个结点1，因此路径是(1)。

对于两个结点X和Y,假设它们到根结点的路径分别是(X1,X2,...,1)和(Y1,Y2,...,1)(这里显然有X=X1,Y=Y1)，那么必然存在两个正整数i和j，使得从Xi和Yj开始，Xi=Yj,Xi+1=Yj+1，...，

现在的问题就是，给定X和Y，要求Xi(也就是Yj)。


输入描述
输入的第一行是一个整数T，表示测试用例个数。以下T行，每行对应一个测试用例。
每个测试用例包括两个整数X和Y，这两个整数都不大于1000。

输出描述
对每个测试用例，单独一行输出一个整数Xi。

输入样例
2
10 4
7 13
​
输出样例
2
3
2
3
```
---
#### 实现思路

1. 首先需要明确祖先的定义

          我们知道 如果i > 1，

          它的父节点编号为floor(i / 2)，

          它的父亲的父亲的编号为floor(floor(i / 2) / 2)，

          祖父的编号为floor(floor(floor(i / 2) / 2) / 2)，
          
          以此类推......

2. 那我们找两个节点公共祖先即执行上述的循环

         循环中判断节点编号大小——>节点编号大的整除 2 ，
         
         循环跳出条件为找到相同的祖先(x == y)

---
#### 实现代码

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int find_common_parent(int x, int y)
{
    // 当 x 和 y 相同，意味着已经找到了公共父节点
    while (x != y)
    {
        if (x > y)
        {
            x /= 2; // 将x向上移动到父节点
        }
        else
        {
            y /= 2; // 将y向上移动到父节点
        }
    }
    return x; // 此时x == y，返回它们的公共父节点
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int x, y;
        cin >> x >> y;
        cout << find_common_parent(x, y) << endl;
    }
    return 0;
}
```

---
---

### 例 2 ：完全二叉树的节点个数（易+）

---
#### 题目描述

```txt
完全二叉树的节点个数

给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。

完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
若最底层为第 h 层，则该层包含 1 ~ 2 ^ h 个节点。


示例 1：
输入：root = [1,2,3,4,5,6]
输出：6

示例 2：
输入：root = []
输出：0

示例 3：
输入：root = [1]
输出：1
 

提示：

树中节点的数目范围是[0, 5 * 10^4]
0 <= Node.val <= 5 * 10^4

题目数据保证输入的树是 完全二叉树
 
进阶：遍历树来统计节点是一种时间复杂度为 O(n) 的简单解决方案。你可以设计一个更快的算法吗？
```
---
#### 实现思路


***遍历得到节点数太幼稚了我们不看，我们直接做进阶，尝试一个时间复杂度为 log^2 n 的算法***


由于我们针对的是完全二叉树，忘了见[对应知识点--完全二叉树](#例题组-1-对应知识点--完全二叉树)

          我们知道完全二叉树只有可能最后一层是不满的

          由于
          高度为 h - 1 的完全二叉树节点个数最多为 2 ^ (h - 1) - 1
          高度为 h 的完全二叉树节点个数最多为 2 ^ h - 1，最少为 2 ^ (h - 1)

          那么
          最大层数为 h 的完全二叉树，节点个数一定在 [2 ^ (h - 1), 2 ^ h - 1] 的范围内
          
      1. but 我们注意看题目中对高度的要求有点不同 “若最底层为第 h 层，则该层包含 1 ~ 2 ^ h 个节点”

           所以相应的(h 全部加 1)我们的节点个数范围就应该是 [2 ^ h , 2 ^ (h + 1) - 1]

      2. 现在的问题转换为在范围 [2 ^ h , 2 ^ (h + 1) - 1] 中查找，找到存在节点的最大节点编号（即第几个节点）

      3. 既然是查找，我们不难想到在该范围内通过二分查找的方式得到完全二叉树的节点个数
         
      4. 现在我们就需要找到从哪个节点开始查找，显然我们需要找的是完全二叉树的最底层最左边（节点编号在该层最小）的节点，
         
         因为该节点一定是叶子节点，因此从根节点出发，通过每次访问左子节点，找到查找开始节点并得到了树的高度，
         
         因此至此我们确定了查找范围的实值

      5. 当查找范围有效时，循环执行二分查找

      6. 现在重点来到了查找方法的实现!!!!!!

          （1）我们首先思考：二叉树是什么？
          
               之所以是二叉树而不是三叉树四叉树，就是一个根节点最多有两个子节点

               两个子节点就可以用两种状态表示，两种状态表示就可以用二进制数实现

![tu](https://i-blog.csdnimg.cn/img_convert/6297f4b4a95fc153c9a0fb3b5aaec3dc.png)

          （2）例如我们现在想找节点 12，我们知道 12 的二进制表示为 1100，这个有什么用意呢？

               由于我们此时在第 3 层找，第 3 层节点范围为 [8, 15]，即[1000, 1111]，
               
               显然由于[1000, 1111]最高位相同，无法标志不同的节点，因此我们不考虑最高位
               （即第 i 层对应着 i 位的二进制表示）

               因此 1100 的有效位就只有 100

          （3）我们通过图可以看出来找节点 12 的路径是 右左左，现在我们恍然大悟！！！！！！
               
               我们可以用 1 来表示向右查找， 用 0 来表示向左查找

          （4）那我们应该怎样得到二进制数中特定位的数呢？

               ！！！！用 "1" 逻辑与 取出，为什么这里的 "1" 加了引号，
               
               是因为这个不是数字 1 ，而是待得到的数位上数字为 1，
               
               例如我们要得到第三个数位的数，我们的 "1" 就是 0100


---
#### 实现代码

```cpp
int countNodes(TreeNode *root)
{
     //空树显然节点数为 0
     if (root == nullptr)
     {
          return 0;
     }
     //定义层数（！！！！这里层数从 0 开始定义，和我们知识点中的从 1 开始有所不同，注意区分）
     int level = 0;
     //定义 node* 指针指向根节点，用于后续遍历
     TreeNode *node = root;
     //因此从根节点出发，每次访问左子节点，直到遇到叶子节点，找到查找开始节点并得到树高
     while (node->left != nullptr)
     {
          level++;
          node = node->left;
     }
     //通过位运算高效的得到查找范围边界
     //若不好理解位运算可以先理解 low = (int)pow(2,level), high = (int)pow(2, level + 1) - 1;
     int low = 1 << level, high = (1 << (level + 1)) - 1;
     //当查找范围有效时，循环执行二分查找，直到 low == high 时找到一个不存在的点（该点即为存在和不存在的分界点，虚拟编号为 low 或者 high）
     while (low < high)
     {    
          //这一句正常思考逻辑是为 mid = (high + low + 1) / 2，之所以不用这一句是由于如果 high 和 low 都为非常大的数容易造成上溢
          int mid = (high - low + 1) / 2 + low;
          if (exists(root, level, mid))
               low = mid;
          else
               high = mid - 1;
     }
     return low;
}

bool exists(TreeNode *root, int level, int k)
{    
     //用于取数的二进制数，若 level 为 3，则 bits 为 0100，
     int bits = 1 << (level - 1); //将数字 1 左移 level - 1 位得到
     //定义 node* 指针指向根节点，用于后续遍历
     TreeNode *node = root;
     //当 node* 指针指向的节点不为空节点，且没取完该取的所有有效位（即查找路径没到头）时
     while (node != nullptr && bits > 0)
     {
          //判断该数位的值（bits & k）
          //值为 0，向左查找
          if (!(bits & k))
               node = node->left;
          //值为 1，向右查找
          else
               node = node->right;
          //取下一个有效位（即继续按照查找路径查找）
          bits >>= 1; //若在例子中此时变为 0010
     }
     //如果 node != nullptr 为真，就说明循环跳出条件是因为 bits == 0，bits == 0 说明路径走完了，找到了一个不为空的节点，return true;
     //如果 node != nullptr 为假，就说明循环跳出条件是因为 bits == 0，bits == 0 说明路径走完了，但找到了一个为空的节点，return false;
     return node != nullptr;
}
```

---
---

### 例 3 ：完全二叉树插入器（易）
---
忘了概念的看[1.（3）完全二叉树](#三特殊二叉树敲重点)
---
#### 题目描述

```txt

完全二叉树插入器

完全二叉树 是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。

设计一种算法，将一个新节点插入到一棵完全二叉树中，并在插入后保持其完整。

实现 CBTInserter 类:

CBTInserter(TreeNode root) 使用头节点为 root 的给定树初始化该数据结构；

CBTInserter.insert(int v)  向树中插入一个值为 Node.val == val的新节点 TreeNode。使树保持完全二叉树的状态，并返回插入节点 TreeNode 的父节点的值；

CBTInserter.get_root() 将返回树的头节点。
 
```

![tu](https://i-blog.csdnimg.cn/img_convert/a688edc794c7fee22fd102acaf56d972.jpeg)

```txt

示例 1：
输入
["CBTInserter", "insert", "insert", "get_root"]
[[[1, 2]], [3], [4], []]
输出
[null, 1, 2, [1, 2, 3, 4]]

解释
CBTInserter cBTInserter = new CBTInserter([1, 2]);
cBTInserter.insert(3);  // 返回 1
cBTInserter.insert(4);  // 返回 2
cBTInserter.get_root(); // 返回 [1, 2, 3, 4]
 

提示：

树中节点数量范围为 [1, 1000] 
0 <= Node.val <= 5000
root 是完全二叉树
0 <= val <= 5000 
每个测试用例最多调用 insert 和 get_root 操作 104 次
```

---

#### 实现思路


***对于一棵完全二叉树而言，其除了最后一层之外都是完全填充的，并且最后一层的节点全部在最左侧***

***也就是说可以添加子节点位置只有最后一层的最左侧的若干个节点，和倒数第二层（如果存在）的最右侧的若干个节点***


由于我们针对的是完全二叉树，忘了见[对应知识点--完全二叉树](#例题组-1-对应知识点--完全二叉树)

          我们这里提供两个方法：
          解法一：用 BFS + 队列
          解法二：用 BFS + 二进制（可以作为例题二用二进制操作树的巩固练习）

```txt
      解法一：用 BFS + 队列

      1. 广度优先搜索 ————> 层序遍历，遍历一遍后将所有的叶子节点入队保存

      2. 每次调用 insert(val) 时，我们就创建出一个节点 child，并将它作为队列的队首节点的子节点。
      
      3. 之后，我们需要把 child 加入队尾，并且如果对队首节点已经有两个子节点，我们需要将其从队列中移除

```

忘了二进制怎么操作的话看，[实现思路6.（2）（3）（4）](#例-2-完全二叉树的节点个数易)

      解法二：用 BFS + 二进制

      1. 首先先得到初始完全二叉树中的节点个数 cnt (本题用了层序遍历，当然可以用例 2 的二分查找优化)

      2. 用 c++ 内置函数得到节点个数 cnt 的二进制从左边数 0 的个数  
   
          __builtin_clz(cnt);
   
      3. 计算二进制数路径有效位（前面已经说明实际的最高位有效位不包括在路径中），即待插入节点的所在的层数

          int highbit = 32 - __builtin_clz(cnt);

          int pathHighbit = highbit - 1;
          
      4. 找插入位置的父节点
          
          在调用 insert(v) 时
          
          （1）我们可以知道它的编号 cnt，那么就可以从高到低循环遍历 cnt 的每一个二进制位（pathHighbit >>= 1）
               直到从右边数第二个数位(条件 pathHighbit > 0001(b))                 
          
          （2）循环逻辑：
               pathHighbit & cnt 如果为 0 就往左子节点移动，为 1 往右子节点移动，这样就可以到达节点需要被插入的位置的父节点

      5. 找插入位置

          现在 pathHighbit >>= 1 得到第一个数位即路径的终点

          我们知道完全二叉树左孩子编号 2x，右孩子编号 2x + 1 ————> 即当编号为奇数时为左孩子，编号为偶数时为右孩子 
          ————> 即 pathHighbit & 1 == 1 时为左孩子，pathHighbit == 0 时为右孩子
---

#### 实现代码

---

##### 解法一 ： BFS + 队列

```cpp
CBTInserter(TreeNode *root)
{    
     this->root = root;
     //用于层序遍历
     queue<TreeNode *> q;
     //用于储存可以插入数据的叶节点
     queue<TreeNode *> canInsertNodes;
     //从根节点开始层序遍历
     q.push(root);

     while (!q.empty())
     {
          TreeNode *node = q.front();
          q.pop();
          
          //层序遍历
          if (node->left)
               q.push(node->left);
          else if (node->right)
               q.push(node->right);
          //找到了叶节点，将所有找到的叶节点加入到 canInsertNodes 中
          if (!(node->left && node->right)) //node->left == nullptr || node->right == nullptr
               canInsertNodes.push(node);
     }
}

int insert(int val)
{
     TreeNode *child = new TreeNode(val);
     TreeNode *node = candidate.front();
     int ret = node->val;
     //左孩子没有插入节点，就插入到左孩子中
     if (!node->left)
     {
          node->left = child;
     }
     //若右孩子没有插入节点（且左孩已经插入了节点），就插入到右孩子中
     else
     {
          node->right = child;
          //完全二叉树不可能出现左孩子为空，右孩子存在的情况，如果右孩子不为空，那么整个节点必定全部被填满
          //所以将这个填满的节点弹出可以插入节点队列
          candidate.pop();
     }
     //加入新的可插入节点到队尾
     candidate.push(child);
     //按题目要求，返回子节点插入位置的父节点
     return ret;
}

TreeNode *get_root()
{
     return root;
}
```

---

##### 解法二：BFS + 二进制


```cpp
//这个统计节点数的方法可以通过例二的二分查找优化
CBTInserter(TreeNode *root)
{    
     this->root = root;
     //用于层序遍历
     queue<TreeNode *> q;
     //从根节点开始层序遍历
     q.push(root);

     while (!q.empty())
     {
          ++cnt; //自己记得定义一个类的内部变量，这里只展示类的方法实现
          TreeNode *node = q.front();
          q.pop();
          
          //层序遍历
          if (node->left)
               q.push(node->left);
          else if (node->right)
               q.push(node->right);
     }
}
int insert(int val)
{
    ++cnt;
    TreeNode* child = new TreeNode(val);
    TreeNode* node = root;

    //思路同例 2
    //__builtin_clz(cnt) 是一个 GCC 编译器提供的内建函数，它返回 cnt 的二进制表示中从最左边开始的 0 的个数，
    //31 - __builtin_clz(cnt) 计算的是 cnt 的二进制表示中有效数字（非零）的最高位的索引，这也代表了当前二叉树的层数。假设 cnt 是 15，那么 cnt 的二进制是 1111，__builtin_clz(cnt) 返回 28（因为 cnt 在 32 位整数中从左到右的前 28 位是 0），所以 highbit 会是 31 - 28 = 3，即表示有 3 层
    int highbit = 31 - __builtin_clz(cnt);
    int bits = 1 << (highbit - 1);
    //找插入位置的父节点
    //为什么这里是大于 1 不是像例 2 中一样大于 0？
    //因为此时是插入不是查找，查找时找的是目标节点（已经存在），故路径完整，插入是找目标位置的父节点插入（因为插入前节点目标节点显然还不存在），路径停留在从右边数第二个数位处
    while(node && bits > 1) {
        if (!(cnt & bits)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
        bits >>= 1;
    }
    //找到插入位置的父节点
    if(node){
        //找插入位置
        bits >>= 1;
        //插入为右边第一个数位为 1，说明插入为编号为奇数，由二叉树的性质得右孩子的编号（2x + 1）为奇数
        if (cnt & bits) 
        {
            node->right = child;
        }
        //编号为偶数，由二叉树的性质得左孩子的编号(2x)为偶数
        else 
        {
            node->left = child;
        }
        return node->val;
    }
    return 0;
}


TreeNode *get_root()
{
    return root;
}
```

---
---
---

## 例题组 2 ：（对应知识点 : ***正则二叉树***）

---

 忘了概念的看[1.（2）特殊二叉树](#三特殊二叉树敲重点)

---
### 例 ：判断正则查找树
---
#### 题目描述

```txt
正则二叉树

问题
给定一颗二叉查找树，其中结点上存储整数关键字，请你判断它是否一棵正则二叉树，即每个内部结点均有两个子结点。

输入
第一行是测试样例数，接下来是若干测试样例。对于每个测试样例，第一行是二叉树结点个数n，第二行是n个关键字序列，表示二叉树的先序遍历结果。假定关键字均不相同。

输出
如果二叉查找树是正则的，则输出“YES”, 否则输出"NO",每个输出占一行。

输入样例
5
2
10 5
3
1 4 7
3 
5 3 2
3
10 4 23
5
10 6 5 8 20
​
输出样例
NO
NO
NO
YES
YES
​

```
---

#### 实现思路


***递归判断***


由于我们针对的是正则二叉树，忘了见[对应知识点--正则二叉树](#1概念介绍)

![](https://i-blog.csdnimg.cn/blog_migrate/b5c9d54b3caa145b98c94f37335f7b23.png#pic_center)

     1. 设置递归终止条件
   
          （1）空节点

          （node == nullptr） ————> return true;

          （2）只有一个子树

          （root->left == nullptr && root->right != nullptr || root->left != nullptr && root->right == nullptr） ————> return false;

     2. 递归判断左右子树
          
          return isRegular(root->left) && isRegular(root->right);
---

#### 实现代码


```cpp
#include <iostream>
using namespace std;
//节点定义
struct node
{
    int val;
    node *left;
    node *right;
    node(int val, node *left = nullptr, node *right = nullptr) : val(val), left(left), right(right) {}
};
//建树
void insert(node *&root, int x)
{
    if (root == nullptr)
    {
        root = new node(x);
        return;
    }
    else if (root->val > x)
        insert(root->right, x);
    else
        insert(root->left, x);
}
//判断是不是正则二叉树
bool isRegular(node *root)
{    
     //空节点
    if (root == nullptr)
        return true;
     //正则二叉树的满足条件：左右子树均存在或均不存在————> 不满足：左右子树只有一个存在
    if (root->left == nullptr && root->right != nullptr || root->left != nullptr && root->right == nullptr)
        return false;
     //递归判断左右子树
    return isRegular(root->left) && isRegular(root->right);
}
//测试函数
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        node *root = nullptr;
        while (m--)
        {
            int x;
            cin >> x;
            insert(root, x);
        }
        if (isRegular(root))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---
---
---

## 例题组 3 ：（对应知识点 : ***BST***）

---

忘了概念的看[1.（5）BST](#三特殊二叉树敲重点)

---

### 例 1 ：插入法建立二叉搜索树（极易）

---

#### 题目描述


```txt
插入法建立二叉搜索树

题目描述：
      下面所给的是二叉搜索树节点的结构，你的任务是写一个插入函数void insert(treeNode* &root, int x)。

	struct treeNode{
			int val;
			treeNode* lchild;
			treeNode* rchild;
			treeNode():val(0),lchild(NULL),rchild(NULL){}
	};
​
      上述结构定义在头文件treeNode.h中（即你需要使用#include"treeNode.h"）。

注意事项：
      你只需写出void insert(treeNode* &root, int x)函数实现即可，不用提交main函数。


```
---
#### 实现思路


***递归判断***


由于我们针对的是 BST，忘了见[对应知识点--BST](#1概念介绍)

     1. 设置递归终止条件
   
          空节点：新建节点

     2. 递归判断左右子树
          
          插入值小于节点值，递归遍历左子树

          插入值大于节点值，递归遍历右子树
---
#### 实现代码

```cpp
#include<iostream>
using namespace std;

//节点定义
struct node
{
    int val;
    node *lchild;
    node *rchild;
    node(int val) : val(val), lchild(NULL), rchild(NULL) {}
};

//建树
void insert(node *&root, int val)
{
    if (root == NULL)
        root = new node(val);
    if (val <= root->val)
        insert(root->lchild, val);
    else
        insert(root->rchild, val);
}
```
---
### 例 2 ：二叉搜索树的路径长度（易）
---
#### 题目描述

```txt
二叉搜索树的路径长度

问题描述
二叉搜索树是这样的一棵二叉树:

要么是一棵空树。
要么由一个根结点和左右子树组成，且根结点key值大于或等于左子树中所有结点key值并且小于右子树中所有结点key值，左右子树同样是二叉搜索树。

我们定义二叉搜索树的root-to-leaf路径长度为：路径上所有结点key值之和。

现在给定一个由n个元素组成的序列和路径长度m，请先根据序列构造出来一棵二叉搜索树，然后找出所有root-to-leaf路径等于m的路径。

输入
有多个测试案例，以EOF结束

每个测试案例有两行：

第一行由n和m组成，n和m之间以空格隔开，n (0<=n<=1000)代表序列中元素个数，m (INT_MIN<=m<=INT_MAX)代表要找到的路径的长度。
第二行是输入的序列，由n个整数组成，以空格隔开。

输出
对于每个测试案例，每一行按序输出一条路径；如果没有符合条件的路径就输出NULL，单独占一行，例如：

13->7->3->5
13->7->8
13->15
​
路径的顺序类似于字符串的的比较。

样例输入
7 28
13 15 7 3 8 -2 5
7 -10
13 15 7 3 8 -2 5
​
样例输出
13->7->3->5
13->7->8
13->15
NULL


```
---
#### 实现思路


***递归判断***


由于我们针对的是二叉查找树（BST），忘了见[对应知识点--BST](#1概念介绍)

     1. 设置递归终止条件BST
   
          空节点 ： 新建节点并返回

     2. 递归判断左右子树
          
          插入值小于节点值 ，递归遍历左子树

          插入值大于节点值，递归遍历右子树
---
#### 实现代码

```cpp
#include <iostream>
#include <vector>
#include <sstream> // for ostringstream
#include <string>
using namespace std;

//节点定义
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};
//建树
void insert(TreeNode *&root, int val)
{
    if (root == nullptr)
        root = new TreeNode(val);
    else if (val < root->val)
        insert(root->left, val);
    else
        insert(root->right, val);
}
//寻找长度为 m 且终点为叶子节点的路径
void findPaths(TreeNode *node, int target, vector<int> &currentPath, vector<string> &results)
{    
     //递归终止条件：遍历到叶节点（叶节点的子树为空）
    if (node == nullptr)
        return;

     //将当前路径加入到路径序列中
    currentPath.push_back(node->val);

     //条件判断
     //条件 1 ：如果终点是叶子节点
    if (node->left == nullptr && node->right == nullptr)
    {

        // 计算当前路径和
        int sum = 0;
        for (int val : currentPath)
            sum += val;

        //条件 2 ：如果路径和等于要找的路径长度 m 
        if (sum == target)
        { 
            // 将路径格式化后保存在结果数组中
            ostringstream oss;
            for (size_t i = 0; i < currentPath.size(); ++i)
            {
                oss << currentPath[i];
                if (i < currentPath.size() - 1)
                {
                    oss << "->";
                }
            }
            results.push_back(oss.str()); // 保存路径
        }
    }
     
    //递归遍历左右子树
    findPaths(node->left, target, currentPath, results);
    findPaths(node->right, target, currentPath, results);

    //回溯恢复路径
    currentPath.pop_back();
}

//测试函数
int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        if (n == 0)
        {
            cout << "NULL" << endl;
            continue;
        }

        TreeNode *root = nullptr;
        for (int i = 0; i < n; ++i)
        {
            int val;
            cin >> val;
            insert(root, val);
        }

        vector<string> results;
        vector<int> currentPath;
        findPaths(root, m, currentPath, results);

        if (results.empty())
        {
            cout << "NULL" << endl;
        }
        else
        {
            for (const string &path : results)
            {
                cout << path << endl;
            }
        }
    }

    return 0;
}
```
---
#### 递归优化

***我们发现，我们每次判断路径和的时候都需要重新计算一次，导致多次的重复计算***

***优化目标：减少在每个叶节点处计算路径和的开销***

     优化步骤：
          1. 添加累加和参数：在递归函数中添加一个参数 currentSum，用于跟踪当前路径的累加和。
          2. 更新累加和：在将当前节点加入路径时，更新 currentSum。
          3. 叶节点判断：到达叶节点时，直接比较 currentSum与目标值，而不需要遍历 currentPath。
          4. 递归调用时传递累加和：在递归调用左右子树时，传递更新后的 currentSum。
---
#### 优化代码实现

```cpp
// 优化的findPaths函数
void findPaths(TreeNode *node, int target, vector<int> &currentPath, int currentSum, vector<string> &results)
{    
    // 递归终止条件：节点为空
    if (node == nullptr)
        return;

    // 将当前节点加入路径，并更新当前路径和
    currentPath.push_back(node->val);
    currentSum += node->val;

    // 判断是否为叶节点
    if (node->left == nullptr && node->right == nullptr)
    {
        // 如果当前路径和等于目标值，则将路径加入结果
        if (currentSum == target)
        { 
            // 将路径格式化为字符串
            ostringstream oss;
            for (size_t i = 0; i < currentPath.size(); ++i)
            {
                oss << currentPath[i];
                if (i < currentPath.size() - 1)
                {
                    oss << "->";
                }
            }
            results.push_back(oss.str());
        }
    }
    // 递归遍历左右子树
    findPaths(node->left, target, currentPath, currentSum, results);
    findPaths(node->right, target, currentPath, currentSum, results);

    // 回溯，移除当前节点
    currentPath.pop_back();
}
```
---
---
---

## 例题组 4 ：（对应知识点 :***AVL***）

---

忘了概念的看[1.（6）AVL树](#三特殊二叉树敲重点)

---
### 例 1 ：判断二叉查找树是否平衡（中）
---
#### 题目描述

```txt
判断二叉查找树是否平衡 2

问题
给定一颗二叉查找树，其中结点上存储整数关键字，请你判断它是否一棵平衡的二叉查找树，即每个内部结点的两颗子树高度差小于等于1。

输入
第一行是测试样例数，接下来是若干测试样例。对于每个测试样例，第一行是二叉树结点个数n，第二行是n个关键字序列，表示二叉树的先序遍历结果。假定关键字均不相同。

输出
如果二叉查找树是平衡的，则输出“YES”, 否则输出"NO",每个输出占一行。

输入样例
5
2
10 5
3
1 4 7
3 
5 3 2
3
10 4 23
5
10 6 5 8 20
​
输出样例
YES
NO
NO
YES
YES
YES
NO
NO
YES
YES
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
#include <vector>
#include <cmath>
using namespace std;

// 定义结点
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 构建二叉查找树的插入函数
TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
        return new TreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
}

// 检查二叉树是否平衡，并返回树的高度
bool isBalanced(TreeNode *root, int &height)
{
    if (!root)
    {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool leftBalanced = isBalanced(root->left, leftHeight);
    bool rightBalanced = isBalanced(root->right, rightHeight);

    // 当前结点平衡的条件是：左右子树高度差不超过 1，且左右子树都是平衡的
    height = max(leftHeight, rightHeight) + 1;
    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}

int main()
{
    int t;
    cin >> t; // 输入测试用例数

    while (t--)
    {
        int n;
        cin >> n; // 输入结点个数
        vector<int> preorder(n);
        for (int i = 0; i < n; i++)
        {
            cin >> preorder[i]; // 输入先序遍历结果
        }

        // 构建二叉查找树
        TreeNode *root = NULL;
        for (int i = 0; i < n; i++)
        {
            root = insert(root, preorder[i]);
        }

        // 判断树是否平衡
        int height = 0;
        if (isBalanced(root, height))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}
```
---
#### 易出现的错误解释：

***观察这两段代码的区别在哪里***

正确：
```cpp
bool isBalanced(TreeNode *root, int &height)
{
    if (!root)
    {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;
    bool leftBalanced = isBalanced(root->left, leftHeight);
    bool rightBalanced = isBalanced(root->right, rightHeight);

    height = max(leftHeight, rightHeight) + 1;

    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}
```

---

错误：
```cpp
bool isBalanced(TreeNode* root, int& height) 
{
    if (!root) 
    {
        height = 0;
        return true;
    }
    
    int leftHeight = 0, rightHeight = 0;

    height = max(leftHeight, rightHeight) + 1;
    
    return isBalanced(root->left, leftHeight) && isBalanced(root->right, rightHeight) && abs(leftHeight - rightHeight) <= 1;
}
```
---
思考：为什么出错？错在哪里？

解答：

     第一段正确代码：

          先递归判断左右子树的平衡性 isBalanced(root->left, leftHeight) 和 isBalanced(root->right, rightHeight)，
          
          并将左右子树的高度分别保存在 leftHeight 和 rightHeight 中。
          
          只有在子树的平衡性已经确认后，才计算当前节点的高度，并判断当前节点是否平衡。
          
          这样，左右子树的高度计算是在递归调用之后进行的，确保了当前节点的平衡性是基于已经计算出的左右子树高度的
          

     第二段错误代码：

          递归判断左右子树的平衡性之前，先计算了当前节点的高度。
          
          也就是说，左右子树的高度（leftHeight 和 rightHeight）在递归调用时仍然是初始值 0，
          
          这会导致在判断当前节点的平衡性时，左右子树的高度总是为 0，从而无法正确判断树的实际平衡状态。
---


---

朋友们，我们光会判断是否是平衡二叉树不行啊，如果是一棵平衡二叉树当然最好，如果不是呢，如果我就要一棵平衡二叉树呢，怎么搞？

让我们一起看例题 2，将二叉搜索树变平衡

---

### 例 2 ： 将二叉搜索树变平衡

#### 题目描述

```txt
题目描述

将二叉搜索树变平衡

给你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，请你返回任意一种。

如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就称这棵二叉搜索树是 平衡的 。

 

示例 1：
输入：root = [1,null,2,null,3,null,4,null,null]
输出：[2,1,3,null,null,null,4]
解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。
```

![tu](https://i-blog.csdnimg.cn/img_convert/c4b875e88a9c5cdfffc2c9611e6936fb.jpeg)

```txt

示例 2：
输入: root = [2,1,3]
输出: [2,1,3]
```

![tu](https://i-blog.csdnimg.cn/img_convert/84c784854c4f5936701124b3f045a42e.jpeg)

```txt
提示：

树节点的数目在 [1, 104] 范围内。
1 <= Node.val <= 105
```

---
#### 实现思路


***递归重建树***

由于我们针对的是二叉搜索树转成 AVL 树，忘了见[对应知识点--AVL](#1概念介绍)

所以我们先要明确二叉搜索树有什么特点？ ————> 显然二叉搜索树元素有序 ————> 所以我们可以用这本来就有序的元素重建树即可

     1. 用中序遍历得到一个递增的有序序列

     2. 每次用中间的节点作为根节点，划分为左右两个区间
          
     3. 分别递归重建左右两个子树

#### 实现代码

```cpp

vector<int> inorderSeq;

// 用中序遍历得到一个递增的有序序列
void getInorder(TreeNode *node)
{
    if (node == nullptr)
        return;
    getInorder(node->left);
    inorderSeq.push_back(node->val);
    getInorder(node->right);
}

TreeNode *build(int l, int r)
{    
     //每次用中间的节点作为根节点
    int mid = l + ((r - l) >> 1);
    TreeNode *root = new TreeNode(inorderSeq[mid]);

    // 递归重建左右两个子树
    if (l <= mid - 1)
        root->left = build(l, mid - 1);
    if (mid + 1 <= r)
        root->right = build(mid + 1, r);
     // 返回重建得到的平衡二叉树
    return root;
}

TreeNode *balanceBST(TreeNode *root)
{
    getInorder(root);
    return build(0, inorderSeq.size() - 1);
}
```

---
如果钻牛角尖的话，我们或许会纠结 ———— 我给出了这个方法 你直接用了这个方法，但是不知道这个方法为什么可行

***如果需要深入了解下面的数学证明，不感兴趣的可以直接跳过***

---
---
#### 数学证明

[自行查看力扣官网题解证明](https://leetcode.cn/problems/balance-a-binary-search-tree/solutions/241897/jiang-er-cha-sou-suo-shu-bian-ping-heng-by-leetcod/)

---
---

## 例题组 5 ：（对应知识点 : ***哈夫曼树***）

---

忘了概念的看[1.（8）哈夫曼树](#三特殊二叉树敲重点)

---

---

### 过程图解


（1）全部初始化为叶节点（只有根节点的树）

![1](https://i-blog.csdnimg.cn/blog_migrate/acdb6c5b36b4fb2b58d1c4cbaa176efb.png)

（2）选择字符频率最小的两个造新树

![1](https://i-blog.csdnimg.cn/blog_migrate/57e8026598960f0dbf69e16ac858b428.png)


（3）删除原字符频率最小的两个节点，添加新节点（那两个节点的父节点）

![1](https://i-blog.csdnimg.cn/blog_migrate/7639e165d1b4892de15864e3f2ddac0c.png)

（4）重复（2）（3）直到剩一个节点

![1](https://i-blog.csdnimg.cn/blog_migrate/edea6726e75ed5d793a96ed1a21c9ab5.png)


---
### 例 ：哈夫曼树编码（易）
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

// text function
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

## 例题组 6 ：（对应知识点 : ***线索化二叉树***）

---

 忘了概念的看[1.（9）特殊二叉树](#三特殊二叉树敲重点)

---

### 问题引入：

    我们的二叉树学到现在，会产生两个问题：

    1. 在n个结点的二叉树中，必定有 n + 1 个空链域（叶子结点的左右子树空间浪费了）
    2. 二叉树的遍历，无论是递归还是非递归算法，效率都不算高。
   
    那我们能不能利用原本浪费掉的空间，来解决第二个问题呢？

    倘若对下图二叉树进行中序遍历，可以得到 1、3、6、8、10，我们可以知道 3 的前驱结点为 1，后驱结点为 6。
    
![tu](https://i-blog.csdnimg.cn/blog_migrate/f921b48defbcffc68843d75490c01e35.png)

    但是，这种关系的建立是在完成遍历后得到的，那么，可不可以在建立二叉树的同时记录下前驱后继的关系，这样我们在寻找前驱后继结点时的效率将会大大提升！

![tu](https://i-blog.csdnimg.cn/blog_migrate/9443d673619f856fd19a390b302a9329.png)

    那我们如何区分一个 lc 指针是指向左孩子还是前驱结点呢？

    为了解决这个问题，我们需要添加标志位 lc 和 rc,并定义以下规则

    lc == 0，指向左孩子；lc == 1，指向前驱结点
    rc == 0，指向右孩子；rc == 1，指向后继结点

```cpp
// 节点定义
struct Treenode
{
    int val;
    Treenode *lc, *rc;
    bool lf, rf; // 标识是否为线索节点：lf表示左线索，rf表示右线索
    Treenode(int val) : val(val), lf(0), rf(0), lc(nullptr), rc(nullptr) {}
};
```

---
---

### 三种线索化方法 + 三种线索化遍历

---


***前序线索化：根 左 右***

***中序线索化：左 根 右***

***后序线索化：左 右 根***

---

#### 三种线索化方法

---

##### 1. 前序线索化

```cpp
void preThreading(Treenode *node)
{
    if (node == nullptr)
        return;

    // 根
    if (node->lc == nullptr)
        node->lc = pre, node->lf = 1;
    if (pre && pre->rc == nullptr)
        pre->rc = node, pre->rf = 1; 
    pre = node;

    // 左
    if (node->lf == 0)
        preThreading(node->lc);
        
    // 右
    if (node->rf == 0)
        preThreading(node->rc);
}

```

---

##### 中序线索化

```cpp
void inThreading(Treenode * node)
{
    if(node == nullptr)
        return;

    // 左
    if (node->lf == 0)
        preThreading(node->lc);

    // 根
    if (node->lc == nullptr)
        node->lc = pre, node->lf = 1;
    if (pre && pre->rc == nullptr)
        pre->rc = node, pre->rf = 1; 
    pre = node;

    // 右
    if (node->rf == 0)
        preThreading(node->rc);
}
```

---

##### 后序线索化

```cpp
void postTHreading(Treenode * node)
{
    if (node == nullptr)
        return;
    //左
    if (node->lf == 0)
        postTHreading(node->lc);

    //右
    if (node->rf == 0)
        postTHreading(node->rc);

    //根
    if (node->lc == nullptr)
        node->lc = pre, node->lf = 1;
    if (pre && pre->rc == nullptr)
        pre->rc = node, pre->rf = 1;
    pre = node;
}
```
---

#### 三种线索化遍历


首先我们需要明确三种线索化的传统应用场景

    前序线索化遍历： 正序遍历
    中序线索化遍历： 正序遍历 / 倒序遍历
    后序线索化遍历： 倒序遍历

##### 1. 前序线索化遍历

```cpp
// 前序线索化正序遍历
void PreOrderThread()
{
    for (Treenode *curr = FirstNode(root); curr != nullptr; curr = NextNode(curr))
        cout << curr->val << " ";
}
```

```cpp
//辅助函数
Treenode *FirstNode(Treenode *node) const
{
    return node;
}
Treenode *NextNode(Treenode *node) const
{
    if (node->rf == 1)
        return node->rc;
    else if (node->lc && node->lf == 0)
        return node->lc; 
    else
        return node->rc; 
}
```

---

##### 中序线索化遍历

```cpp
// 中序线索化正序遍历
void inOrderThread_Positive()
{
    for(Treenode* curr = FirstNode(root); curr != nullptr; curr = NextNode(curr)) 
      cout << curr->val << " ";
}
// 中序线索化倒序遍历
void inOrderThread_Reverse()
{
    for(Treenode* curr = LastNode(root); curr != nullptr; curr = PreNode(curr)) 
      cout << curr->val << " ";
}
```

```cpp
//辅助函数
Treenode* FirstNode(Treenode* node) const
{
    while(node && node->lf == 0) 
      node = node->lc;
    return node;
}
Treenode* LastNode(Treenode* node) const
{
    while(node && node->rf == 0) 
      node = node->rc;
    return node;
}
Treenode* NextNode(Treenode* node) const
{
    if(node->rf == 1) 
      return node->rc;
    else 
      return FirstNode(node->rc);
}
Treenode* PreNode(Treenode* node) const
{
    if(node->lf == 1) 
      return node->lc;
    else 
      return LastNode(node->lc);
}
```

---

##### 后序线索化遍历

```cpp
// 后序线索化倒序遍历
void PostOrderThread()
{
    for (Treenode *curr = LastNode(root); curr != nullptr; curr = PreNode(curr))
        cout << curr->val << " ";
}
```

```cpp
//辅助函数
Treenode *LastNode(Treenode *node)
{
  return node;
}
Treenode *PreNode(Treenode *node)
{
    if (node->lf == 1)
      return node->lc;
    else if (node->rc && node->rf == 0)
      return node->rc;
    else
      return node->lc;
}
```
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
     （2）构造比较函数是通过函数（静态成员或者非成员） : 函数名不是类型名，所以不能直接传函数名，要传 decltype(&函数名)，还需要传入实体
                    
          为什么要传 decltype(&函数名)？
          
               因为需要使用 decltype(&函数名) 来获取函数指针的类型
          
          为什么需要函数指针的类型？
          
               因为函数指针是一个具体的类型。
               因此模板参数仍然是类型参数，但这个类型是函数指针类型。
                    
               例如：compare是一个普通函数，其类型为bool(*)(int, int)


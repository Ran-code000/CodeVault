# ***线索化二叉树***

---
## 概念

 线索化树 (Threaded Binary Tree): 

     在树的空指针中插入指向前驱和后继节点的线索，以便于遍历。

这里展示的是中序线索化
![](https://i-blog.csdnimg.cn/blog_migrate/3533caf79328f1cfcaf42e08b3ac204b.png)


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

## ***三种线索化方法 + 三种线索化遍历***

---


***前序线索化：根 左 右***

***中序线索化：左 根 右***

***后序线索化：左 右 根***

---

### 三种线索化方法

---

#### 1. 前序线索化

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

#### 中序线索化

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

#### 后序线索化

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

#### 1. 前序线索化遍历

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

#### 中序线索化遍历

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

#### 后序线索化遍历

```cpp
// 中序线索化倒序遍历
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

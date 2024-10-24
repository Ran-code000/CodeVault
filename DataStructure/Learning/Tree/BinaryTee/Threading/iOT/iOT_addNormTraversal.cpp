#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
//建立可线索化的二叉树
class ThreadedBinaryTree{
    struct Treenode{
        int val;
        Treenode* lc, *rc;
        bool lf, rf;
        Treenode(int val) : val(val), lc(nullptr), rc(nullptr), lf(0), rf(0){} 
    };
    Treenode* root;
    Treenode* pre;
    //中序线索化
    void inThreading(Treenode* node){
        if(node){
        //左
            inThreading(node->lc);//找最左下的节点（第一个开始遍历的节点）
        //中
            //找前驱
            if(node->lc == nullptr){
                node->lc = pre, node->lf = 1;//在哪个节点更新哪个节点
                if(pre) cout << node->val << "'s pre is " << pre->val << endl;
            } 
            //找后继
            //第一个条件控制找到第一个节点（最左下）
            if(pre && pre->rc == nullptr){
                pre->rc = node, pre->rf = 1;//在哪个节点更新哪个节点！！！！！
                if(pre) cout << pre->val << "'s post is " << node->val << endl;
            }
            //线索化过程细节开关
            //if(node && pre) cout << "node->val: " << node->val << " pre->val: " << pre->val << "\n";
            //if(node && pre) cout << "node->rf: " << node->rf << " pre->rf: " << pre->rf << "\n\n";
            pre = node;
            //if(node->val == 14) exit(-1); 为了找 bug。。。。
        //右
            if(node) inThreading(node->rc);
        }
    }
    //普通遍历————利用栈递归
    void inOrderTraversal_Ordinary(Treenode* node) const{
        if(node){
            inOrderTraversal_Ordinary(node->lc);
            cout << node->val << " ";
            inOrderTraversal_Ordinary(node->rc);
        }
    }
    //找第一个开始遍历的节点（或者在 NextNode() 的调用中，在没有后继节点的前提下找到右子树最左下（最小）节点）
    Treenode* FirstNode(Treenode* node) const{
        while(node && node->lf == 0) node = node->lc;
        return node;
    }
    Treenode* LastNode(Treenode* node) const{
        while(node && node->rf == 0) node = node->rc;
        return node;
    }
    Treenode* NextNode(Treenode* node) const{
        if(node->rf) return node->rc;
        else return FirstNode(node->rc);
    }
    Treenode* PreNode(Treenode* node) const{
        if(node->lf) return node->lc;
        else return LastNode(node->lc);
    }
public:
    ThreadedBinaryTree() : root(nullptr), pre(nullptr){}
    void insert(int val){
        Treenode* newnode = new Treenode(val);
        if(root == nullptr){ root = newnode; return;}
        Treenode* curr = root;
        Treenode* prev = nullptr;
        //定位
        while(curr){
            prev = curr;//移动跟踪
            //不同于链表，有指针和标志位两个判断要素
            if(val < curr->val) curr = !(curr->lf) ? curr->lc : nullptr;//左
            else if(val > curr->val) curr = !(curr->rf) ? curr->rc : nullptr;//右
            else return;//不允许重复值出现
        }
        //插入
        if(val < prev->val) prev->lc = newnode;
        else prev->rc = newnode;
    }
    void CreateinThreading(){ 
        pre = nullptr; 
        if(root){
            inThreading(root);
            //处理一下尾节点（不处理也行）
            pre->rc = nullptr;
            pre->rf = 1;
        }
    }
    //线索化中序顺序遍历
    void inOrderTraversal_Thread_Positive() const{
        Treenode* curr = root;
        // //find the first node
        // while(curr->lf == 0) curr = curr->lc;
        // Treenode* temp = curr;
        while(curr){
            while(curr->lf == 0) curr = curr->lc;
            cout << curr->val << " ";
            while(curr->rc && curr->rf){ curr = curr->rc; cout << curr->val << " ";}//沿后继找
            //没有后继————找右子树最左边的节点，即为后继节点
            curr = curr->rc;
            //while(!(curr->lf)) curr = curr->lc;
        }
        //baby法2
        // while(curr->lf == 0) curr = curr->lc;
        // cout << curr->val << " ";
        // while(curr){
        //     if(curr->rc && curr->rf) curr = curr->rc, cout << curr->val << " "; //有后继直接找
        //     else{//没有后继找右子树最左下的节点
        //         curr = curr->rc;
        //         if(curr){
        //             while(curr->lf == 0 && curr->lc) curr = curr->lc;
        //             cout << curr->val << " ";
        //         }
        //     }
        // }
        cout << endl;
    }
    //线索化中序逆序遍历
    void inOrderTraversal_Thread_Reverse() const{
        Treenode* curr = root;
        while(curr){
            while(curr->rf == 0) curr = curr->rc;
            cout << curr->val << " ";
            while(curr->lc && curr->lf) curr = curr->lc, cout << curr->val << " ";
            curr = curr->lc;
        }
        cout << endl;
    }
    //标准线索化正序遍历（为了和链表类比）
    void inOrderTraversal_Thread_Positive_Norm(){
        for(Treenode* curr = FirstNode(root); curr != nullptr; curr = NextNode(curr)) cout << curr->val << " ";
        cout << endl;
    }
    //标准线索化逆序遍历（为了和链表类比）
    void inOrderTraversal_Thread_Reverse_Norm(){
        for(Treenode* curr = LastNode(root); curr != nullptr; curr = PreNode(curr)) cout << curr->val << " ";
        cout << endl;
    }
    //中序普通递归遍历
    void inOrderTraversal_Ordinary() const{ inOrderTraversal_Ordinary(root); cout << endl;}
};
//text function
int main(){
    ThreadedBinaryTree ThreadedBinaryTree;
    ThreadedBinaryTree.insert(10);
    ThreadedBinaryTree.insert(6);
    ThreadedBinaryTree.insert(14);
    ThreadedBinaryTree.insert(4);
    ThreadedBinaryTree.insert(8);
    ThreadedBinaryTree.insert(12);
    ThreadedBinaryTree.insert(16);
    ThreadedBinaryTree.insert(7);
    ThreadedBinaryTree.insert(11);
    ThreadedBinaryTree.insert(15);
    ThreadedBinaryTree.insert(13);
    //普通遍历
    auto start1 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.inOrderTraversal_Ordinary();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "inOrderTraversal_Ordinary_runnning time: " << duration1 << "μs" << endl;
    //线索化中序正序遍历
    ThreadedBinaryTree.CreateinThreading();
    auto start2 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.inOrderTraversal_Thread_Positive();
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "inOrderTraversal_Thread_Positive_runnning time: " << duration2 << "μs" << endl;
    //线索化中序逆序遍历
    //ThreadedBinaryTree.CreateinThreading();
    auto start3 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.inOrderTraversal_Thread_Reverse();
    auto end3 = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end3 - start3).count();
    cout << "inOrderTraversal_Thread_Reverse_runnning time: " << duration3 << "μs" << endl;
    //线索化标准正序遍历（封装后遍历类比链表）
    auto start4 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.inOrderTraversal_Thread_Positive_Norm();
    auto end4 = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(end4 - start4).count();
    cout << "inOrderTraversal_Thread_Positive_Norm_runnning time: " << duration4 << "μs" << endl;
    //线索化标准逆序遍历（封装后遍历类比链表）
    auto start5 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.inOrderTraversal_Thread_Reverse_Norm();
    auto end5 = chrono::high_resolution_clock::now();
    auto duration5 = chrono::duration_cast<chrono::microseconds>(end5 - start5).count();
    cout << "inOrderTraversal_Thread_Reverse_Norm_runnning time: " << duration5 << "μs" << endl;
    return 0;
}
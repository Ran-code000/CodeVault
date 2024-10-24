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
        Treenode(int val) : val(val) , lf(0), rf(0), lc(nullptr), rc(nullptr){}
    };
    Treenode* root;
    Treenode* pre;
    //前序线索化
    void preThreading(Treenode* node){
        if(node){
            //根
            if(node->lc == nullptr) node->lc = pre, node->lf = 1;
            if(pre && pre->rc == nullptr) pre->rc = node, pre->rf = 1;
            //线索化细节控制开关
            if(node && pre) cout << "node->val: " << node->val << " pre->val: " << pre->val << "\n";
            if(node && pre) cout << "node->rf: " << node->rf << " pre->rf: " << pre->rf << "\n";
            if(node && pre) cout << "node->lf: " << node->lf << " pre->rf: " << pre->lf << "\n\n";
            pre = node;
            //左
            if(node->lf == 0) preThreading(node->lc);
            //右
            if(node->rf == 0) {preThreading(node->rc);}
            //需要判断lf和rf是否等于0，因为前面已经进行了部分线索化，所以不进行判断就会陷入无线循环当中
        }
    }
    //普通遍历————利用栈递归
    void PreOrderTraversal_Normal(Treenode* node) const{
        if(node){
            cout << node->val << " ";
            PreOrderTraversal_Normal(node->lc);
            PreOrderTraversal_Normal(node->rc);
        }
    }
    Treenode* FirstNode(Treenode* node) const{
        return node;
    }
    Treenode* NextNode(Treenode* node) const{
        if(node->rf == 1){
            if(node->rc) return node->rc;
            return nullptr;//判断最后一个节点
        }else if(node->lc && node->lf == 0) return node->lc;//左孩子
        else return node->rc;//只有右孩子
    }
    // Treenode* LastNode(Treenode* node) const{
    //     while(node && node->rf == 0) node = node->rc;
    //     return node;
    // }
public:
    ThreadedBinaryTree() : root(nullptr), pre(nullptr){}
    void insert(int val){
        Treenode* newnode = new Treenode(val);
        if(root == nullptr){ root = newnode; return;}
        Treenode* prev = nullptr;
        Treenode* curr = root;
        //定位
        while(curr){
            prev = curr;
            //错误写法
            // if(val < curr->val && curr->lf == 0) curr = curr->lc;
            // else if(val > curr->val && curr->rf == 0) curr = curr->rc;
            // else return;
            if(val < curr->val) curr = !(curr->lf) ? curr->lc : nullptr;
            else if(val > curr->val) curr = !(curr->rf) ? curr->rc : nullptr;
            else return;
        }
        //插入
        if(val < prev->val) prev->lc = newnode;
        else prev->rc = newnode;
    }
    void CreatePreThreading(){ 
        pre = nullptr; 
        if(root){
            preThreading(root);
            //处理一下尾节点（不处理也行）
            pre->rc = nullptr;
            pre->rf = 1;//注意对尾节点判断的影响
        }
    }
    //线索化前序顺序遍历
    void PreOrderTraversal_Thread_Positive(){
        Treenode* curr = root;
        while(curr){
            //先输出再移动（类比 cout << a++;）
            while(curr->lf == 0) cout << curr->val << " ", curr = curr->lc;
            while(curr->rc && curr->rf == 1) cout << curr->val << " ", curr = curr->rc;
            if(curr->rc == nullptr){ cout << curr->val << endl; return;}
        }
        //法二
        // while(curr->lf == 0) cout << curr->val << " ", curr = curr->lc;
        // while(curr){
        //     if(curr->rc && curr->rf == 1) cout << curr->val << " ", curr = curr->rc; //用后继找
        //     else{
        //         if(curr){
        //             while(curr->lf == 0) cout << curr->val << " ", curr = curr->lc;
        //             if(curr->rc == nullptr && curr->rf == 1){cout << curr->val << endl; return;}//已处理过尾节点，尾节点的 rf 被线索化调用时手动设为了 1
        //         }
        //     }
        //}
    }
    // //线索化前序逆序遍历
    // void PreOrderTraversal_Thread_Reverse() const{
    //     Treenode* curr = root;
    //     while(curr){
    //         while(curr->rc) curr = curr->rc;
    //         while(curr->lc && curr->lf) curr = curr->lc, cout << curr->val << " ";
    //         cout << curr->val << " ";
    //     }
    //     cout << endl;
    // }
    //标准线索化正序遍历（为了和链表类比）
    void PreOrderTraversal_Thread_Positive_Norm(){
        for(Treenode* curr = FirstNode(root); curr != nullptr; curr = NextNode(curr)) cout << curr->val << " ";
        cout << endl;
    }
    void PreOrderTraversal_Normal(){ PreOrderTraversal_Normal(root); cout << endl;}

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
    ThreadedBinaryTree.PreOrderTraversal_Normal();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "PreOrderTraversal_Normal_runnning time: " << duration1 << "ms" << endl;
    //线索化前序正序遍历
    ThreadedBinaryTree.CreatePreThreading();
    auto start2 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.PreOrderTraversal_Thread_Positive();
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "PreOrderTraversal_Thread_Positive_runnning time: " << duration2 << "ms" << endl;
    // //线索化前序逆序遍历
    // //ThreadedBinaryTree.CreatePreThreading();
    // auto start3 = chrono::high_resolution_clock::now();
    // ThreadedBinaryTree.PreOrderTraversal_Thread_Reverse();
    // auto end3 = chrono::high_resolution_clock::now();
    // auto duration3 = chrono::duration_cast<chrono::microseconds>(end3 - start3).count();
    // cout << "PreOrderTraversal_Thread_Positive_runnning time: " << duration3 << "ms" << endl;
    //线索化标准正序遍历（封装后遍历类比链表）
    auto start4 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.PreOrderTraversal_Thread_Positive_Norm();
    auto end4 = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(end4 - start4).count();
    cout << "PreOrderTraversal_Thread_Positive_Norm_runnning time: " << duration4 << "ms" << endl;
}
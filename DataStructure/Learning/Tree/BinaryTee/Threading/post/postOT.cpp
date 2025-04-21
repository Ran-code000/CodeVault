#include <iostream>
#include <chrono>
using namespace std;
class ThreadedBinaryTree{
    struct Treenode{
        int val;
        Treenode* lc, *rc;
        bool lf, rf;
        Treenode(int val) : val(val), lc(nullptr), rc(nullptr), lf(0), rf(0){}
    };
    Treenode* root;
    Treenode* pre;
    void postTHreading(Treenode* node){
        if(node){
            if(node->lf == 0) postTHreading(node->lc);
            if(node->rf == 0) postTHreading(node->rc);
            if(node->lc == nullptr) node->lc = pre, node->lf = 1;
            if(pre && pre->rc == nullptr) pre->rc = node, pre->rf = 1;
            if(node && pre) cout << "node->val: " << node->val << " pre->val: " << pre->val << "\n";
            if(node && pre) cout << "node->rf: " << node->rf << " pre->rf: " << pre->rf << "\n";
            if(node && pre) cout << "node->lf: " << node->lf << " pre->lf: " << pre->lf << "\n\n";
            pre = node;
        }
    }
    Treenode* LastNode(Treenode* node){
        return node;
    }
    Treenode* PreNode(Treenode* node){
        //if(node){
            if(node->lf == 1) return node->lc;
            else if(node->rc && node->rf == 0) return node->rc;
            else return node->lc;
        //}
    }
    void PostOrderTraversal_Ordinary(Treenode* node){
        if(node){
            PostOrderTraversal_Ordinary(node->lc);
            PostOrderTraversal_Ordinary(node->rc);
            cout << node->val << " ";
        }
    }
public:
    ThreadedBinaryTree() : root(nullptr), pre(nullptr){}
    void insert(int val){
        Treenode* newnode = new Treenode(val);
        if(root == nullptr){ root = newnode; return;}
        Treenode* curr = root;
        Treenode* prev = nullptr;
        while(curr){
            prev = curr;
            if(val < curr->val) curr = curr->lf == 0 ? curr->lc : nullptr;
            else if(val > curr->val) curr = curr->rf == 0 ? curr->rc : nullptr;
            else return;
        }
        if(val < prev->val) prev->lc = newnode;
        else prev->rc = newnode;
    }
    void CreatePostThreading(){
        pre = nullptr;
        if(root){
            postTHreading(root);
            // pre->rc = nullptr;
            // pre->rf = 1;
        }
    }
    void PostOrderTraversal_Thread_Reverse(){
        Treenode* curr = root;
        while(curr){
            cout << curr->val << " ";//根
            while(curr->rc && curr->rf == 0) curr = curr->rc, cout << curr->val << " ";//右
            while(curr->lc && curr->lf == 1) curr = curr->lc, cout << curr->val << " ";//前驱
            //若没有前驱，有右孩子进右孩子
            if(curr->rc && curr->rf == 0) curr = curr->rc;
            //没右孩子进左孩子
            else curr = curr->lc;
        }
        cout << endl;
    }
    void PostOrderTraversal_Thread_Reverse_Norm(){
        for(Treenode* curr = LastNode(root); curr != nullptr; curr = PreNode(curr)) cout << curr->val << " ";
        cout << endl;
    }
    void PostOrderTraversal_Ordinary(){ PostOrderTraversal_Ordinary(root);}
};
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
    ThreadedBinaryTree.PostOrderTraversal_Ordinary();
    auto end1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "PostOrderTraversal_Ordinary_runnning time: " << duration1 << "μs" << endl;
    // //线索化后序正序遍历
    // ThreadedBinaryTree.CreateinThreading();
    // auto start2 = chrono::high_resolution_clock::now();
    // ThreadedBinaryTree.inOrderTraversal_Thread_Positive();
    // auto end2 = chrono::high_resolution_clock::now();
    // auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    // cout << "PostOrderTraversal_Thread_Positive_runnning time: " << duration2 << "μs" << endl;
    //线索化中序逆序遍历
    //ThreadedBinaryTree.CreateinThreading();
    ThreadedBinaryTree.CreatePostThreading();
    auto start3 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.PostOrderTraversal_Thread_Reverse();
    auto end3 = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end3 - start3).count();
    cout << "PostOrderTraversal_Thread_Reverse_runnning time: " << duration3 << "μs" << endl;
    // //线索化标准正序遍历（封装后遍历类比链表）
    // auto start4 = chrono::high_resolution_clock::now();
    // ThreadedBinaryTree.PostOrderTraversal_Thread_Positive_Norm();
    // auto end4 = chrono::high_resolution_clock::now();
    // auto duration4 = chrono::duration_cast<chrono::microseconds>(end4 - start4).count();
    // cout << "PostOrderTraversal_Thread_Positive_Norm_runnning time: " << duration4 << "μs" << endl;
    //线索化标准逆序遍历（封装后遍历类比链表）
    auto start5 = chrono::high_resolution_clock::now();
    ThreadedBinaryTree.PostOrderTraversal_Thread_Reverse_Norm();
    auto end5 = chrono::high_resolution_clock::now();
    auto duration5 = chrono::duration_cast<chrono::microseconds>(end5 - start5).count();
    cout << "PostOrderTraversal_Thread_Reverse_Norm_runnning time: " << duration5 << "μs" << endl;
    return 0;
}
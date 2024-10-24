#include <iostream>
#include <chrono>
using namespace std;
class TBT{
    struct Treenode{
        int val;
        Treenode* lc, *rc;
        bool lf, rf;
        Treenode(int val) : val(val), lc(nullptr), rc(nullptr), lf(0), rf(0){} 
    };
    Treenode* root;
    Treenode* pre;
    void iT(Treenode* node){
        if(node){
            iT(node->lc);
            if(node->lc == nullptr){
                node->lc = pre;
                node->lf = 1;
            }
            //第一个条件控制找到第一个节点（最左下）
            if(pre && pre->rc == nullptr){
                pre->rc = node;
                //node->rf = 1; fuck wrong!!!!!!!
                pre->rf = 1;
            } 
            pre = node;
            iT(node->rc);
        }
    }
    void iOT_Normal(Treenode* node) const{
        if(node){
            iOT_Normal(node->lc);
            cout << node->val << " ";
            iOT_Normal(node->rc);
        }
    }
public:
    TBT() : root(nullptr), pre(nullptr){}
    void insert(int val){
        Treenode* newnode = new Treenode(val);
        if(root == nullptr){ root = newnode; return;}
        Treenode* curr = root;
        Treenode* prev = nullptr;
        while(curr){
            prev = curr;
            if(val < curr->val) curr = !curr->lf? curr->lc : nullptr;
            else if(val > curr->val) curr = !curr->rf? curr->rc : nullptr;
            else return;
        }
        if(val < prev->val) prev->lc = newnode;
        else prev->rc = newnode;
    }
    void CreateIT(){ pre = nullptr; if(root) iT(root);}
    void iOT_Thread() const{
        Treenode* curr = root;
        while(curr){
            while(!(curr->lf)) curr = curr->lc;
            cout << curr->val << " ";
            while(curr->rf && curr->rc != nullptr){ curr = curr->rc; cout << curr->val << " ";}
            curr = curr->rc;
            //while(!curr->lf) curr = curr->lc;
        }
        cout << endl;
    }
    void iOT_Normal() const{ iOT_Normal(root); cout << endl;}
};
int main(){
    TBT tbt;
    tbt.insert(10);
    tbt.insert(6);
    tbt.insert(14);
    tbt.insert(4);
    tbt.insert(8);
    tbt.insert(12);
    tbt.insert(16);
    // auto start1 = chrono::high_resolution_clock::now();
    // tbt.iOT_Normal();
    // auto end1 = chrono::high_resolution_clock::now();
    // auto duration1 = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    // cout << "iOT_Normal_runnning time: " << duration1 << "ms" << endl;
    tbt.CreateIT();
    auto start2 = chrono::high_resolution_clock::now();
    tbt.iOT_Thread();
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "iOT_Thread_runnning time: " << duration2 << "μs" << endl;
    return 0;
}
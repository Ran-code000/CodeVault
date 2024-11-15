#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;
class BST{
private:
    struct Treenode{
        int val;
        Treenode* lc;
        Treenode* rc;
        Treenode(const int& val) : val(val), lc(nullptr), rc(nullptr){}
    };
    Treenode* root;
    /* 注意！！！
    insert 函数：其逻辑是通过指针修改树的结构。由于在这个过程中直接修改了指针，当递归到合适的位置并成功插入节点后，函数自然结束，不需要再返回值给调用者。
    find 函数：其目的是在树中查找某个值并返回查找结果（布尔值），结果需要在多个递归调用之间传递，返回值显得尤为重要。
    */
    void insert(Treenode*& node, const  int& val){
        if(node == nullptr) node = new Treenode(val);
        else if(val < node->val) insert(node->lc, val);
        else if(val > node->val) insert(node->rc, val);
        else return;
    }
    bool find(Treenode* node, const int& val){
        if(node == nullptr) return false;
        if(val == node->val) return true;
        //！！！！！！！！致命 bug！！！
        //不 return ：即使递归调用找到了目标值，结果也不会被传递回上一级调用，最终返回的是默认值 false，即使中间某一级找到了目标值。
        //返回结果：递归调用的结果会被传递给上一级调用，最终返回正确的结果
        else if(val < node->val) return find(node->lc, val);
        else if(val > node->val) return find(node->rc, val);
        return false;
    }
    void remove(Treenode*& node, const int& val){
        if(node == nullptr) return;
        else if(val < node->val) remove(node->lc, val);
        else if(val > node->val) remove(node->rc, val);
        else{
            if(node->lc == nullptr && node->rc == nullptr) delete node, node = nullptr;
            else if(node->lc == nullptr){
                Treenode* temp = node;
                node = node->rc;
                delete temp;
            }else if(node->rc == nullptr){
                Treenode* temp = node;
                node = node->lc;
                delete temp;
            }else{
                // Treenode* minNode_of_rc = findMin(node->rc);
                // node->val = minNode_of_rc->val;
                // remove(node->rc, minNode_of_rc->val);

                Treenode* maxNode_of_rc = findMin(node->rc);
                node->val = maxNode_of_rc->val;
                remove(node->rc, maxNode_of_rc->val);
            }
        }
    }
    Treenode* findMin(Treenode* node) const{
        while(node && node->lc) node = node->lc;
        return node;
    }
    Treenode* findMax(Treenode* node) const{
        while(node && node->lc) node = node->lc;
        return node;
    }
    void clear(Treenode*& node){
        if(node == nullptr) return;
        clear(node->lc);
        clear(node->rc);
        delete node;
        node = nullptr;
    }
    void inOrder(Treenode* node) const{
        if(node == nullptr) return;
        inOrder(node->lc);
        cout << node->val << " ";
        inOrder(node->rc);
    }
    void preOrder(Treenode* node) const{
        if(node == nullptr) return;
        cout << node->val << " ";
        preOrder(node->lc);
        preOrder(node->rc);
    }
    void postOrder(Treenode* node) const{
        if(node == nullptr) return;
        postOrder(node->lc);
        postOrder(node->rc);
        cout << node->val << " ";
    }
public:
    BST() : root(nullptr){}
    ~BST(){ clear();}
    void insertRandom(int n){ 
        while(n--){
            int val = rand() % 100;
            insert(root, val);
        }
    }
    bool find(const int& val){ if(find(root, val)) return true; else return false;}
    void remove(const int& val){ 
        if(!find(root, val)){ cout << "Value " << val << " not found in the tree.\n"; return;}
        else remove(root, val);
    }
    void clear(){ clear(root);}
    void inOrder() const{ inOrder(root), cout << endl;}
    void preOrder() const{ preOrder(root), cout << endl;}
    void postOrder() const{ postOrder(root), cout << endl;}
    void Display() const{ inOrder(root), cout << endl;}
};
//text function
int main(){
    auto start = chrono::high_resolution_clock::now();
    BST BST;
    srand(time(0));
    BST.insertRandom(10);//生成10个数
    int val1 = rand() % 100, val2 = rand() % 100;
    cout << val1 << ": " << BST.find(val1) << endl;
    cout << val2 << ":"  << BST.find(val2) << endl;
    BST.remove(41);
    cout << "inOrder: ";
    BST.inOrder();
    cout << "preOrder: ";
    BST.preOrder();
    cout << "postOrder: ";
    BST.postOrder();
    BST.clear();
    auto end = chrono::high_resolution_clock::now();
    //cout << "running time: " << end - start << endl; wrong
    chrono::duration<double, milli> duration = end - start;
    cout << "running time: " << duration.count() << "ms" << endl;
    return 0;
}
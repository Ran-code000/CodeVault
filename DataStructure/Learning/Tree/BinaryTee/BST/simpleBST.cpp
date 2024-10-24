#include <iostream>
#include <ctime>
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
    void insert(Treenode*& node, const int& val){
        if(node == nullptr) node = new Treenode(val);
        else if(val < node->val) insert(node->lc, val);
        else if(val > node->val) insert(node->rc, val);
        else return;//已经有相同元素则不插入
    }
    //！！！！！致命 bug！！！
    //不 return ：即使递归调用找到了目标值，结果也不会被传递回上一级调用，最终返回的是默认值 false，即使中间某一级找到了目标值。
    //返回结果：递归调用的结果会被传递给上一级调用，最终返回正确的结果
    bool find(Treenode* node, const int& val){
        if(node == nullptr) return false;
        if(val == node->val) return true;
        //错误写法
        // else if(val < node->val) find(node->lc, val);
        // else if(val > node->val) find(node->rc, val);
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
                Treenode* minNode_of_rc = findMin(node->rc);
                node->val = minNode_of_rc->val;
                remove(node->rc, minNode_of_rc->val);
            }
        }
    }
    Treenode* findMin(Treenode* node) const{
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
    //计算操作（如计算树的高度）： 需要将每个子树的高度传递回上一级调用，以便计算整个树的高度
    int TreeDepth(Treenode* node) const{
        int depth = 0;
        if(node == nullptr) return depth;
        return depth = 1 + max(TreeDepth(node->lc), TreeDepth(node->rc));
    }
public:
    BST() : root(nullptr){}
    ~BST(){ clear();}
    void insertRandom(int n){ 
        while(n--){
            //srand(time(0)); !!!随机数种子只需要在主函数里设置一次即可
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
    int TreeDepth() const{ return TreeDepth(root);}
    void Display() const{ inOrder(root), cout << endl;}
};
//text function
int main(){
    BST bst;
    srand(time(0));
    bst.insertRandom(20);//生成10个数
    bst.Display();
    int val1 = rand() % 100, val2 = rand() % 100;
    cout << val1 << ": " << bst.find(val1) << endl;
    cout << val2 << ":"  << bst.find(val2) << endl;
    bst.remove(41);
    cout << "inOrder: ";
    bst.inOrder();
    cout << "preOrder: ";
    bst.preOrder();
    cout << "postOrder: ";
    bst.postOrder();
    cout << "TreeDepth: ";
    cout << bst.TreeDepth();
    bst.clear();
    return 0;
}
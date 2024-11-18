#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct NTreeNode{
    double x_min, x_max, y_min, y_max;
    pair<double, double> point;
    NTreeNode* child[4];
    bool isleafNode;

    NTreeNode(double xmin, double xmax, double ymin, double ymax) : x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), isleafNode(true){
        point = {-1, -1};
        fill(begin(child), end(child), nullptr); // 子节点指针初始化为空
    }
    bool iscontained(double x, double y){
        return x >= x_min && x <= x_max && y >= y_min && y <= y_max;
    }
    void split(){
        // double x_mid = x_min + ((x_max - x_min) >> 1);
        // double y_mid = y_min + ((y_max - y_min) >> 1);
        double x_mid = (x_min + x_max) / 2.0; 
        double y_mid = (y_min + y_max) / 2.0;  
        child[0] = new NTreeNode(x_min, x_mid, y_min, y_mid);
        child[1] = new NTreeNode(x_min, x_mid, y_mid, y_max);
        child[2] = new NTreeNode(x_mid, x_max, y_min, y_mid);
        child[3] = new NTreeNode(x_mid, x_max, y_mid, y_max);
        isleafNode = false;
    }
};
class NTree{
private:
    NTreeNode* root;
    void insert(NTreeNode*& node, double x, double y){
        if(!node->iscontained(x, y)) return;
        if(node->isleafNode){
            if(node->point.first== -1) node->point = {x, y};
            else{
                node->split();
                insertTochild(node, node->point.first, node->point.second);
                node->point = {-1, -1};
                insertTochild(node, x, y);
            }
        }else{
            insertTochild(node, x, y);
        }
    }
    void insertTochild(NTreeNode* node, double x, double y){
        for(int i = 0; i < 4; i++){
            if(node->child[i]->iscontained(x, y)){
                insert(node->child[i], x, y);
                break;
            }
        }
    }
public:
    NTree(){
        root = new NTreeNode(0, 10, 0, 10);
    }
    void insert(double x, double y){
        insert(root, x, y);
    }
    void levelorder(){
        queue<NTreeNode*> q;
        q.push(root);
        while(!q.empty()){
            NTreeNode* currNode = q.front();
            q.pop();
            if(!currNode->isleafNode){
                for (int i = 0; i < 4; i++) 
                    if (currNode->child[i]) q.push(currNode->child[i]);
            }
            else {
                if(currNode->point.first != -1) cout << currNode->point.first << " " << currNode->point.second << endl;
            }
        }
    }
};
int main(){
    int n; cin >> n;
    NTree nt;
    for(int i = 0; i < n; i++){
        double x, y; cin >> x >> y;
        nt.insert(x, y);
    }
    nt.levelorder();
    return 0;
}
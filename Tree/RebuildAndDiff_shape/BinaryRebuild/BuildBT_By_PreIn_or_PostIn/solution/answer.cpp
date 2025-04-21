#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;
struct node{
    char val;
    node* left;
    node* right;
    node(char val) : val(val), left(nullptr), right(nullptr){}
};
node* buildTree(const string& preorder, const string& inorder, int& preid, int instart, int inend, unordered_map<int, int>& inmap){
    if(instart > inend) return nullptr;

    char rootval = preorder[preid++];
    int rootindex = inmap[rootval];
    
    node* root = new node(rootval);
    root->left = buildTree(preorder, inorder, preid, instart, rootindex - 1, inmap);
    root->right = buildTree(preorder, inorder, preid, rootindex + 1, inend, inmap);

    return root;
}
void leverOrder(node* root){
    queue<node*> q;
    
    q.push(root);
    while(!q.empty()){
        node* temp = q.front(); q.pop();

        cout << temp->val;
        if(temp->left != nullptr) q.push(temp->left);
        if(temp->right != nullptr) q.push(temp->right);
    }
}
int main(){
    int n; cin >> n;
    while(n--){
        string preorder, inorder;
        cin >> preorder >> inorder;

        unordered_map<int, int> inMap;
        for(int i = 0; i < inorder.size(); i++) inMap[inorder[i]] = i;
        
        int preindex = 0;
        node* root = buildTree(preorder, inorder, preindex, 0, inorder.size() - 1, inMap);
        leverOrder(root);

        cout << endl;
    }
    return 0;
}
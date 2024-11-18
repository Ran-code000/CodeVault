void levelTraversal(BinaryNode* root, void (*visit)(T &x)){}
    if(root == nullptr) return;
    queue<BinaryNode<T>*>nodequeue;
    nodequeue.push(root);
    while(!nodequeue.empty()){
        BinaryNode<T>* node = nodequeue.front();
        nodequeue.pop();
        visit(node->data);
        if(node->lchild != nullptr) nodequeue.push(node->lchild);
        if(node->rchild != nullptr) nodequeue.push(node->rchild);
    }
]
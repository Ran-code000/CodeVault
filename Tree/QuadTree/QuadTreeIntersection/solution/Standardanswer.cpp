Node *intersect(Node *quadTree1, Node *quadTree2)
{
    if (quadTree1->isLeaf)
    {
        if (quadTree1->val)
        {
            return new Node(true, true);
        }
        return new Node(quadTree2->val, quadTree2->isLeaf, quadTree2->topLeft, quadTree2->topRight, quadTree2->bottomLeft, quadTree2->bottomRight);
    }
    else if (quadTree2->isLeaf)
    {
        return intersect(quadTree2, quadTree1);
    }
    else
    {
        Node *o1 = intersect(quadTree1->topLeft, quadTree2->topLeft);
        Node *o2 = intersect(quadTree1->topRight, quadTree2->topRight);
        Node *o3 = intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
        Node *o4 = intersect(quadTree1->bottomRight, quadTree2->bottomRight);
        if (o1->isLeaf && o2->isLeaf && o3->isLeaf && o4->isLeaf && o1->val == o2->val && o1->val == o3->val && o1->val == o4->val)
            return new Node(o1->val, true);
        else
            return new Node(false, false, o1, o2, o3, o4);
    }
}
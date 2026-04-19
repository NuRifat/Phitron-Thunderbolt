bool isBST(Node* root, int &prev){
    if(root==NULL) return true;
    if(!isBST(root->left, prev)) return false;
    if(root->data <= prev) return false;
    prev = root->data;
    return isBST(root->right,prev);
}
bool checkBST(Node* root) {
    int prev = -1; 
    return isBST(root,prev);
}
#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK }; 
  
struct Node 
{ 
    int data; 
    bool color; 
    Node *left, *right, *parent; 
  
    // Constructor 
    Node(int data) 
    { 
       this->data = data; 
       left = right = parent = nullptr; 
       this->color = RED; 
    } 
}; 
  
// Class to represent Red-Black Tree 
class RBTree 
{ 
private: 
    Node *root; 
protected: 
    void rotateLeft(Node *&, Node *&); 
    void rotateRight(Node *&, Node *&); 
    void fixViolation(Node *&, Node *&); 
public: 
    // Constructor 
    RBTree() { root = nullptr; } 

    void insert(const int &n); 
    void inorder(); 
    void levelOrder(); 
}; 
  
// A recursive function to do level order traversal 
void inorderHelper(Node *root) 
{ 
    if (root == nullptr) 
        return; 
  
    inorderHelper(root->left); 
    cout << root->data << "  "; 
    inorderHelper(root->right); 
} 
  
// A utility function to insert a new node with given key in BST 
Node* BSTInsert(Node* root, Node *ptr) 
{ 
    // If the tree is empty, return a new node 
    if (root == nullptr) 
       return ptr; 
  
    // Otherwise, recur down the tree 
    if (ptr->data < root->data) 
    { 
        root->left  = BSTInsert(root->left, ptr); 
        root->left->parent = root; 
    } 
    else if (ptr->data > root->data) 
    { 
        root->right = BSTInsert(root->right, ptr); 
        root->right->parent = root; 
    } 
  
    /* return the (unchanged) node pointer */
    return root; 
} 
  
// Utility function to do level order traversal 
void levelOrderHelper(Node *root) 
{ 
    if (root == nullptr) 
        return; 
  
    std::queue<Node *> q; 
    q.push(root); 
  
    while (!q.empty()) 
    { 
        Node *temp = q.front(); 
        cout << temp->data << "  "; 
        q.pop(); 
  
        if (temp->left != nullptr) 
            q.push(temp->left); 
  
        if (temp->right != nullptr) 
            q.push(temp->right); 
    } 
} 
  
void RBTree::rotateLeft(Node *&root, Node *&ptr) 
{ 
    Node *ptr_right = ptr->right; 
  
    ptr->right = ptr_right->left; 
  
    if (ptr->right != nullptr) 
        ptr->right->parent = ptr; 
  
    ptr_right->parent = ptr->parent; 
  
    if (ptr->parent == nullptr) 
        root = ptr_right; 
  
    else if (ptr == ptr->parent->left) 
        ptr->parent->left = ptr_right; 
  
    else
        ptr->parent->right = ptr_right; 
  
    ptr_right->left = ptr; 
    ptr->parent = ptr_right; 
} 
  
void RBTree::rotateRight(Node *&root, Node *&ptr) 
{ 
    Node *ptr_left = ptr->left; 
  
    ptr->left = ptr_left->right; 
  
    if (ptr->left != nullptr) 
        ptr->left->parent = ptr; 
  
    ptr_left->parent = ptr->parent; 
  
    if (ptr->parent == nullptr) 
        root = ptr_left; 
  
    else if (ptr == ptr->parent->left) 
        ptr->parent->left = ptr_left; 
  
    else
        ptr->parent->right = ptr_left; 
  
    ptr_left->right = ptr; 
    ptr->parent = ptr_left; 
} 
  
// This function fixes violations caused by BST insertion 
void RBTree::fixViolation(Node *&root, Node *&ptr) 
{ 
    Node *parent_ptr = nullptr; 
    Node *grandparent_ptr = nullptr; 
  
    while ((ptr != root) && (ptr->color != BLACK) && 
           (ptr->parent->color == RED)) 
    { 
  
        parent_ptr = ptr->parent; 
        grandparent_ptr = ptr->parent->parent; 
  
        /*  Case: A 
            Parent of ptr is left child of Grandparent of ptr */
        if (parent_ptr == grandparent_ptr->left) 
        { 
  
            Node *uncle_ptr = grandparent_ptr->right; 
  
            /* Case: 1 
               The uncle of ptr is also red 
               Only Recoloring required
             */
            if (uncle_ptr != nullptr && uncle_ptr->color == RED) 
            { 
                grandparent_ptr->color = RED; 
                parent_ptr->color = BLACK; 
                uncle_ptr->color = BLACK; 
                ptr = grandparent_ptr; 
            } 
  
            else
            { 
                /* Case: 2 
                   Ptr is right child of its parent 
                   Left-rotation required 
                */
                if (ptr == parent_ptr->right) 
                { 
                    rotateLeft(root, parent_ptr); 
                    ptr = parent_ptr; 
                    parent_ptr = ptr->parent; 
                } 
  
                /* Case: 3 
                   ptr is left child of its parent 
                   Right-rotation required */
                rotateRight(root, grandparent_ptr); 
                swap(parent_ptr->color, grandparent_ptr->color); 
                ptr = parent_ptr; 
            } 
        } 
  
        /* Case: B 
           Parent of ptr is right child of Grandparent of ptr */
        else
        { 
            Node *uncle_ptr = grandparent_ptr->left; 
  
            /*  Case: 1 
                The uncle of ptr is also red 
                Only Recoloring required 
            */
            if ((uncle_ptr != nullptr) && (uncle_ptr->color == RED)) 
            { 
                grandparent_ptr->color = RED; 
                parent_ptr->color = BLACK; 
                uncle_ptr->color = BLACK; 
                ptr = grandparent_ptr; 
            } 
            else
            { 
                /* Case: 2 
                   Ptr is left child of its parent 
                   Right-rotation required 
                */
                if (ptr == parent_ptr->left) 
                { 
                    rotateRight(root, parent_ptr); 
                    ptr = parent_ptr; 
                    parent_ptr = ptr->parent; 
                } 
  
                /* Case: 3 
                   Ptr is right child of its parent 
                   Left-rotation required 
                */
                rotateLeft(root, grandparent_ptr); 
                swap(parent_ptr->color, grandparent_ptr->color); 
                ptr = parent_ptr; 
            } 
        } 
    } 
  
    root->color = BLACK; 
} 
  
// Function to insert a new node with given data 
void RBTree::insert(const int &data) 
{ 
    Node *ptr = new Node(data); 
  
    // Do a normal BST insert 
    root = BSTInsert(root, ptr); 
  
    // Fix Red Black Tree violations 
    fixViolation(root, ptr); 
} 
  
// Function to do inorder and level order traversals 
void RBTree::inorder()     { inorderHelper(root); } 
void RBTree::levelOrder()  { levelOrderHelper(root); } 
  
int main() 
{ 
    RBTree tree; 
  
    tree.insert(7); 
    tree.insert(6); 
    tree.insert(5); 
    tree.insert(4); 
    tree.insert(3); 
    tree.insert(2); 
    tree.insert(1); 
  
    cout << "Inoder Traversal of Created Tree\n"; 
    tree.inorder(); 
  
    cout << "\n\nLevel Order Traversal of Created Tree\n"; 
    tree.levelOrder(); 
  
    return 0; 
} 
#include "BST.h"
#include "TreeUtils.h"
#include <iostream>
using namespace std;

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    destroy(root);                  // postorder delete of every node
}

// ============================ Q4 ============================

bool BST::insert(int value)
{
    bool inserted = false;
    root = insertInto(root, value, inserted);
    return inserted;
}

TreeNode* BST::insertInto(TreeNode* node, int value, bool& inserted)
{
    if (node == nullptr) {          // empty spot: the new node goes here
        inserted = true;
        return makeNode(value);
    }
    if (value < node->data)
        node->left = insertInto(node->left, value, inserted);
    else if (value > node->data)
        node->right = insertInto(node->right, value, inserted);
    // value == node->data: duplicate, nothing changes, inserted stays false
    return node;                    // the root of this subtree, for the parent
}

// ============================ Q5 ============================

bool BST::find(int value) const
{
    const TreeNode* current = root;
    while (current != nullptr) {    // walk down, one side only
        if (value == current->data)
            return true;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;                   // fell off the tree: not there
}

bool BST::findMin(int& value) const
{
    if (root == nullptr)
        return false;
    const TreeNode* current = root;
    while (current->left != nullptr)    // leftmost node
        current = current->left;
    value = current->data;
    return true;
}

bool BST::findMax(int& value) const
{
    if (root == nullptr)
        return false;
    const TreeNode* current = root;
    while (current->right != nullptr)   // rightmost node
        current = current->right;
    value = current->data;
    return true;
}

// ============================ Q7 ============================

bool BST::remove(int value)
{
    bool removed = false;
    root = removeFrom(root, value, removed);
    return removed;
}

TreeNode* BST::removeFrom(TreeNode* node, int value, bool& removed)
{
    if (node == nullptr)            // not found: removed stays false
        return nullptr;

    if (value < node->data)
        node->left = removeFrom(node->left, value, removed);
    else if (value > node->data)
        node->right = removeFrom(node->right, value, removed);
    else {
        // found it
        if (node->left == nullptr || node->right == nullptr) {
            // leaf or one child: the parent links to the child
            // (child is nullptr for a leaf)
            TreeNode* child = (node->left != nullptr) ? node->left : node->right;
            delete node;
            removed = true;
            return child;
        }
        // two children: take the key of the inorder successor
        // (the smallest key of the right subtree) and remove that node
        TreeNode* successor = node->right;
        while (successor->left != nullptr)
            successor = successor->left;
        node->data = successor->data;
        node->right = removeFrom(node->right, successor->data, removed);
    }
    return node;                    // this node stays; return it to the parent
}

// ============================ wrappers ============================

void BST::preorder() const   { ::preorder(root); }
void BST::inorder() const    { ::inorder(root); }
void BST::postorder() const  { ::postorder(root); }
int  BST::height() const     { return ::height(root); }
bool BST::isBalanced() const { return ::isBalanced(root); }
bool BST::isEmpty() const    { return root == nullptr; }

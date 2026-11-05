#include "TreeUtils.h"
#include <iostream>
#include <queue>                    // std::queue: the library version of
using namespace std;                // Week 4's Queue, for any type

TreeNode* makeNode(int value)
{
    TreeNode* node = new TreeNode;
    node->data = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// ============================ Q2 ============================

void preorder(const TreeNode* node)
{
    if (node == nullptr)            // base case: empty tree, nothing to print
        return;
    cout << node->data << " ";      // node ...
    preorder(node->left);           // ... left ...
    preorder(node->right);          // ... right
}

void inorder(const TreeNode* node)
{
    if (node == nullptr)
        return;
    inorder(node->left);            // left ...
    cout << node->data << " ";      // ... node ...
    inorder(node->right);           // ... right
}

void postorder(const TreeNode* node)
{
    if (node == nullptr)
        return;
    postorder(node->left);          // left ...
    postorder(node->right);         // ... right ...
    cout << node->data << " ";      // ... node
}

int countNodes(const TreeNode* node)
{
    if (node == nullptr)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(const TreeNode* node)
{
    if (node == nullptr)            // must come first: node->left below
        return 0;                   // would crash on nullptr
    if (node->left == nullptr && node->right == nullptr)
        return 1;                   // a leaf: no children
    return countLeaves(node->left) + countLeaves(node->right);
}

// ============================ Q3 ============================

int height(const TreeNode* node)
{
    if (node == nullptr)
        return -1;                  // empty tree; so a leaf gets 1 + (-1) = 0
    int hl = height(node->left);
    int hr = height(node->right);
    return 1 + (hl > hr ? hl : hr); // 1 + the taller subtree
}

void levelOrder(const TreeNode* node)
{
    if (node == nullptr)
        return;
    queue<const TreeNode*> q;       // FIFO: nodes waiting to be printed
    q.push(node);
    while (!q.empty()) {
        const TreeNode* current = q.front();   // read front() first,
        q.pop();                               // pop() returns nothing
        cout << current->data << " ";
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

// ============================ Q6 ============================

bool isBalanced(const TreeNode* node)
{
    if (node == nullptr)
        return true;                // an empty tree is balanced
    int diff = height(node->left) - height(node->right);
    if (diff > 1 || diff < -1)
        return false;               // this node breaks the rule
    return isBalanced(node->left) && isBalanced(node->right);
}

// ============================ memory ============================

void destroy(TreeNode* node)
{
    if (node == nullptr)
        return;
    destroy(node->left);            // children first ...
    destroy(node->right);
    delete node;                    // ... the node last (postorder)
}

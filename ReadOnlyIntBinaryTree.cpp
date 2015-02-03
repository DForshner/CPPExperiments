#include "ReadOnlyIntBinaryTree.h"
#include "assert.h"

using namespace readonly_int_binary_tree;

ReadOnlyIntBinaryTree::ReadOnlyIntBinaryTree()
{
  root = nullptr;
}

ReadOnlyIntBinaryTree::~ReadOnlyIntBinaryTree()
{
  DestoryTree();
}

// Public version of insert to handle case of root being
// null or call recursive version.
void ReadOnlyIntBinaryTree::Insert(int key)
{
  if (root != nullptr)
    Insert(key, root);
  else
  {
    root = new Node;
    root->key_value = key;
    root->left = nullptr;
    root->right = nullptr;
  }
}

void ReadOnlyIntBinaryTree::Insert(int key, Node *node)
{
  // Check if the key belongs on the left or right
  // side of the current node.
  if (key < node->key_value)
  {
    // If this node already has a child continue 
    // recursively searching to the left.
    // Otherwise create a new left child node.
    if (node->left != nullptr)
      Insert(key, node->left);
    else
    {
      node->left = new Node();
      node->left->key_value = key;
      node->left->left = nullptr;
      node->left->right = nullptr;
    }
  }
  // If this node already has a right child continue
  // to recursively search to the right.
  // Otherwise create a new right child node.
  else if (key >= node->key_value)
  {
    if (node->right != nullptr)
      Insert(key, node->right);
    else
    {
      node->right = new Node();
      node->right->key_value = key;
      node->right->left = nullptr;
      node->right->right = nullptr;
    }
  }
}

// Public version of Search to call recursive version.
Node *ReadOnlyIntBinaryTree::Search(int key)
{
  return Search(key, root);
}

// Recursively searches down the tree until it either finds
// a node with a value that matches the key or it reaches
// the bottom of the tree (uninitialized node) which means
// the key being searched for does not exist in the tree.
Node *ReadOnlyIntBinaryTree::Search(int key, Node *node)
{
  if (node != nullptr)
  {
    if (key == node->key_value)
      return node;
    if (key < node->key_value)
      return Search(key, node->left);
    else
      return Search(key, node->right);
  }
  
  return nullptr;
}

// Public version of DestroyTree to call recursive version.
void ReadOnlyIntBinaryTree::DestoryTree()
{
  DestoryTree(root);
  root = nullptr;
}

// Recursively searches to the bottom of the tree (node is null)
// and then works its way back up deleting nodes as it goes.
void ReadOnlyIntBinaryTree::DestoryTree(Node *node)
{
  if (node != nullptr)
  {
    DestoryTree(node->left);
    DestoryTree(node->right);
    delete node;
  }
}
#pragma once

// A simple read-only int Binary Tree
//  
// A binary tree is a data structure for rapidly storing and retrieving sorted data.
// It is composed of parent nodes and child nodes where the left child node is less
// than the parent and the right child has an equal or greater value.
//
// Notes:
// 1) In the best case each nodes has both a left and right child which produces a "balanced"
// binary tree.  In the worst case each node only has one child which causes the tree to
// degrade into a linked list.
// 2) Search is O(log(n))
// 3) Filling the entire tree takes O(n log(n)).

namespace readonly_int_binary_tree
{
    struct Node
    {
        int key_value;
        Node *left;
        Node *right;
    };

    class ReadOnlyIntBinaryTree
    {
    public:
      ReadOnlyIntBinaryTree();
      ~ReadOnlyIntBinaryTree();

      void Insert(int key);
      Node *Search(int key);
      void DestoryTree();

    private:
      void Insert(int key, Node *node);
      Node *Search(int key, Node *node);
      void DestoryTree(Node *node);

      Node *root;
    };
}
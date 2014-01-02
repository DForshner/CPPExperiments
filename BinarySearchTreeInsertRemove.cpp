// Inserting/Removing unique elements from a binary search tree.
//
// No re-balancing has been implemented to keep height of tree height at O(log(n))
// so performance can vary between O(log(n) to O(n) for insert/remove operations.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <memory>
#include <list>
#include <cassert>
#include <utility>
#include <chrono>

using namespace std;

#ifdef _DEBUG
static int destructed_nodes; // Static member assigned zero by default;
#endif

template <typename T>
class BinarySearchTree {

public:

  virtual ~BinarySearchTree() { clear(); }

  bool empty() const { return !root.get(); }

  void clear() { clear(&root); }

  bool insert(const T& key) {

    if (empty()) {
      root = unique_ptr<Node>(new Node{ key, nullptr, nullptr });
      return true;
    }

    Node* current = root.get();
    Node* parent = nullptr;

    // Traverse tree downwards until we find an empty node.
    while (current) {
      parent = current;

      // Duplicate key - all elements should be unique
      if (key == current->data)
        return false;

      // If key is less go left or if key is greater go right.
      current = (key < current->data) ? current->left.get() : current->right.get();
    }
    assert(current == nullptr);

    // Insert key according to < or > parent data
    if (key < parent->data)
      parent->left.reset(new Node{ key });
    else
      parent->right.reset(new Node{ key });

    return true;
  }

  // Removes a node.  Returns true on success.
  bool remove(const T& key) {
    Node* current = root.get();
    Node* parent = nullptr;

    // Traverse downwards until we find an empty or matching node
    while (current && current->data != key) {
      parent = current;
      // If key is less go left or if key is greater go right.
      current = (key < current->data) ? current->left.get() : current->right.get();
    }
    assert(current == nullptr || current->data == key);

    // Was the found in the tree?
    if (!current) 
      return false;

    if (current->right) {
      // If a right subtree exists then then this node will be
      // replaced with the minimum node in the right node's subtree.

      // traverse down the right subtree to find the right subtree's minimum.
      Node* replacement = current->right.get();
      auto replacement_parent = current;
      while (replacement->left) {
        replacement_parent = replacement;
        replacement = replacement->left.get();
      }
      assert(replacement != nullptr);

      // Attach the deleted node's left child to its replacement.
      replacement->left.reset(current->left.release());

      Node* replacement_old_right = replacement->right.release();
      Node* replace_parent_replacement_link = nullptr;

      // If the node being deleted isn't the replacement's parent 
      // then remove the deleted node's right and attach it to replacement.
      if (current->right.get() != replacement) {
        replacement->right.reset(current->right.release());
        replace_parent_replacement_link = replacement_old_right;
      }

      // Attach the replacement's old right to it's parent left
      if (replacement_parent->left.get() == replacement) {
        replacement = replacement_parent->left.release();
        replacement_parent->left.reset(replace_parent_replacement_link);
      }
      // Attach the replacement's old right to it's parent right
      else {
        replacement = replacement_parent->right.release();
        replacement_parent->right.reset(replace_parent_replacement_link);
      }

      replace_parent_child_link(parent, current, replacement);

      // If the node being removed is the root replace it and re-attach the
      // replacement nodes right subtree.
      if (root.get() == current) {
        replacement->right.reset(replacement_old_right);
        root.reset(replacement);
      }
    }
    else {
      // If there was was no right subtree then just replace the current
      // with its left child.

      // If the node being removed is the root replace it.
      if (root.get() == current)
        root.reset(current->left.release());

      replace_parent_child_link(parent, current, current->left.release());
    }
    return true;
  }

  // Traverse downwards displaying in a breadth first search pattern
  void display_BFS() const {
    list<Node*> queue;
    queue.push_front(root.get());

    while (!empty() && !queue.empty()) {
      auto current = queue.back();
      queue.pop_back();

      cout << current->data << " ";

      if (current->left.get())
        queue.push_front(current->left.get());

      if (current->right.get())
        queue.push_front(current->right.get());
    }

    cout << endl;
  }

private:

  // Nodes remain under ownership of unique ptr so they will
  // exist as long as the unique pointer does.
  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
#ifdef _DEBUG
    ~Node() { --destructed_nodes; }
#endif
  };

  unique_ptr<Node> root = nullptr;

  // Recursively delete all nodes
  void clear(unique_ptr<Node>* node) {

    // If nullptr do nothing
    if (!node->get())
      return;
    
    if ( node->get()->left.get())
      clear(&((*node)->left));
    
    if ( (*node)->right.get())
      clear(&((*node)->right));

    node->reset(nullptr);
  }

  // Replace the link between parent and child with new link.
  void replace_parent_child_link(Node* parent, Node* child, Node* new_link) {
    // If the child is the root node do nothing.
    if (!parent)
      return;

    // If the left child replace left link.
    if (parent->left.get() == child)
      parent->left.reset(new_link);
    else
      parent->right.reset(new_link);
  }
};


#ifdef _DEBUG
int main()
{

  auto tree = new BinarySearchTree<int>();

  tree->insert(10);
  tree->insert(11);
  tree->insert(9);
  tree->insert(4);
  tree->insert(8);
  tree->insert(3);
  tree->insert(44);
  tree->insert(14);
  tree->insert(12);
  tree->insert(16);
  tree->insert(100);
  tree->insert(2);
  tree->insert(13);
  tree->insert(21);
  tree->insert(5);

  tree->display_BFS();
  assert(destructed_nodes == 0);

  cout << "Attempt add duplicate node (10)" << endl;
  assert(tree->insert(10) == false);
  tree->display_BFS();

  cout << "Remove root node (10)" << endl;
  tree->remove(10);
  tree->display_BFS();
  assert(destructed_nodes == -1);

  cout << "Attempt remove non existent node (10)" << endl;
  assert(tree->remove(10) == false);
  tree->display_BFS();
  assert(destructed_nodes == -1);

  cout << "Remove non root node (13) with right subtree" << endl;
  tree->remove(13);
  tree->display_BFS();
  assert(destructed_nodes == -2);

  cout << "Remove non root node (4) with no right subtree" << endl;
  tree->remove(4);
  tree->display_BFS();
  assert(destructed_nodes == -3);

  cout << "Add & remove a random node" << endl;
  srand(time(0));
  int r;
  while (true) {
    r = rand() % 30;
    if (tree->insert(r))
      break;
  }

  tree->display_BFS();
  tree->remove(r);
  tree->display_BFS();
  assert(destructed_nodes == -4);

  cout << "Clearing tree" << endl;
  tree->clear();
  tree->display_BFS();
  assert(destructed_nodes == -16);

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}

#endif
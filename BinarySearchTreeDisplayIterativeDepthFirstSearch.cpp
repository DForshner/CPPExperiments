// Display the nodes of a binary search tree in depth first search order.
// 
// Implemented using iteration instead of recursion.
// O(n) display
// O(log(n)) to O(n) insert
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <memory>
#include <list>
#include <cassert>
#include <utility>

using namespace std;

template <typename T>
class BinarySearchTree {

public:

  // ** Majority of ADT methods omitted ** //

  bool empty() const { return !root.get(); }

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

  // Traverse downwards displaying in a depth first search (non-recursive) 
  void display_DFS() const {
    cout << endl << "############ Binary Search Tree Contents - Depth First Search (In Order Traversal) ############ " << endl;

    // first: false = search, true = visit
    list<pair<bool, Node*>> stack;
    stack.push_front(pair<bool, Node*>(false, root.get()));

    while (!stack.empty()) {
      display_stack_contents(stack);

      pair<bool, Node*> current = stack.front();
      stack.pop_front();

      // If visiting display the current node and continue on to the next node on the stack.
      if (current.first == true) {
        cout << "Visiting: " << current.second->data << endl;
        continue;
      }

      // If we are here it means we are searching the current node.

      if (current.second->right.get())
        stack.push_front(pair<bool, Node*>(false, current.second->right.get()));

      // Mark current node for visit and push back onto stack.
      if (current.second)
        stack.push_front(pair<bool, Node*>(true, current.second));

      if (current.second->left.get())
        stack.push_front(pair<bool, Node*>(false, current.second->left.get()));
    }

    cout << endl;
  }

private:

  struct Node {
    T data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
  };

  void display_stack_contents(const list<pair<bool, Node*>>& stack) const {
    cout << "[ ";
    for (const auto& e : stack)
      cout << "(" << e.first << "|" << e.second->data << "),";
    cout << "] " << endl;
  }

  unique_ptr<Node> root = nullptr;
};

int main()
{
  auto tree = new BinarySearchTree<int>();

  tree->insert(10);
  tree->insert(11);
  tree->insert(9);
  tree->insert(4);
  tree->insert(8);
  tree->insert(3);
  tree->insert(14);
  tree->insert(12);
  tree->insert(16);
  tree->insert(2);
  tree->insert(13);

  tree->display_DFS();

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
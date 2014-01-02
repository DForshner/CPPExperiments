// Display the nodes of a binary search tree in breadth first search order.
// 
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

  // Traverse downwards displaying in a breadth first search pattern
  void display_BFS() const {
    cout << endl << "############ Binary Search Tree Contents - Breadth First Search ############ " << endl;

    list<Node*> queue;
    queue.push_front(root.get());

    while (!queue.empty()) {
      display_queue_contents(queue);

      auto current = queue.back();
      queue.pop_back();

      cout << "Visiting: " << current->data << endl;

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
  };

  void display_queue_contents(const list<Node*>& queue) const {
    cout << "[ ";
    for (const auto& e : queue)
      cout << "(" << e->data << "),";
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

  tree->display_BFS();

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
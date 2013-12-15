// Partition a linked list around a value x, such that all nodes
// less than x come before all nodes greater than or equal to x.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename T>
struct Node {
  T val;
  shared_ptr<Node<T>> next;
  Node(T val, shared_ptr<Node<T>> next) : val(val), next(next) {}
};

template <typename T>
void partition(shared_ptr<Node<T>> *node, T pivot) {
  shared_ptr<Node<T>> greater = nullptr, less = nullptr;

  while (*node) {
    auto next = (*node)->next;

    if ((*node)->val > pivot) {
      (*node)->next = greater;
      greater = (*node);
    } else {
      (*node)->next = less;
      less = (*node);
    }

    // Move to next element
    *node = next;
  }

  // Check there are elements in the greater list to append to.
  if (!(greater)) {
    *node = less;
    return;
  }

  // Scan to end of greater list and append the less list.
  auto greater_tail = greater;
  while (greater_tail->next)
    greater_tail = greater_tail->next;
  greater_tail->next = less;

  *node = greater;
}

template <typename T>
shared_ptr<Node<T>> convert_to_linked_list(const vector<T> &vec) {
  if (vec.empty())
    return nullptr;

  shared_ptr<Node<T>> head = nullptr, tail = nullptr;
  for (const T &val : vec) { // By ref to avoid copying
    auto current = shared_ptr<Node<T>>(new Node<T>(val, nullptr));

    // If head exists append to tail else set as head.
    (head) ? tail->next = current: head = current;

    tail = current;
  }

  return head;
}

template <typename T>
void display(const shared_ptr<Node<T>> &head) {
  auto current = head;
  cout << endl << "start->";
  while (current) {
    cout << current->val << "->";
    current = current->next;
  }
  cout << "end" << endl;
}

int main()
{
  vector<int> values { 5, 10, 3, 6, 8, 4, 2, 8, 7, 6, 3, 2, 1, 2, 3, 4 };
  auto list = convert_to_linked_list(values);
  cout << "Before" << endl;
  display(list);

  partition(&list, 5);
  cout << "After" << endl;
  display(list);

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
// Write a function that merges two sorted linked lists together.
//
// O(n) time complexity and O(1) space complexity.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>;
#include <memory>;
#include <vector>;

using namespace std;

template <typename T>
struct Node {
  T data;
  shared_ptr<Node<T>> next;
};

template <typename T>
shared_ptr<Node<T>> merge(shared_ptr<Node<T>> a, shared_ptr<Node<T>> b) {
  // Check if there is anything to merge.
  if (a == nullptr && b != nullptr)
    return b;
  if (a != nullptr && b == nullptr)
    return a;
  
  // Pick the first element
  shared_ptr<Node<T>> head;
  if (a->data <= b->data) {
    head = a;
    a = a->next;
  }
  else {
    head = b;
    b = b->next;
  }

  // If there are elements in both lists chose the smaller
  // of the element from the lists.
  shared_ptr<Node<T>> current = head;
  while (a != nullptr && b != nullptr) {
    if (a->data <= b->data) {
      current->next = a;
      a = a->next;
    }
    else {
      current->next = b;
      b = b->next;
    }

    current = current->next;
  }

  // Add any remaining elements in list a.
  while (a != nullptr) {
    current->next = a;
    a = a->next;
    current = current->next;
  }

  // Add any remaining elements in list b.
  while (b != nullptr) {
    current->next = b;
    b = b->next;
    current = current->next;
  }

  return head;
}

template <typename T>
const shared_ptr<Node<T>> to_linked_list(const vector<T>& vec)
{
  shared_ptr<Node<T>> prev, head = nullptr;
  for (const auto &value: vec) { // access by reference to avoid copying
    auto current = shared_ptr<Node<T>>(new Node<T>());
    current->data = value;
    current->next = nullptr; // tail node will have next = nullptr.

    // If head node save for return else update the previous node.
    if (prev == nullptr)
      head = current;
    else
      prev->next = current;

    prev = current;
  }

  return head;
}

template <typename T>
void display(const shared_ptr<Node<T>> ptr) {
  cout << endl << "[HEAD]->";
  auto current = ptr;
  while (current) {
    cout << current->data << "->";
    current = current->next;
  }
  cout << "[TAIL/NULL]" << endl;
}

void main() {
  auto a = new vector<int> { 1, 3, 5, 6, 8, 9, };
  cout << endl << "List A";
  auto list_a = to_linked_list(*a);
  display(list_a);

  auto b = new vector<int> { 0, 2, 4, 7 };
  cout << endl << "List B";
  auto list_b = to_linked_list(*b);
  display(list_b);

  cout << endl << "Merged List";
  auto sorted = merge(list_a, list_b);
  display(sorted);

  // Cleanup
  delete a;
  delete b;

  cout << std::endl << "[Press enter to exit]" << std::endl;
  std::cin.ignore();
}
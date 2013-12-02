// Iteratively reverse a singly linked list.
//
// O(1) storage and O(n) time complexity.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <memory>

using namespace std;

template<typename T>
struct Node
{
  shared_ptr<Node<T>> next;
  T val;
};

template <typename T>
shared_ptr<Node<T>> build_list(int size) {

  auto head = shared_ptr<Node<T>>(new Node<T>());
  head->val = 0;

  shared_ptr<Node<T>> current = head;
  for (int i = 1; i <= size; i++) {
    auto next = shared_ptr<Node<T>>(new Node<T>());
    next->val = i;

    current->next = next;
    current = next;
  }

  current->next == nullptr;

  return head;
}

template <typename T>
void display_list(shared_ptr<Node<T>> head) {
  auto current = head;
  cout << endl << "[HEAD]";
  while (current) {
    std::cout << "->" << current->val;
    current = current->next;
  }
}

template <typename T>
shared_ptr<Node<T>> reverse_list(const shared_ptr<Node<T>>& head) {
  auto current = head;
  shared_ptr<Node<T>> prev = nullptr;
  while (current) {

    // change current->next so it points a previous element
    shared_ptr<Node<T>> before = current->next;
    current->next = prev;

    // Move ahead a step
    prev = current;
    current = before;
  }

  return prev;
}

void main()
{
  auto head = build_list<int>(10);
  display_list<int>(head);

  auto reverse = reverse_list<int>(head);
  display_list<int>(reverse);

  std::cout << std::endl << "[Press enter to exit]";
  std::cin.ignore();
}
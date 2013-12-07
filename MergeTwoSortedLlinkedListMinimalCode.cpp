// Write a function that merges two sorted linked lists together.
//
// O(n) time complexity and O(1) space complexity.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>;
#include <memory>;
#include <vector>;
#include <functional>;

using namespace std;

template <typename T>
struct Node {
  T data;
  shared_ptr<Node<T>> next;
};

template <typename T>
void append_node(shared_ptr<Node<T>>* head, shared_ptr<Node<T>>* tail, const shared_ptr<Node<T>>* new_element) {
  // If head exists append to tail else set as head.
  (*head) ? (*tail)->next = *new_element : *head = *new_element;
  // Reset tail to last node
  *tail = *new_element; 
}

template <typename T>
shared_ptr<Node<T>> merge(shared_ptr<Node<T>> list_a, shared_ptr<Node<T>> list_b) {
  shared_ptr<Node<T>> head = nullptr, tail = nullptr;
  
  // Append the smaller of the two elements.
  while (list_a && list_b) {
    auto new_element = (list_a->data < list_b->data) ? &list_a : &list_b;
    append_node(&head, &tail, new_element);
    *new_element = (*new_element)->next; // advance
  }

  // Append remaining nodes
  append_node(&head, &tail, list_a ? &list_a : &list_b);

  return head;
}

template <typename T>
const shared_ptr<Node<T>> to_linked_list(const vector<T>* vec)
{
  shared_ptr<Node<T>> head = nullptr, tail = nullptr;
  for (const auto &value: *vec) { // access by reference to avoid copying
    auto current = shared_ptr<Node<T>>(new Node<T>());
    current->data = value;
    current->next = nullptr; // current tail node always equal to nullptr.

    append_node(&head, &tail, &current);
  }
  return head;
}

template <typename T>
void display(const shared_ptr<Node<T>>* ptr) {
  cout << endl << "[HEAD]->";
  auto current = *ptr;
  while (current) {
    cout << current->data << "->";
    current = current->next; // Advance
  }
  cout << "[TAIL/NULL]" << endl;
}

void main() {
  auto a = new vector<int> { 1, 3, 5, 6, 8, 9, };
  cout << endl << "List A";
  auto list_a = to_linked_list(a);
  display(&list_a);

  auto b = new vector<int> { 0, 2, 4, 7 };
  cout << endl << "List B";
  auto list_b = to_linked_list(b);
  display(&list_b);

  cout << endl << "Merged List";
  auto sorted = merge(list_a, list_b);
  display(&sorted);

  cout << std::endl << "[Press enter to exit]" << std::endl;
  std::cin.ignore();
}
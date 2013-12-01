// Given a singularly linked list L and number k, write a function to remove the k-th
// last element from L.  Assume you cannot store the length of the list.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <memory>
#include <bitset>
#include <assert.h> 
#include "stdafx.h"

using namespace std;

struct Node
{
  shared_ptr<Node> next;
  int val;
};

shared_ptr<Node> build_linked_list(int size)
{
  assert(size > 0);
  
  // Create head
  shared_ptr<Node> head(new Node());
  head->val = 0;

  // Create rest of elements
  std::shared_ptr<Node> current(head);
  for (int i = 1; i <= size - 1; i++)
  {
    // Assign current nodes next element.
    current->next = std::shared_ptr<Node>(new Node());
    current->next->val = i;

    current = current->next; 
  }

  // Close off tail.
  current->next = NULL;

  return head;
}

void display_list(shared_ptr<Node> head)
{
  std::shared_ptr<Node> current(head);
  while (current)
  {
    std::cout << "->" << current->val;
    current = current->next;
  }
  std::cout << std::endl;
}

void remove_kth_last_element(shared_ptr<Node>* head, int k)
{
  assert(k > 0);

  if (*head == NULL)
    return;

  // Look ahead k elements.
  shared_ptr<Node> current = *head;
  shared_ptr<Node> look_ahead = *head;
  for (int i = 0; i <= k - 1; i++)
  {
    // If we can't reach k elements ahead then there is nothing to remove.
    if (look_ahead == NULL)
      return;

    look_ahead = look_ahead->next;
  }

  // Scan the list advancing all pointers one step until the lookup ahead pointer reaches the tail.
  shared_ptr<Node> previous;
  while (look_ahead != NULL) {
    look_ahead = look_ahead->next;
    previous = current;
    current = current->next;
  }
  std::cout << "Current: " << current->val << std::endl;

  // Remove current element
  if (previous != NULL) {
    previous->next = current->next;
    current->next = NULL;
  }
  else {
    // Special case: current element is the head of the list.
    shared_ptr<Node> temp = current->next;
    current->next = NULL;
    *head = temp;
  }
}

int _tmain()
{
  // Test by removing different elements from a linked list.
  for (int i = 1; i <= 10; i++)
  {
      std::cout << std::endl << "Removing " << i << "th last element." << std::endl;
      auto head = build_linked_list(10);
      display_list(head);
      remove_kth_last_element(&head, i);
      display_list(head);
  }

  return 0;
}
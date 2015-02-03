#include <exception>
#include "BinaryHeap.h"

// The Types_Min_Val is used as a sentinel value and is stored at the top of the heap.
// The sentinel value is a dummy piece of information that lets the algorithm avoid
// checking for the top of the list each loop iteration.
template <class Element_Type>
BinaryHeap<Element_Type>::BinaryHeap(unsigned int Initial_Size, const Element_Type Types_Min_Val)
{
  Size = 0;
  Max_Size = Initial_Size;

  Elements = new Element_Type [ Max_Size + 1]; // The number of elements + the sentinel value at the top
  if (Elements == NULL)
    throw "Unable to allocate";

  Elements[0] = Types_Min_Val; // Assign the sentinel value.
}

template <class Element_Type>
void BinaryHeap<Element_Type>::Make_Empty()
{
  Size = 0;
}

template <class Element_Type>
const bool BinaryHeap<Element_Type>::Is_Full()
{
  return (Size == Max_Size);
}

template <class Element_Type>
const bool BinaryHeap<Element_Type>::Is_Empty()
{
  return (Size == 0);
}

// Creates a hole in the next available location and percolates the 
// hole upwards until the current node's parent node is smaller
// than the node being inserted.
template <class Element_Type>
void BinaryHeap<Element_Type>::Insert(const Element_Type& X)
{
  unsigned int i;

  if (Is_Full())
  {
    throw std::exception( "Priority queue is full");
  }
  else
  {
    i = ++Size; // Create a hole in the next available location.

    // While the parent node is greater than the node being inserted.
    while (Elements[i / 2] > X )  // [i/2] points to the binary tree parent (h-1) node of [i].
    {
      Elements[i] = Elements[i / 2]; // Move the parent node down into the hole.
      i /= 2; // Set i to the parent node (h-1).
    }
    
    Elements[i] = X; // The parent node is less than the node being inserted so insert into this hole.
  }
}

// Removes the minimum element (always the root) which creates a hole.
// Percolate the hole downward until the last element can
// moved up a level.
template <class Element_Type>
Element_Type BinaryHeap<Element_Type> :: Delete_Min()
{
  unsigned int Child;
  Element_Type Min_Element, Last_Element;

  if (Is_Empty())
  {
    throw std::exception("Priority queue is empty");
    return Elements[0]; // Return sentinel value
  }

  Min_Element = Elements[1]; // The min element is the root.
  Last_Element = Elements[Size--]; // Get last value and then decrement the size.

  int i = 1; // Start at the hole in the root.

  while (i * 2 <= Size)
  {
    // Find smaller child element
    Child = i * 2; // i * 2 gives the first child node (h + 1)
    if (Child != Size) // Don't assume that there are two children.  Check that we are not at the bottom of the heap.
      if (Elements[Child + 1] < Elements[Child])
        Child++; // If second child is less than the first child move the pointer from the first child to the second.

    // If the last element in the heap is greater than the smallest child in the current branch & level.
    if (Last_Element > Elements[Child])
      Elements[i] = Elements[Child]; // Percolate the hole down one level into the child node.
    else
      break; // The last element is less than the current branch & level's child.

    i = Child; // Move down to next level's hole.
  }
  Elements[i] = Last_Element; // Move the final element

  return Min_Element;
}
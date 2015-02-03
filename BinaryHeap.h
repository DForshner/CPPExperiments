#pragma once

//
// Binary Heap
// An implementation of a priority queue.
//
// Properties:
//
// 1) Structure - A binary tree that is completely filled with the exception 
// of the last row which is filled from left to right.  The regular pattern allows
// the binary heap to be represented as an array.
//
// 2) Heap order - For every node, the key in the nodes parent is smaller than (or equal to)
// the current node's key.  The root is always the smallest element.
//
// Notes:
// - Given a height of h the binary tree has between 2^h and 2^(h+1) - 1 elements.
// - Given n elements the binary tree height is O(log n).

static const int Default_Max_Size = 10;

template <class Element_Type>
class BinaryHeap
{
private:
  unsigned int Max_Size; // Max number of elements
  unsigned int Size; // Current number of elements
  Element_Type *Elements; // The array of elements

public:
  // Constructor
  // Initial_Size = the number of elements in the heap, Types_Min_Val = The minimum value possible for the element type.
  BinaryHeap(unsigned int Initial_Size, const Element_Type Types_Min_Val); 
  
  ~BinaryHeap() { delete [] Elements; } // Destructor

  // Member Functions
  void Make_Empty();
  const bool Is_Empty();
  const bool Is_Full();
  
  void Insert(const Element_Type& X);
  Element_Type Delete_Min();

};

// explicit template instantiations
template class BinaryHeap<int>;
template class BinaryHeap<double>;
template class BinaryHeap<char>;
template class BinaryHeap<bool>;
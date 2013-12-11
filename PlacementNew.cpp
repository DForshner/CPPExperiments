// Placement new is an alternate syntax for the new operator that runs "in place" on previously allocated memory.
// This can be faster because there is no need to allocate memory only setting up the vtable and calling the constructor.
//
// A common use is for a slab allocator that starts with a single large 
// chunk of memory and uses placement new to allocate objects sequentially within the chunk.
// This avoids memory fragmentation and the overhead of heap traversal that malloc incurs.
//
// Possible uses: building a memory pool, a garbage collector, or when it's critical that the allocation not fail at
// a certain point in the program (by allocating the memory beforehand).
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
using namespace std;

struct Test {
  int data;
  Test() { cout << "Test::Test() called" << endl; }
  ~Test() { cout << "Test::~Test() called" << endl; }
};

int main()
{
  // Using malloc and using new
  cout << "Allocating memory" << endl;
  Test *pool1 = (Test *)malloc(sizeof(Test));
  char *pool2 = new char[sizeof(Test)];

  cout << "Calling placement new" << endl;
  Test *ptr1 = new (pool1) Test; // Create a pointer to Test stored in pool1
  Test *ptr2 = new (pool2) Test();    
  // Ordinary Heap Allocation: auto *q = new Test();     

  cout << "Storing data 11 and 22" << endl;
  ptr1->data = 11;
  ptr2->data = 22;

  cout << "Retrieved data " << ptr1->data << " and " << ptr2->data << endl;

  // Destructors must be called manually.
  cout << "Manually calling the destructor" << endl;
  ptr1->~Test();
  ptr2->~Test();

  // Only call delete[] on the original buffer.
  cout << "Releasing memory" << endl;
  free(pool1);
  delete[] pool2;

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
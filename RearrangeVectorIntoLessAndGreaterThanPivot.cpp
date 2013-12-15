// Take an array index that points to a pivot and rearrange the elements (in place) such 
// that elements are sorted by elements greater than, equal to, and less than the pivot.
//
// O(1) space complexity and O(n) time complexity.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template <typename T>
void sort(vector<T> * vec, const unsigned pivot_index) {
  assert(vec);
  assert(pivot_index >= 0);

  if (vec->empty() || pivot_index >= vec->size())
    return;

  auto pivot = vec->at(pivot_index);

  // Divide the array into 4 sections:
  // [0 <-> ( smaller - 1)] : smaller elements
  // [smaller <-> (equal - 1)] : equal elements
  // [equal <-> larger] : unclassified elements
  // [(larger + 1) - (size - 1)]: larger elements
  unsigned smaller = 0, equal = 0, larger = (vec->size() - 1);

  // While there are still unclassified elements.
  while (larger >= equal)
  {
    if (vec->at(equal) < pivot)
      swap(vec->at(equal++), vec->at(smaller++));
    else if (vec->at(equal) == pivot)
      ++equal;
    else
      swap(vec->at(equal), vec->at(larger--));
  }
}

template <typename T>
void display(const vector<T> & vec) {
  for (const auto &val : vec)
    cout << val << " ";
  cout << endl;
}

int main()
{
  auto vec = new vector<int> { 1, 3, 4, 5, 6, 7, 7, 8, 9, 2, 4, 5, 3, 7, 4, 4, 2 };
  cout << endl << "Pivot: " << vec->at(2) << endl;
  cout << endl << "Unsorted" << endl;
  display(*vec);

  cout << endl << "Sorted" << endl;
  sort(vec, 2);
  display(*vec);

  delete vec;

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}
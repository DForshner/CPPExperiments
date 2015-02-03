#include <vector>
#include "MedianOf3QuickSort.h"
#include "assert.h"

using namespace std;

// Note: this implementation doesn't use the insertion sort optimization.

void MedianOf3QuickSort::Sort(vector<int>& v)
{
  int first = 0;
  int last = static_cast<unsigned>(v.size()) - 1;

  Sort(v, first, last);
}

inline void MedianOf3QuickSort::Swap(vector<int>& v, const unsigned i, const unsigned j)
{
  int temp = v[j];
  v[j] = v[i];
  v[i] = temp;
}

int MedianOf3QuickSort::Median3(vector<int>& v, const unsigned first, const unsigned last)
{
  // Find the middle of the array
  unsigned middle = (first + last) / 2;

  // Order the values in the first, middle, last array position by size.
  if (v[first] > v[middle])
    Swap(v, first, middle);
  if (v[first] > v[last])
    Swap(v, first, last);
  if (v[middle] > v[last])
    Swap(v, middle, last);

  // Note: When sorting a partition with only two elements first will equal middle.
  assert(v[first] <= v[middle]);
  assert(v[first] <= v[last]);
  assert(v[middle] <= v[last]);

  // Hide the pivot in the second to last position
  Swap(v, middle, last - 1);
  return v[last - 1];
}

void MedianOf3QuickSort::Sort(vector<int>& v, const unsigned first, const unsigned last)
{
  // Check if the the bottom most recursive level has been reached (1 or 2 elements)
  if (first + 1 >= last)
  {
    if(v[last] < v[first]) // Will never be true if there is only one element.
      Swap(v, first, last);

    return;
  }

  int pivot = Median3(v, first, last);
  int i = first;
  int j = last - 1;
 
  // The Median3 method should hide the pivot at position last - 1
  assert(v[last - 1] == pivot);

  while(true)
  {
    // Search first to last stopping at value greater than pivot
    while (v[++i] < pivot);
    // Search last to first stopping at value less than pivot
    while (v[--j] > pivot);

    // If the i search crosses the j search break;
    if (i < j)
      Swap(v, i, j);
    else
      break;
  }

  // Restore the pivot
  Swap(v, i, (last -1));

  // Recursively sort the  less than pivot partition.
  Sort(v, first, i - 1);
  
  // Recursively sort the greater than pivot partition.
  Sort(v, i + 1, last);
}
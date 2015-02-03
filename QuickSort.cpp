#include <vector>
#include "QuickSort.h"

using namespace std;

// Problem: This particular implementation doesn't have a good partitioning scheme.  See header for details.

bool QuickSort::Sort(vector<int>& v)
{
  // Exit of less than 2 elements
  if (v.size() < 2)
    return false;

  unsigned first = 0;
  unsigned last = static_cast<unsigned>(v.size()) - 1;

  return QSort(v, first, last);
}

bool QuickSort::QSort(vector<int>& v, unsigned first, unsigned last)
{
  unsigned i, j;
  int swap, median;

  i = first;
  j = last;

  // get median element
  median = v[(first + last) / 2];

  // Inner loop - Scans for elements that are out of place with respect to the median (pivot) element and swaps them.
  do {

    // scan from the first towards the last until we find a value that is greater than the median.
    while (v[i++] < median);
    
    // The test occurred at i but then incremented to i + 1.  Decrement i once so it's back to i for the comparison.
    i--; 

    // scan form the last towards the first until we find a value that is less than the median.
    while (median < v[j--]);
    
    // The test occurred at j but then decremented to j - 1.  Increment j once so it's back to  for the comparison.
    j++;

    // Comparison - If the value greater than the median (i) is located to the 
    // left of the value that is less than the median (j) then they are out of order
    // and need to be swapped.
    if (i <= j) {
      swap = v[i];
      v[i++] = v[j];
      v[j--] = swap;
    }

    // Continue scanning from where we left off until the i scan towards last element crosses the 
    // j scan towards the first element.
  } while (i <= j && j != UINT_MAX);

  // the i scan has now crossed the j scan.

  // Recursively sort left side.
  if (first < j && j != UINT_MAX)
    QSort(v, first, j);

    // Recursively sort right side.
  if (i < last)
    QSort(v, i, last);

  // This section of the array is now sorted
  return true;
}
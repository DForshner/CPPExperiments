#include <vector>
#include "CombSort.h"

using namespace std;

bool CombSort::Sort(vector<int>& v)
{
  unsigned i, j, offset;
  int swap;
  bool isSorted;

  // Exit of less than 2 elements
  if (v.size() < 2)
    return false;

  // The initial offset is the number of sorted array elements.
  offset = v.size();

  // Outer loop - decreases the offset each time until the offset is 1 and no exchanges occurred.
  // Note: the pass where the offset is 1 can run multiple times to allow the sorting of nearby neighbours.
  do {

    // Update offset
    offset = (offset * 8) / 11;
    
    // Do not let the offset become less than 1.
    offset = (offset == 0) ? 1 : offset;

    // Assume the array is sorted until an exchange occurs.
    isSorted = true;

    // Inner loop - compare and swap elements that are offset elements apart.
    for (i = 0; i <= (v.size() - 1 - offset); i++ ) {
      j = i + offset;

      // Compare elements at i and j
      if (v[i] > v[j]) {

        // indicate that the current offset produced a swap
        isSorted = false;

        // swap elements
        swap = v[i];
        v[i] = v[j];
        v[j] = swap;
     }
    }

  } while (!(isSorted && offset == 1));
  return isSorted; 
}
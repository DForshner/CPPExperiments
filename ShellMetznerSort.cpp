#include <vector>
#include "ShellMetznerSort.h"

using namespace std;

bool ShellMetznerSort::Sort(vector<int>& v)
{
  unsigned i, j, offset;
  int swap;
  bool isSorted;

  // Exit of less than 2 elements
  if (v.size() < 2)
    return false;

  offset = v.size();

  // Outer loop - Keeps decreasing the offset amount each pass until the last pass that ran was offset = 1 (no offset).
  while (offset > 1) {

    // Update the comparison offset using the Knuth sequence is considered better for small arrays.
    offset = (offset - 1) / 3;
    // Alternative: offset = (offset  1) / 2; // Faster for large arrays (+500 elements).

    // Prevent offset from going below 1.  
    // When integers are divided, the result of the / operator is 
    // the algebraic quotient with any fractional part discarded.
    // Example: offset = (3 - 1) / 3 = 0.66 => returns 0
    offset = (offset == 0) ? 1 : offset;

    // Middle loop - Continues to sort until there is a pass where no swaps occur.
    do {
      isSorted = true;

      // Inner loop - Compares and swaps elements that are offset elements apart each pass.
      for (i = 0; i <= (v.size() - 1 - offset); i++) {
        j = i + offset;

        // Check if swap i and j
        if (v[i] > v[j]) {

          // Indicate that a swap occurred during this pass.
          isSorted = false;

          // Swap the elements that are offset apart.
          swap = v[i];
          v[i] = v[j];
          v[j] = swap;
        }
      }

      // If the last pass of the inner loop didn't find any elements to re-order
      // then trigger the middle loop to exit so the offset can be decreased.
    } while (!isSorted);
  }

  return isSorted; 
}
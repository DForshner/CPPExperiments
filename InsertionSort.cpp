#pragma once

#include <vector>
#include "InsertionSort.h"

void InsertionSort::Sort(vector<int>& v)
{
  // (N - 1) passes from second position to the end of the array.
  for (unsigned i = 1; i <= (v.size() - 1); ++i)
  {
    // Remove the current pass starting value from the array.
    // This creates the empty space that the elements will be
    // shuffled into.
    int temp = v[i];

    unsigned j;

    // Walk backwards from the empty space and move larger
    // objects upwards until either the end of the array 
    // or a smaller element is encountered.
    for (j = i; j > 0 ; --j) {

      if (temp > v[j - 1])
        break;

      // The elements from 0 to i - 1 have already been sorted so
      // its safe to shuffle them down one position.
      v[j] = v[j-1];
    }

    // Fill the empty space with the current pass value.
    v[j] = temp;
  }
}
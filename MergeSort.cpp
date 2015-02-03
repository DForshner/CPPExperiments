#include <vector>
#include "MergeSort.h"

void MergeSort::Sort(int a[], const unsigned size)
{
  int* temp = new int[size];
  
  Sort(a, temp, 0, size - 1);
  
  delete [] temp;
}

void MergeSort::Sort(int a[], int temp[], const unsigned first, const unsigned last)
{
  if (first < last)
  {
    unsigned middle = (first + last) / 2;

    // Recursively sort the lower half of the array
    Sort(a, temp, first, middle);

    // Recursively sort the upper half of the array
    Sort(a, temp, middle + 1, last);

    // Merge lower and upper sections together.
    Merge(a, temp, first, middle + 1, last);
  }
}

void MergeSort::Merge(int a[], int temp[], unsigned lower_pos, unsigned upper_pos, unsigned upper_end_pos)
{
  unsigned lower_end_pos = upper_pos - 1;
  unsigned temp_pos = lower_pos;
  unsigned number_elements = upper_end_pos - lower_pos + 1;
  
  // Compare elements between the upper and lower sections one at a time.
  // In each comparison take the lower lower valued one and store it in the temp array.
  while (lower_pos <= lower_end_pos && upper_pos <= upper_end_pos)
    if (a[lower_pos] <= a[upper_pos])
      temp[temp_pos++] = a[lower_pos++];
    else
      temp[temp_pos++] = a[upper_pos++];

  // At this point all the the elements have been merged from one of the sections.

  // Append any leftover elements from the lower section
  while (lower_pos <= lower_end_pos)
    temp[temp_pos++] = a[lower_pos++];

  // Append any leftover elements from the the upper section
  while (upper_pos <= upper_end_pos)
    temp[temp_pos++] = a[upper_pos++];

  // Copy the temp array into the original array
  // Copies from back to front upper_end_pos can be re-used.
  for (int i = 1; i <= number_elements; i++, upper_end_pos--)
    a[upper_end_pos] = temp[upper_end_pos];
}
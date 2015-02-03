#pragma once

#include <vector>

using namespace std;

// Merge Sort
//
// Notes: 
// - O(n log(n)) running time but can be O(n) if list is already sorted.
// - Requires linear extra memory to store temporary data.
// - Often used for external (hd, tape,ect.) sorts.

class MergeSort
{
public:
  void Sort(int a[], unsigned size);
private:
  void Sort(int a[], int temp[], const unsigned first, const unsigned last);
  void Merge(int a[], int temp[], unsigned lower_pos, unsigned upper_pos, unsigned upper_end_pos);
};
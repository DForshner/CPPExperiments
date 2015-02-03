#pragma once

#include <vector>

using namespace std;

// Median of 3 quick sort 
// A recursive in-place exchange type sort.  This version of quick sort uses a median of 3 partitioning 
// scheme at each recursion level to try and create even sized partitions.  This will prevent the the
// situation where a sorted input results in the majority of the elements ending up in one partition.
//
// Notes: In many implementations quick sort is only performed until the partition reaches a cut-off (~20)
// size and then an insertion sort is performed over the entire array for the remaining unordered elements.

class MedianOf3QuickSort
{
public:
  void Sort(vector<int>& v);
private:
  inline void Swap(vector<int>& v, const unsigned i, const unsigned j);
  int Median3(vector<int>& v, const unsigned first, const unsigned last);
  void Sort(vector<int>& v, const unsigned first, const unsigned last);
};
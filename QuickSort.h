#pragma once

#include <vector>

using namespace std;

// QuickSort method
// A recursive in-place exchange type sort.
//
// Notes:
// Optimal case of O(n log(2)) with a worst case (ordered data) of O(n^2).
//
// Problems:
// This particular implementation doesn't use the median of three partitioning scheme that most modern
// implementations of quick sort appear to use.
//
// This means there is a possibility of choosing an initial median element that is equal to the largest or smallest value
// in the array.  If this happens then as we compare all of the elements to the median element we will
// end up dumping all the elements into one of the two sub arrays that will be processed recursively.
// If this same scenario takes place at each recursion level the running time of the algorithm will approach O(n^2).

class QuickSort
{
public:  
  bool Sort(vector<int>& v);
private:
  bool QSort(vector<int>& v, unsigned first, unsigned last);
};
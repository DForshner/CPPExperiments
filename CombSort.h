#pragma once

#include <vector>

using namespace std;

// CombSort method
// An in-place exchange type sort developed by Richard Box and Stephen Lacey.
// A modification of either the dreaded bubble sort or the Shell - Metzner sort.  Uses single path
// pass cycles for re-ordering distant neighbours and multiple passes for re-ordering nearby neighbours.
//
// Notes:
// 1) Claimed to be O(n log(n)).  The authors tests showed it is 50x bubble sort, equal to heap sort, and 1/2 the speed of qsort.
// 2) In some ways very similar to the Shell - Metzner sort but it does a single pass at each offset (except for offset = 1).

class CombSort
{
public:  
  bool Sort(vector<int>& v);
};
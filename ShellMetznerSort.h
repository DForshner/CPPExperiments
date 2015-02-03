#pragma once

#include <vector>

using namespace std;

// Shell - Metzner sorting method
// An in-place exchange type sort.  Sorts an array by using cycles of re-ordering elements
// at different offset distances from each other.  Each cycle consists of multiple passes
// (using same offset) that ensure the order of the (initially) distance elements.
//
// Notes:
// 1) O(n log(n))

class ShellMetznerSort
{
public:  
  bool Sort(vector<int>& v);
};
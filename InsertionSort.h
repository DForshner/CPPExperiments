#pragma once

// Insertion Sort
// 
// Notes:
// - O(N^2) Complexity
// - Often the preferred algorithm with the sequences to be sorted are small (<20 elements).

#include<vector>

using namespace std;

class InsertionSort
{
public:
  void Sort(vector<int>& v);
};
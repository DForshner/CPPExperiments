// A naive quick sort implementation. 
//
// It doesn't use randomized pivot so it's vulnerable to
// a pathological dataset were the data is already sorted.
//
// Average Time Complexity: O(nlog(n))
// Worst Case (Pathological dataset) Time Complexity: O(n^2)
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NaiveQuickSort {

  template<typename T>
  void swap(T& x, T& y) {
    T temp = x;
    x = y;
    y = temp;
  }

  int partition(vector<int>& v, int left, int right) {
    auto pivot = v[right];
    auto i = (left - 1);

    // Working our way to the right place elements less than the 
    // pivot to the left i so that when j reaches right - 1 the
    // pivot can be placed in its final location at i + 1
    for (auto j = left; j <= right - 1; j++) {
      if (v[j] <= pivot) { // Less than pivot so swap
        i++;
        swap(v[i], v[j]);
      }
    }

    // Place pivot in final location
    swap(v[i + 1], v[right]);
    return (i + 1);
  }

  void qsort(vector<int>& v, int left, int right) {
    if (left < right) {
      auto partitionIndex = partition(v, left, right);
      // the element at partitionIndex is at it's final location so
      // we recursively sort the elements to the left and right of it.
      qsort(v, left, partitionIndex - 1);
      qsort(v, partitionIndex + 1, right);
    }
  }

  void qsort(vector<int>& v) {
    qsort(v, 0, v.size() - 1);
  }

  TEST_CLASS(NaiveQuickSortTests) {
    public:
      TEST_METHOD(WhenNoElements_ExpectNoElements) {
        vector<int> value;
        qsort(value);
        Assert::AreEqual(size_t(0), value.size());
      }

      TEST_METHOD(WhenOneElement_ExpectOneElement) {
        vector<int> value{ 1 };
        qsort(value);
        Assert::AreEqual(1, value[0]);
      }

      TEST_METHOD(WhenSorted_ExpectSorted) {
        vector<int> value{ 1, 2, 3, 4, 5 };
        qsort(value);
        Assert::IsTrue(is_sorted(value.cbegin(), value.cend()));
      }

      TEST_METHOD(WhenUnsortedSorted_ExpectSorted) {
        vector<int> value{ 5, 4, 3, 2, 1 };
        qsort(value);
        Assert::IsTrue(is_sorted(value.cbegin(), value.cend()));
      }
  };

  // Console Test Code
  //void displayVector(const vector<int>& v) {
  //  cout << "[ ";
  //  for (const auto& i : v) { cout << i << " "; }
  //  cout << "]" << endl;
  //}

  // Console Test Code
  //void displayQuickSort(vector<int> v) {
  //  displayVector(v);
  //  qsort(v);
  //  displayVector(v);
  //}
}
  
// Console Test Code
//int main() {
//  NaiveQuickSort::displayQuickSort({ 4, 6, 1, 3, 2, 5 });
//  NaiveQuickSort::displayQuickSort({ 10, 8, 4, 6, 1, 3, 7, 2, 9, 5 });
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
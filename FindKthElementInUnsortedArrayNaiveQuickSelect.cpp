// Given an unsorted array of distinct values find the element.
//
// Quick select is similar to quick sort.  At the end of each partition step 
// in quick sort the pivot is at its' final location.  In quick select we 
// perform partition and stop at the point where the pivot is the Kth element.
//
// Average Time Complexity: O(n)
// Worst Case Time Complexity: O(n^2)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindKthElementInUnsortedArrayNaiveQuickSelect {

  // I'm including this for comparison only.  This is another version of partition
  // that takes the left element and works inwards from left and right sides.  
  // It's easier to understand than pivotRight but requires more code.
  int partitionLeft(vector<int>& values, int low, int high) {
    auto left = low + 1;
    auto right = high;

    // Take leftmost element as pivot
    auto pivot = values[low];

    // Partition values to one side or other of pivot
    while (left < right) {

      // Find value greater than pivot on left side
      while (left <= right && values[left] < pivot) { left++; }

      // Find value less than pivot on right side
      while (left <= right && values[right] > pivot) { right--; }

      if (left < right) {
        swap(values[left], values[right]);
      }
    }

    // All values from low to right should be less than pivot
    // and all values from left to high should be greater than pivot.
    swap(values[low], values[right]);

    // Pivot is now in final location.
    return right;
  }

  // This is a simpler version of the partition function that works
  // from left to right.
  int partitionRight(vector<int>& values, int low, int high) {
    auto pivot = values[high];

    // Work our way from left to right keeping values less than 
    // the pivot on the right side of the partition;
    auto partition = low;
    for (auto current = low; current <= high - 1; current++) {
      // If the current value is less than the pivot store it on the left side of the partition.
      if (values[current] <= pivot) {
        swap(values[partition], values[current]);
        partition++;
      }
    }

    // partition should point to the first value that is greater than the pivot.
    swap(values[partition], values[high]);

    return partition;
  }

  int findKthElement(vector<int>& values, int k) {
    if (k <= 0 || k > values.size()) {
      return numeric_limits<int>::min();
    }

    int low = 0;
    int high = values.size() - 1;

    while (low <= high) {
      auto p = partitionRight(values, low, high);
      if (p == k - 1) {
        return values[p];
      } else if (p < k - 1) { // k must be located between pivot and high.
        low = p + 1;
      } else { // p > k - 1: k must be located between low and the pivot.
        high = p - 1;
      }
    }

    // We couldn't find the Kth element
    return numeric_limits<int>::min();
  }

  TEST_CLASS(FindKthElementInUnsortedArrayNaiveQuickSelectTests) {
    public:
      TEST_METHOD(WhenZeroIthElement_ExpectIntMin) {
        vector<int> values{ 4, 3, 2, 1 };
        auto kth = findKthElement(values, 0);
        Assert::AreEqual(numeric_limits<int>::min(), kth);
      }

      TEST_METHOD(WhenKthElementLargerThanArray_ExpectIntMin) {
        vector<int> values{ 4, 3, 2, 1 };
        auto kth = findKthElement(values, 5);
        Assert::AreEqual(numeric_limits<int>::min(), kth);
      }

      TEST_METHOD(WhenReverseSorted_ExpectKthReturned) {
        vector<int> values{ 4, 3, 2, 1 };
        auto kth = findKthElement(values, 3);
        Assert::AreEqual(3, kth);
      }

      TEST_METHOD(WhenUnsorted_ExpectKthReturned) {
        vector<int> values{ 8, 2, 3, 4, 6, 5};
        auto kth = findKthElement(values, 5);
        Assert::AreEqual(6, kth);
      }
  };
}
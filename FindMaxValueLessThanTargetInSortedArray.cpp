// Given a sorted array find the maximum number under some
// target number.
// 
// Time Complexity: O(log(n))
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindMaxValueLessThanTargetInSortedArray {

  // Use binary search to find maximum number that is less than the target.
  int getMaxLessThanTarget(vector<int> arr, int target) {
    if (arr.size() == 0) { return numeric_limits<int>::min(); }

    int left{ 0 };
    int right = arr.size() - 1;
    int mid = (left + right) / 2;

    while (mid != left) {
      mid = (left + right) / 2;
      if (arr[mid] <= target) {
        left = mid;
      } else {
        right = mid;
      }
    }

    // We are down to one or two elements so pick the rightmost of the two
    // that are less than the target
    if (arr[right] < target) {
      return arr[right];
    } else if (arr[left] < target) {
      return arr[left];
    } else {
      return numeric_limits<int>::min();
    }
  }

  TEST_CLASS(FindMaxValueLessThanTargetInSortedArrayTests) {
  public:
    TEST_METHOD(WhenNoNumbers_ExpectIntMin) {
      auto result = getMaxLessThanTarget({}, 8);
      Assert::AreEqual(numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenNoNumbersLessThanTarget_ExpectIntMin) {
      auto result = getMaxLessThanTarget({ 5, 6, 7, 9, 10, 12 }, 3);
      Assert::AreEqual(numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenOnlyTargetNumberInArray_ExpectIntMin) {
      auto result = getMaxLessThanTarget({ 7, 7, 7, 7, 7, 7, 7 }, 7);
      Assert::AreEqual(numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenOneElementAndLessThanDoesNotExist_ExpectIntMin) {
      auto result = getMaxLessThanTarget({ 3 }, 2);
      Assert::AreEqual(numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenOneElementAndLessThanExists_ExpectLessThanReturned) {
      auto result = getMaxLessThanTarget({ 1 }, 2);
      Assert::AreEqual(1, result);
    }

    TEST_METHOD(WhenTwoElementsAndLessThanDoesNotExist_ExpectIntMin) {
      auto result = getMaxLessThanTarget({ 3, 4 }, 2);
      Assert::AreEqual(numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenTwoElementsAndLessThanExists_ExpectLessThanReturned) {
      auto result = getMaxLessThanTarget({ 1, 2 }, 2);
      Assert::AreEqual(1, result);
    }

    TEST_METHOD(WhenTargetExistsInArray_ExpectNumberToLeftOfTargetReturned) {
      auto result = getMaxLessThanTarget({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }, 8);
      Assert::AreEqual(7, result);
    }
  };
}
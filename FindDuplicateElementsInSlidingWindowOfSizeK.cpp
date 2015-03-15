// Given an unsorted array find all of the duplicate elements
// that occur inside a given window size.
//
// Time Complexity: O(N)
// Space Complexity: O(K) where k is the window size.
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <set>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindDuplicateElementsInSlidingWindowOfSizeK {

  // O(N^2) brute force approach that compares all possible pairs
  // of elements.
  vector<int> findDuplicatesBruteForce(const vector<int>& arr, size_t windowSize) {
    vector<int> duplicates;

    for (size_t i = 0; i < arr.size(); i++) {
      for (size_t j = i + 1; j < arr.size(); j++) {
        // If matching value and index difference equals distance.
        if ((arr[i] == arr[j]) && (j - i - 1 <= windowSize)) {
          duplicates.emplace_back(arr[i]);
        }
      }
    }

    return duplicates;
  }

  // O(N) version that uses a hash set to hold the current values that are inside the window.
  vector<int> findDuplicates(const vector<int>& arr, size_t windowSize) {
    set<int> valuesInWindow;
    vector<int> duplicates;

    for (size_t i = 0; i < arr.size(); i++) {
      // Remove the value that just moved outside the window
      if (i >= windowSize) {
        valuesInWindow.erase(arr[i - windowSize]);
      }

      // If this value has already been seen inside the 
      // window we have found a duplicate.
      if (valuesInWindow.find(arr[i]) != valuesInWindow.cend()) {
        duplicates.emplace_back(arr[i]);
      }

      // Add this value to the window's set of values.
      valuesInWindow.emplace(arr[i]);
    }

    return duplicates;
  }

  TEST_CLASS(FindDuplicateElementsInSlidingWindowOfSizeKTests) {
    public:
      TEST_METHOD(BruteForce_WhenTwoDuplicatesTwoElementsApart_ExpectBothReturned) {
        vector<int> values{ 1, 2, 4, 2, 3, 3, 1, 4 };
        auto results = findDuplicatesBruteForce(values, 3);
        Assert::AreEqual(2, results[0]);
        Assert::AreEqual(3, results[1]);
      }

      TEST_METHOD(WhenNoDuplicates_ExpectNoDuplicates) {
        vector<int> values{ 1, 2, 3, 4, 5, 6, 7 };
        auto results = findDuplicates(values, 3);
        Assert::IsTrue(results.empty());
      }

      TEST_METHOD(WhenTwoDuplicatesWindowSizeApart_ExpectBothReturned) {
        vector<int> values{ 1, 2, 4, 2, 3, 3, 1, 4 };
        auto results = findDuplicates(values, 3);
        Assert::AreEqual(2, results[0]);
        Assert::AreEqual(3, results[1]);
      }

      TEST_METHOD(WhenDuplicatesGreaterThanWindowSizeApart_ExpectNoDuplicates) {
        vector<int> values{ 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7 };
        auto results = findDuplicates(values, 6);
        Assert::IsTrue(results.empty());
      }
  };
}
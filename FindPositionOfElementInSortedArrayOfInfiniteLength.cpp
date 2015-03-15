// Given an infinite array of sorted integers find the position
// of a given search key.
//
// Time Complexity: O(log(key))
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindPositionOfElementInSortedArrayOfInfiniteLength {

  // Pretend arr[] is infinite.
  // O(log(key)) calls to find key in search range.
  int binarySearch(int arr[], int low, int high, int key) {
    if (low > high) {
      // We didn't find the key we were searching for. 
      return numeric_limits<int>::min();
    }

    auto mid = (low + high) / 2;
    if (arr[mid] == key) {
      return mid;
    } else if (arr[mid] < key) {
      return binarySearch(arr, low, mid - 1, key);
    } 
    
    // arr[mid] > key
    return binarySearch(arr, low, mid - 1, key);
  }

  // Pretend arr[] is infinite.
  int findPosition(int arr[], int key) {
    int low{ 0 };
    int high{ 1 };
    int value = arr[high];

    // Search for range that contains the key doubling the 
    // size of the search range each pass.  
    // O(log(key)) passes to find range with key.
    while (value < key) {
      low = high;
      high = 2 * high;
      value = arr[high];
    }

    // The key should lie between the low and high ranges now.
    return binarySearch(arr, low, high, key);
  }

  TEST_CLASS(FindPositionOfElementInSortedArrayOfInfiniteLengthTests) {
    public:
      TEST_METHOD(WhenKeyNotInArray_ExpectNegativePosition) {
        int arr[] { 1, 2, 3, 4, 5, 6, 8, 10, 11, 12, 13, 14, 15, 16, 17 };
        auto position = findPosition(arr, 7);
        Assert::AreEqual(numeric_limits<int>::min(), position);
      }

      TEST_METHOD(WhenKeyInArray_ExpectKeysPositionReturned) {
        int arr[] { 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17 };
        auto position = findPosition(arr, 7);
        Assert::AreEqual(6, position);
      }
  };
}
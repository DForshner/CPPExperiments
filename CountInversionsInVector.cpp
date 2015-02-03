// Count the inversions in an array.
//
// Contains both a O(n^2) brute force and O(nlog(n)) divide and conquer algorithm.
//
// Inversion counts can be used to give you an idea of how far 
// an array is from being in sorted order.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CountInversionsInVector {

  // Brute Force - For each item count how many items to 
  // the right have values less than the current item;
  // Time complexity: O(n^2)
  int const bruteForce(const vector<int>& arr) {
    auto count = 0;
    for (auto i = 0; i < arr.size(); i++) {
      for (auto j = i + 1; j < arr.size(); j++) {
        if (arr[i] > arr[j]) {
          count++;
        }
      }
    }

    return count;
  }

  // Merge the two arrays together and return the inversion count
  int merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    auto i = left;
    auto j = mid + 1;
    auto k = left;
    auto count = 0;

    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j]) {
        temp[k++] = arr[i++];
      } else {
        temp[k++] = arr[j++];
        // Because the items to the right of i are sorted 
        // (arr[i], arr[i+1], arr[i+2] … arr[mid]) will be 
        // greater than arr[j]
        count = count + (mid + 1 - i);
      }
    }

    // Copy remaining elements of left sub-array.
    while (i <= mid) {
      temp[k++] = arr[i++];
    }

    // Copy remaining elements of right sub-array.
    while (j <= right) {
      temp[k++] = arr[j++];
    }

    // Copy back merged elements
    for (auto m = left; m <= right; m++) {
      arr[m] = temp[m];
    }

    return count;
  }

  int mergeCountInversions(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) {
      return 0;
    }

    auto mid = (left + right) / 2;

    // Sum the inversions of the left and right parts
    auto count = mergeCountInversions(arr, temp, left, mid);
    count += mergeCountInversions(arr, temp, mid + 1, right);

    // Merge the two parts together
    count += merge(arr, temp, left, mid, right);

    return count;
  }

  // Divide and conquer
  // Time Complexity: O(nlog(n))
  int mergeCountInversions(vector<int>&& arr) {
    vector<int> temp(arr);
    return mergeCountInversions(arr, temp, 0, arr.size() - 1);
  }

  TEST_CLASS(DisjointSetsTests) {
    public:
      TEST_METHOD(WhenDisjoint_ExpectTrue) {
        Assert::AreEqual(1, mergeCountInversions({ 2, 1 }));
      }

      TEST_METHOD(WhenNotDisjoint_ExpectFalse) {
        Assert::AreEqual(0, mergeCountInversions({ 1, 2 }));
      }
  };

  //// Console Test Code
  //void const displayVector(const vector<int>& arr) {
  //  cout << "[ ";
  //  for (auto const &item : arr) {
  //    cout << item << " ";
  //  }
  //  cout << "]" << endl;
  //}

  //// Console Test Code
  //void const displayInversionCount(vector<int> v) {
  //  displayVector(v);
  //  cout << "Brute Force: " << bruteForce(v) << endl;
  //  cout << "Merge Count: " << mergeCountInversions(v) << endl << endl;
  //}
}
  
// Console Test Code
//int main()
//{
//  CountInversionsInVector::displayInversionCount({ 2, 1 });
//  CountInversionsInVector::displayInversionCount({ 1, 2, 3, 4 });
//  CountInversionsInVector::displayInversionCount({ 4, 3, 2, 1 });
//  CountInversionsInVector::displayInversionCount({ 2, 4, 1, 3, 5 });
//
//  cout << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
// Given an array that contains even and odd numbers
// sort the elements so that even numbers are on the 
// left and odd numbers are on the right of the array.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SegregateEvenAndOddNumbersInAnArray {

  template<typename T>
  void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
  }

  void sort(vector<int>& v) {
    auto left = 0;
    auto right = v.size() - 1;

    // Move the left and right pointers towards the middle 
    // and swap odd/even elements we go.
    while (left < right) {

      // Move left pointer towards the middle until we find an even number.
      while (left < right) {
        if (v[left] % 2 == 0) {
          left++;
        } else { // Found a odd number we want to swap
          break;
        }
      }

      // Move right pointer towards the middle until we find an odd number.
      while (left < right) {
        if (v[right] % 2 == 1) {
          right--;
        } else { // Found a even number we want to swap.
          break;
        }
      }

      // Swap the left (odd) element with the right (even) element;
      if (left < right) {
        swap(v[left], v[right]);
      }
    }
  }

  TEST_CLASS(SegregateEvenAndOddNumbersInAnArrayTests) {
    public:
    TEST_METHOD(WhenElements_ExpectFirstHalfEvenLastHalfOdd) {
      vector<int> results{ 1, 2, 3, 4, 5, 6 };
      sort(results);
      Assert::IsTrue(results[0] % 2 == 0);
      Assert::IsTrue(results[1] % 2 == 0);
      Assert::IsTrue(results[2] % 2 == 0);
      Assert::IsTrue(results[3] % 2 == 1);
      Assert::IsTrue(results[4] % 2 == 1);
      Assert::IsTrue(results[5] % 2 == 1);
    }
  };

  //// Console Test Code
  //void displayVector(const vector<int>& v) {
  //  cout << "[ ";
  //  for (const auto& item : v) {
  //    cout << item << " ";
  //  }
  //  cout << "]" << endl;
  //}

  //// Console Test Code
  //void displaySort(vector<int> v) {
  //  displayVector(v);
  //  sort(v);
  //  displayVector(v);
  //}
}

// Console Test Code
//int main() {
//  SegregateEvenAndOddNumbersInAnArray::displaySort({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
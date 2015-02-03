// Find the pair of numbers between two sorted arrays
// whose sum is closest to a target number.
//
// O(n) Time Complexity, O(1) Space Complexity
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <limits>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindPairSumClosestToTargetInTwoSortedArrays {

  // Brute force exhaustive search of all pairs. 
  // Space Complexity: O(n^2), Time Complexity: O(1) 
  pair<int, int> bruteForce(const vector<int>& v1, const vector<int>& v2, int x) {
    int minDiff{ numeric_limits<int>::max() };
    pair<int, int> pair;

    for (auto i = 0; i < v1.size(); i++) {
      for (auto j = 0; j < v2.size(); j++) {
        if (abs(v1[i] + v2[j] - x) < minDiff) {
          minDiff = abs(v1[i] + v2[j] - x);
          pair = make_pair(v1[i], v2[j]);
        }
      }
    }

    return pair;
  }

  // Work left to right in v1 and right to left in v2 working towards
  // the pair of elements whose sum is closest to x.
  // O(n) Time Complexity, O(1) Space Complexity
  pair<int, int> scanForClosest(vector<int>&& v1, vector<int>&& v2, int x) {
    int minDiff{ numeric_limits<int>::max() };
    pair<int, int> pair;

    int left{ 0 };
    int right = v2.size() - 1;
    while (left < v1.size() && right >= 0) {

      // Check if current pair's sum is closer to the target
      // then any pairs we have seen so far.
      if (abs(v1[left] +  v2[right] - x) < minDiff) {
        minDiff = abs(v1[left] + v2[right] - x);
        pair = make_pair(v1[left], v2[right]);
      }

      if (v1[left] + v2[right] > x) {
        // The sum is greater so try and decrease it by decreasing the right element.
        right--;
      } else {
        // The sum is less so try and increase it by increasing the left element.
        left++;
      }
    }

    return pair;
  }

  TEST_CLASS(FindPairSumClosestToTargetInTwoSortedArraysTests) {
    public:
      TEST_METHOD(WhenPairWithNegatives_ExpectClosestSumChosen) {
        auto result = scanForClosest({ -100, 5, 100 }, { -200, 10, 200 }, 20);
        Assert::AreEqual(5, result.first);
        Assert::AreEqual(10, result.second);
      }

      TEST_METHOD(WhenPair_ExpectClosestSumChosen) {
        auto result = scanForClosest({ 1, 2, 10, 20, 100, 200 }, { 50, 51, 52, 120, 130, 140, 250 }, 100);
        Assert::AreEqual(1, result.first);
        Assert::AreEqual(120, result.second);
      }
  };

  // Console Test Code
  //void displayVector(const vector<int>& v) {
  //  cout << "[ ";
  //  for (auto const &item : v) {
  //    cout << item << " ";
  //  }
  //  cout << "]" << endl;
  //}

  // Console Test Code
  //void displayClosestPairs(vector<int> v1, vector<int> v2, int x) {
  //  displayVector(v1);
  //  displayVector(v2);

  //  auto bruteForceResult = bruteForce(v1, v2, x);
  //  cout << "Brute Force : [ " << bruteForceResult.first << " " << bruteForceResult.second << " ]" << endl;

  //  auto scanForClosestResult = scanForClosest(v1, v2, x);
  //  cout << "Sort and Scan: [ " << scanForClosestResult.first << " " << scanForClosestResult.second << " ]" << endl;

  //  cout << endl;
  //}
}

// Console Test Code
//int main() {
//  FindPairSumClosestToTargetInTwoSortedArrays::displayClosestPairs({ -100, 5, 100 }, { -200, 10, 200 }, 20);
//  FindPairSumClosestToTargetInTwoSortedArrays::displayClosestPairs({ 1, 2, 10, 20, 100, 200 }, { 50, 51, 52, 120, 130, 140, 250 }, 100);
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
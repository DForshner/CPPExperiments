// Given a sorted array find the pair of elements
// in the array whose sum is closest to a target number.
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

namespace FindPairClosestToTargetNumberInSortedArray {

  // O(n^2) Brute force compare all possible pairs until pair with sum nearest to target is found.
  pair<int, int> bruteForce(const vector<int>& v, int target) {
    int minDiff{ numeric_limits<int>::max() };
    pair<int, int> pair;

    for (auto i = 0; i < v.size(); i++) {
      for (auto j = i + 1; j < v.size(); j++) {
        if (abs(v[i] + v[j] - target) < minDiff) {
          minDiff = abs(v[i] + v[j] - target);
          pair = make_pair(v[i], v[j]);
        }
      }
    }

    return pair;
  }

  // O(n) Linear method to find pairs whose sum is closest to target number
  pair<int, int> findPairSumClosestToTarget(const vector<int>& v, int target) {
    int left{ 0 };
    auto right = v.size() - 1;
    int minDiff{ numeric_limits<int>::max() };
    pair<int, int> pair;

    while (left < right) {
      // Check if sum of the current pair is less than the min difference found so far.
      if (abs(v[left] + v[right] - target) < minDiff) {
        minDiff = abs(v[left] + v[right] - target);
        pair = make_pair(v[left], v[right]);
      }

      if (v[left] + v[right] > target) {
        // The sum is greater than the target so try decreasing it by picking a smaller right number.
        right--;
      } else {
        // The sum less than the target so try increasing it by picking a larger left number
        left++;
      }
    }

    return pair;
  }

  TEST_CLASS(FindPairClosestToTargetNumberInSortedArrayTests) {
    public:
      TEST_METHOD(WhenPairWithNegatives_ExpectClosestSumChosen) {
        auto result = findPairSumClosestToTarget({ 1, 3, 5, 10 }, 4);
        Assert::AreEqual(1, result.first);
        Assert::AreEqual(3, result.second);
      }

      TEST_METHOD(WhenPair_ExpectClosestSumChosen) {
        auto result = findPairSumClosestToTarget({ -100, -50, -30, 0, 15, 25, 50, 100 }, 40);
        Assert::AreEqual(15, result.first);
        Assert::AreEqual(25, result.second);
      }
  };

  // Console Test Code
  //void displayVector(const vector<int>& v) {
  //  cout << "[ ";
  //  for (auto const &item : v) { cout << item << " "; }
  //  cout << "]" << endl;
  //}

  // Console Test Code
  //void displayPairClosestToTarget(const vector<int>& v, int target) {
  //  displayVector(v);

  //  auto bruteForceSolution = bruteForce(v, target);
  //  cout << "Brute Force solution: [ " << bruteForceSolution.first << " " << bruteForceSolution.second << " ]" << endl;

  //  auto betterSolution = findPairSumClosestToTarget(v, target);
  //  cout << "Better solution: [ " << betterSolution.first << " " << betterSolution.second << " ]" << endl;

  //  cout << endl;
  //}
}

// Console Test Code
//int main() {
//  FindPairClosestToTargetNumberInSortedArray::displayPairClosestToTarget({ 1, 3, 5, 10 }, 4);
//  FindPairClosestToTargetNumberInSortedArray::displayPairClosestToTarget({ -100, -50, -30, 0, 15, 25, 50, 100 }, 40);
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
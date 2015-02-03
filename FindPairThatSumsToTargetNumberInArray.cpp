// Given a unsorted array find the pair of elements
// in the array whose sum equals a target number.
//
// Brute Force - O(n^2) Time, O(1) Space
// Sort And Scan - O(nlog(n)) Time , O(1) Space but it mutates the array
// Hash And Scan - O(n) Time , O(n) Space
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FindPairThatSumsToTargetNumberInArray {

  // O(n^2) time, O(1) space
  pair<int, int> bruteForce(const vector<int>& v, int target) {
    for (auto i = 0; i < v.size(); i++) {
      for (auto j = i + 1; j < v.size(); j++) {
        if (v[i] + v[j] == target) {
          return make_pair(v[i], v[j]);
        }
      }
    }
    return make_pair(0, 0);
  }

  // Sort the array and scan for elements that sum to the target value.
  // O(nlog(n)) Time, O(1) Space but it mutates the array.
  pair<int, int> sortAndScan(vector<int>&& v, int target) {
    sort(v.begin(), v.end());

    auto left = 0;
    auto right = v.size() - 1;

    while (left < right) {
      auto sum = v[left] + v[right];
      if (sum < target) { // Sum is less so increase it by picking a bigger left number
        left++;
      } else if (sum > target) { // Sum is greater so decrease it by picking a small right number
        right--;
      } else { // sum == target
        return{ v[left], v[right] };
      }
    }

    // We didn't find a pair that would sum up to the target value.
    return{ 0, 0 };
  }

  // Hash the array and then scan the array trying to find a pair that would sum to the target.
  // O(n) Time, O(n) Space
  pair<int, int> hashAndScan(const vector<int>& v, int target) {
    unordered_set<int> lookup(v.cbegin(), v.cend());
    for (const auto& i : v) {
      auto difference = target - i;
      if (lookup.find(difference) != lookup.cend()) {
        return{ i, difference };
      }
    }

    // We didn't find a pair that would sum up to the target value.
    return{ 0, 0 };
  }

  TEST_CLASS(FindPairThatSumsToTargetNumberInArrayTests) {
    public:
      TEST_METHOD(WhenSmallPair_ExpectNearestSumChosen) {
        auto result = sortAndScan({ 4, 6, 1, 3, 2, 5 }, 8);
        Assert::AreEqual(2, result.first);
        Assert::AreEqual(6, result.second);
      }

      TEST_METHOD(WhenLargerPair_ExpectNearestSumChosen) {
        auto result = sortAndScan({ 10, 8, 4, 6, 1, 3, 7, 2, 11, 5 }, 10);
        Assert::AreEqual(2, result.first);
        Assert::AreEqual(8, result.second);
      }
  };

  // Console Test Code
  //void displayVector(const vector<int>& v) {
  //  cout << "[ ";
  //  for (auto const &item : v) { cout << item << " "; }
  //  cout << "]" << endl;
  //}

  // Console Test Code
  //void displayFindPair(vector<int> v, int target) {
  //  displayVector(v);

  //  auto bruteForceResult = bruteForce(v, target);
  //  cout << "Brute Force solution: [ " << bruteForceResult.first << " " << bruteForceResult.second << " ]" << endl;

  //  auto sortAndScanResult = sortAndScan(v, target);
  //  cout << "Sort and Scan solution: [ " << sortAndScanResult.first << " " << sortAndScanResult.second << " ]" << endl;

  //  auto hashAndScanResult = hashAndScan(v, target);
  //  cout << "Hash and Scan solution: [ " << hashAndScanResult.first << " " << hashAndScanResult.second << " ]" << endl;

  //  cout << endl;
  //}
}

// Console Test Code
//int main() {
//  FindPairThatSumsToTargetNumberInArray::displayFindPair({ 4, 6, 1, 3, 2, 5 }, 8);
//  FindPairThatSumsToTargetNumberInArray::displayFindPair({ 10, 8, 4, 6, 1, 3, 7, 2, 11, 5 }, 10);
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
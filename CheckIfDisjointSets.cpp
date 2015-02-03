// Given two vectors determine if they are disjoint sets or not.
//
// Contains a O(mn) brute force, O(mlog(m) + nlog(n))sorting and scanning, 
// and a O(m + n) hashing solution.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DisjointSets {

  // Brute Force
  // Time Complexity: O(mn)
  // Space Complexity: O(1)
  bool bruteForce(const vector<int>& set1, const vector<int> &set2) {
    for (auto const &i : set1) {
      for (auto const &j : set2) {
        if (i == j) {
          return false;
        }
      }
    }
    return true;
  }

  // Sort the sets and then use a merge like process to compare elements.
  // Time Complexity: O(nlog(n) + mlog(m)) 
  // Space Complexity: O(1) but it modifies the input sets.
  bool sortAndScan(vector<int>&& set1, vector<int>&& set2) {
    std::sort(set1.begin(), set1.end()); // O(nlog(n))
    std::sort(set2.begin(), set2.end()); // O(nlog(n))

    // Walk through the sets and count
    auto i = 0;
    auto j = 0;

    while (i < set1.size() && j < set2.size()) { // O(n + m)
      if (set1[i] < set2[j]) {
        i++;
      } else if (set1[i] > set2[j]) {
        j++;
      } else { // set1[i] == set2[j]
        return false;
      }
    }

    return true;
  }

  // Store first set in hash set and then iterate over the 
  // second set checking if each element exists in the first set.
  // Time Complexity: O(m + n)
  // Space Complexity: O(m) to store first set in map
  bool hashAndScan(const vector<int>& set1, const vector<int>& set2) {
    std::unordered_set<int> set1Lookup(set1.cbegin(), set1.cend());
    for (const auto& item : set2) {
      if (set1Lookup.find(item) != set1Lookup.cend()) {
        return false;
      }
    }
    return true;
  }

  TEST_CLASS(DisjointSetsTests) {
  public:
    TEST_METHOD(WhenDisjoint_ExpectTrue) {
      Assert::IsTrue(sortAndScan({ 1, 2 }, { 3, 4 }));
    }

    TEST_METHOD(WhenNotDisjoint_ExpectFalse) {
      Assert::IsFalse(sortAndScan({ 1, 2, 3 }, { 3, 4, 5 }));
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
  //void displayDisjointSets(vector<int> set1, vector<int> set2) {
  //  displayVector(set1);
  //  displayVector(set2);
  //  cout << "Brute Force solution: " << bruteForce(set1, set2) << endl;
  //  cout << "Sort and scan solution: " << sortAndScan(set1, set2) << endl;
  //  cout << "Hash and scan solution: " << hashAndScan(set1, set2) << endl;
  //  cout << endl;
  //}
}

// Console Test Code
//int main() {
//  DisjointSets::displayDisjointSets({ 1, 2 }, { 3, 4 });
//  DisjointSets::displayDisjointSets({ 1, 2, 3 }, { 3, 4, 5 });
//  DisjointSets::displayDisjointSets({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 });
//  DisjointSets::displayDisjointSets({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 14 }, { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 });
//
//  cout << endl << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
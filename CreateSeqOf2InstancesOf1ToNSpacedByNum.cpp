// Given a number n using backtracking to attempt
// to fill an array with two instances of every
// number from 1 to n.  The two instance of number i
// must be separated by i numbers.
// Ex: n = 3 => [3, 1, 2, 1, 3, 2]
//
// Time Complexity: O(n!)
// Space Complexity: O(n)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <unordered_map>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CreateSeqOf2InstancesOf1ToNSpacedByNum {

  bool attemptToFill(int curr, int n, vector<int>& v) {
    // Base case: current number is zero so all numbers have been filled.
    if (curr == 0) { return true; }

    // Try placing two instances of curr at all possible locations
    for (auto i = 0; i < v.size() - 1 - curr; i++) {
      if (v[i] == 0 && v[i + 1 + curr] == 0) {
        // The two instances are curr elements apart.  Ex: 2##2, 3###3
        v[i] = curr;
        v[i + 1 + curr] = curr;

        // Does this placement yield a solution?
        if (attemptToFill(curr - 1, n, v)) {
          return true; // Found a solution
        }

        // Solution wasn't found so restore original state so we can backtrack. 
        v[i] = 0;
        v[i + 1 + curr] = 0;
      }
    }
    
    return false; // Didn't find a solution.
  }

  vector<int> attemptToFill(int n) {
    vector<int> v(2*n, 0); // Fill array with 2 * n zeros
    if (!attemptToFill(n, n, v)) {
      // If we didn't find solution return an empty array.
      v.clear();
    }

    return move(v);
  }

  TEST_CLASS(CreateSeqOf2InstancesOf1ToNSpacedByNumTests) {
    public:
      TEST_METHOD(WhenImpossible_ExpectEmpty) {
        auto result = attemptToFill(2);
        Assert::AreEqual(size_t(0), result.size());
      }

      TEST_METHOD(WhenPossible_ExpectTwoInstancesOfEveryNumber) {
        auto result = attemptToFill(3);
        Assert::AreEqual(size_t(6), result.size());
        Assert::AreEqual(2, count(result.cbegin(), result.cend(), 1));
        Assert::AreEqual(2, count(result.cbegin(), result.cend(), 2));
        Assert::AreEqual(2, count(result.cbegin(), result.cend(), 3));
      }

      TEST_METHOD(WhenPossible_ExpectInstanceSeperatedByNumberElements) {
        auto result = attemptToFill(4);
        unordered_map<int, int> map;
        for (auto i = 0; i < result.size(); i++) {
          auto val = result[i];
          if (map.find(val) == map.cend()) {
            // First instance of number so store it.
            map.insert(make_pair(val, i));
          } else {
            // Second instance of number so check distance from first instance.
            auto firstLocation = map[val];
            Assert::AreEqual(val, i - 1 - firstLocation);
          }
        }
      }
  };
}
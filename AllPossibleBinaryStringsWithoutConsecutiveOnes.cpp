// Output all possible binary (1/0) strings that have no
// consecutive 1s for a given number of digits.
//
// Time Complexity: O(N^2) where N is the number of digits.
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include <cassert>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AllPossibleBinaryStringsWithoutConsecutiveOnes {

  // Uses dynamic programming so each pass builds up it's strings
  // based on the previous passes strings.
  // If the string ends with 1 we can only append 0. 
  // If the string ends with 0 we can append both 1 and 0.
  void getBinaryStrings(vector<string>& v, int numDigits) {
    if (numDigits == 0) {
      // Base Case: no digits give no binary strings.
      return;
    } else if (numDigits == 1) {
      // Base Case: one digits gives two possible binary strings.
      v.emplace_back("1");
      v.emplace_back("0");
      return;
    }

    getBinaryStrings(v, numDigits - 1);
    assert(v.size() >= 2);

    auto len = v[0].length();
    vector<string> newStrings;
    for (auto& s : v) {
      if (s[len - 1] == '0') {
        // Ends with 0 so create a copy and append 1.
        string copy(s);
        copy.append("1");
        newStrings.emplace_back(copy);
      }

      // Can append a 0.
      s.append("0");
    }

    for (auto& s : newStrings) {
      v.emplace_back(s);
    }
  }

  TEST_CLASS(AllPossibleBinaryStringsWithoutConsecutiveOnesTests) {
    public:
      TEST_METHOD(WhenZeroDigits_ExpectZeroStrings) {
        vector<string> results;
        getBinaryStrings(results, 0);
        Assert::AreEqual(size_t(0), results.size());
      }

      TEST_METHOD(WhenOneDigit_ExpectTwoPossibleStrings) {
        vector<string> results;
        getBinaryStrings(results, 1);
        sort(results.begin(), results.end());
        Assert::IsTrue("0" == results[0]);
        Assert::IsTrue("1" == results[1]);
      }

      TEST_METHOD(WhenThreeDigits_ExpectFivePossibleStrings) {
        vector<string> results;
        getBinaryStrings(results, 3);
        sort(results.begin(), results.end());
        Assert::IsTrue("000" == results[0]);
        Assert::IsTrue("001" == results[1]);
        Assert::IsTrue("010" == results[2]);
        Assert::IsTrue("100" == results[3]);
        Assert::IsTrue("101" == results[4]);
      }
  };
}
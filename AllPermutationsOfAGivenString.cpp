// Print all permutations of a given string using backtracking.
// Time Complexity: O(n*n!)
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AllPermutationsOfAGivenString {

  void swap(char& x, char& y) {
    auto temp = x;
    x = y;
    y = temp;
  }

  void getPermutations(string& arr, int lvl, int n, vector<string>& results) {
    if (lvl == n) {
      results.emplace_back(arr);
      return;
    }

    for (auto i = lvl; i <= n; i++) {
      swap(arr[i], arr[lvl]);
      getPermutations(arr, lvl + 1, n, results);

      // We are backtracking so restore original value;
      swap(arr[lvl], arr[i]);
    }
  }

  vector<string> getPermutations(const string& s) {
    string arr(s);
    vector<string> results;
    getPermutations(arr, 0, arr.length() - 1, results);
    return move(results);
  }

  TEST_CLASS(AllPermutationsOfAGivenStringTests) {
    public:
      TEST_METHOD(WhenEmpty_ExpectZeroPermutations) {
        auto results = getPermutations("");
        Assert::AreEqual(size_t(0), results.size());
      }

      TEST_METHOD(WhenThreeChar_ExpectSixPermutations) {
        auto results = getPermutations("ABC");
        Assert::AreEqual(size_t(6), results.size()); // 3! = 3 x 2 x 1 = 6
      }

      TEST_METHOD(WhenFourChar_ExpectTwentyFourPermutations) {
        auto results = getPermutations("ABCD");
        Assert::AreEqual(size_t(24), results.size()); // 4! = 4 x 3 x 2 x 1 = 24 
      }

      TEST_METHOD(WhenTwoChar_ExpectAllPossiblePermutations) {
        auto results = getPermutations("AB");
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "AB"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "BA"; }) != results.cend());
      }

      TEST_METHOD(WhenThreeChar_ExpectAllPossiblePermutations) {
        auto results = getPermutations("ABC");
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "ABC"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "ACB"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "BAC"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "BCA"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "CAB"; }) != results.cend());
        Assert::IsTrue(find_if(results.cbegin(), results.cend(), [](const string& x) { return x == "CBA"; }) != results.cend());
      }
  };
}

// Console test program
//int main() {
//  string myString = "ABC";
//  displayPermutations(myString, 0, myString.length() - 1);
//
//  cout << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}
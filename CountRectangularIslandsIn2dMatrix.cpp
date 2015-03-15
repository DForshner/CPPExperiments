// Given a 2-D matrix of O/X characters count the number
// of rectangular 'X' islands surrounded by 'O's.  Islands
// are not horizontally or vertically adjacent but may be 
// diagonally adjacent.
//
// Time Complexity: O(MN)
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <cassert>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CountRectangularIslandsIn2dMatrix {

  // Count the number of upper left corners that are 'X's
  int countIslands(vector<vector<char>>& m) {
    if (m.empty() || m[0].empty()) {
      return 0;
    }
    auto rowSize = m.size();
    auto colSize = m[0].size();
    int count{ 0 };

    for (size_t row = 0; row < rowSize; row++) {
      for (size_t col = 0; col < colSize; col++) {
        assert(m.size() == m[row].size()); // Assert square matrix

        if ((m[row][col] == 'X') // Current tile is 'X'
          && (row == 0 || m[row - 1][col] == 'O') // top row or tile above is 'O'
          && (col == 0 || m[row][col - 1] == 'O') // leftmost row or tile to left is 'O' 
          ) {
          count++;
        }
      }
    }

    return count;
  }

  TEST_CLASS(AATests) {
  public:
      TEST_METHOD(WhenSquareInCenter_ExpectOne) {
        vector<vector<char>> m {
          { 'O', 'O', 'O', 'O' },
          { 'O', 'X', 'X', 'O' },
          { 'O', 'X', 'X', 'O' },
          { 'O', 'O', 'O', 'O' },
        };
        auto result = countIslands(m);
        Assert::AreEqual(1, result);
      }

      TEST_METHOD(WhenIslandsInFourCorners_ExpectFour) {
        vector<vector<char>> m {
          { 'X', 'X', 'O', 'X', 'X' },
          { 'X', 'X', 'O', 'X', 'X' },
          { 'O', 'O', 'O', 'O', 'O' },
          { 'X', 'X', 'O', 'X', 'X' },
          { 'X', 'X', 'O', 'X', 'X' },
        };
        auto result = countIslands(m);
        Assert::AreEqual(4, result);
      }
  };
}
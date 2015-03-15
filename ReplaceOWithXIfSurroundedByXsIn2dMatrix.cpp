// Given a matrix of X/O elements replace all Os with Xs if they are
// completely surrounded (Left/Right/Up/Down) by Xs.
//
// Time Complexity: O(MN)
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReplaceOWithXIfSurroundedByXsIn2dMatrix {

  void floodFill(vector<vector<char>>& m, size_t x, size_t y, char from, char to) {
    // If invalid tile position
    if (y < 0 || y >= m.size() || x < 0 || x >= m[y].size()
      // not right type of tile
      || m[y][x] != from) {
      return;
    }

    // Change current tile
    m[y][x] = to;

    // Change neighbors
    floodFill(m, x - 1, y, from, to); // Left
    floodFill(m, x + 1, y, from, to); // Right
    floodFill(m, x, y - 1, from, to); // Down
    floodFill(m, x, y + 1, from, to); // Up
  }

  void replaceSurrounded(vector<vector<char>>& m) {
    size_t xMin = 0;
    size_t xMax = m[0].size() - 1;
    size_t yMin = 0;
    size_t yMax = m.size() - 1;

    // Change all Os to temporary type T.
    for (auto& row : m) {
      for (auto& pos : row) {
        if (pos == 'O') {
          pos = 'T';
        }
      }
    }

    // Restore any Ts around outermost edges to Os.
    for (auto y = yMin; y <= yMax; y++) {
      floodFill(m, xMin, y, 'T', 'O'); // Left Edge
      floodFill(m, xMax, y, 'T', 'O'); // Right Edge
    }

    for (auto x = xMin; x <= xMax; x++) {
      floodFill(m, x, yMin, 'T', 'O'); // Top Edge
      floodFill(m, x, yMax, 'T', 'O'); // Bottom Edge
    }

    // Fill any remaining (non-edge) Ts with Xs. O(MN)
    for (auto y = yMin; y <= yMax; y++) {
      for (auto x = xMin; x <= xMax; x++) {
        floodFill(m, x, y, 'T', 'X');
      }
    }
  }

  TEST_CLASS(ReplaceOWithXIfSurroundedByXsIn2dMatrixTests) {

    public:
      TEST_METHOD(WhenEdges_ExpectNoChange) {
        vector<vector<char>> result{
          { 'X', 'O', 'X' },
          { 'X', 'X', 'X' },
          { 'X', 'X', 'X' },
        };
        replaceSurrounded(result);
        vector<vector<char>> expected{
          { 'X', 'O', 'X' },
          { 'X', 'X', 'X' },
          { 'X', 'X', 'X' },
        };

        assertMatch(result, expected);
      }

      TEST_METHOD(WhenSurrounded_ExpectChanged) {
        vector<vector<char>> result {
          { 'X', 'X', 'X' },
          { 'X', 'O', 'X' },
          { 'X', 'X', 'X' },
        };
        replaceSurrounded(result);
        vector<vector<char>> expected {
          { 'X', 'X', 'X' },
          { 'X', 'X', 'X' },
          { 'X', 'X', 'X' },
        };

        assertMatch(result, expected);
      }

      TEST_METHOD(WhenSurroundedAndEdge_ExpectOnlySurroundedChanged) {
        vector<vector<char>> result {
          { 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'O', 'X', 'O', 'X' },
          { 'X', 'O', 'X', 'O', 'X' },
          { 'X', 'O', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'O', 'O' },
        };
        replaceSurrounded(result);
        vector<vector<char>> expected {
          { 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'X', 'X' },
          { 'X', 'X', 'X', 'O', 'O' },
        };

        assertMatch(result, expected);
      }

    private:
      void assertMatch(vector<vector<char>>& expected, vector<vector<char>>& result) {
        for (size_t y{ 0 }; y < result.size(); y++) {
          for (size_t x{ 0 }; x < result[y].size(); x++) {
            Assert::AreEqual(expected[y][x], result[y][x]);
          }
        }
      }
  };
}
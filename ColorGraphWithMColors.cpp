#include "CppUnitTest.h"
#include <string>
#include <memory>
#include <cassert>
#include <array>

namespace ColorGraphWithMColors {

  const int BLANK = 0;

  template <size_t size>
  bool neighborsShareColor(const std::array<std::array<bool, size>, size>& graph, std::array<int, size> colors, int currentVertex, int color) {
      for (int a = 0; a < graph.size(); a++) {
        if (graph[currentVertex][a] && colors[a] == color)
          return true;
      }
      return false;
  }

  template <size_t size>
  bool colorGraph(const std::array<std::array<bool,size>,size>& graph, int numColors, std::array<int,size>& colors, int currentVertex) {

    // Base Case: if all of the vertexes have been colored then we are done.
    if (currentVertex == size) { return true; }

    // Try out each color on this node
    for (int c = 1; c <= numColors; c++) {

      // if any neighboring nodes have same color try new color.
      if (neighborsShareColor(graph, colors, currentVertex, c))
        continue;

      // Try out this color
      colors[currentVertex] = c;

      // If we are able to recursively color all following nodes.
      if (colorGraph(graph, numColors, colors, currentVertex + 1))
        return true;

      // No workable combination of colors could be found with 
      // this node set c so backtrack and try a new color.
      colors[currentVertex] = BLANK;
    }

    // No color could be found for this node that lead to a solution.
    return false;
  }
    
  using namespace Microsoft::VisualStudio::CppUnitTestFramework;

  TEST_CLASS(ColorGraphWithMColorsTests) {
  public:
    TEST_METHOD(WhenLessThanMinAmountOfColorsNeeded_ExpectFalse) {
      std::array<std::array<bool, 4>, 4> graph = 
      { { 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }, 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }
      } };
      std::array<int, 4> colors;
      colors.fill(BLANK);
      auto result = colorGraph(graph, 1, colors, 0);
      Assert::IsFalse(result);
    }

    TEST_METHOD(WhenMinAmountOfColorsNeeded_ExpectTrue) {
      std::array<std::array<bool, 4>, 4> graph = 
      { { 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }, 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }
      } };
      std::array<int, 4> colors;
      colors.fill(BLANK);
      auto result = colorGraph(graph, 2, colors, 0);
      Assert::IsTrue(result);
    }

    TEST_METHOD(WhenMoreThanAmountOfColorsNeeded_ExpectTrue) {
      std::array<std::array<bool, 4>, 4> graph = 
      { { 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }, 
        { 0, 1, 0, 1 }, 
        { 1, 0, 1, 0 }
      } };
      std::array<int, 4> colors;
      colors.fill(BLANK);
      auto result = colorGraph(graph, 10, colors, 0);
      Assert::IsTrue(result);
    }
  };
}
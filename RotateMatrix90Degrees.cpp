#include "stdafx.h"
#include "CppUnitTest.h"

#include <array>

// Rotates a square matrix built using std::array in place 90 degrees.
// O(n^2)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RotateMatrix90Degrees 
{
  template <typename T, size_t N>
  class MatrixOperations {
  public:
    static void Rotate(std::array<std::array<T, N>, N>* matrix) {
      for (auto layer = 0; layer < N / 2; ++layer) {
        auto start = layer;
        auto end = N - 1 - layer;

        for (auto i = start; i < end; ++i) {
          int offset = i - start;
          T top = matrix->at(start)[i];
          matrix->at(start)[i] = matrix->at(end - offset)[start]; // Left -> Top
          matrix->at(end - offset)[start] = matrix->at(end)[end- offset]; // Bottom -> Left
          matrix->at(end)[end - offset] = matrix->at(i)[end]; // Right -> Bottom
          matrix->at(i)[end] = top; // Top -> Right
        }
      }
    }
  };
  
  TEST_CLASS(RotateMatrix90DegreesTests)
  {
  public:
    TEST_METHOD(Rorate_WhenTwoByTwoMatrixOnStack_ExpectCorrect)
    {
      std::array<std::array<int, 2>, 2> m { { 
        { { 1, 2 } }, 
        { { 3, 4 } } 
      } };
      MatrixOperations<int, 2>::Rotate(&m);
      // 3, 1
      // 4, 2
      Assert::AreEqual(3, m[0][0]);
      Assert::AreEqual(1, m[0][1]);
      Assert::AreEqual(4, m[1][0]);
      Assert::AreEqual(2, m[1][1]);
    }

    TEST_METHOD(Rorate_WhenThreeByThreeMatrixOnHeap_ExpectCorrect)
    {
      auto m = new std::array<std::array<int, 3>, 3>
      { {
        { { 1, 2, 3 } },
        { { 4, 5, 6 } },
        { { 7, 8, 9 } }
      } };
      MatrixOperations<int, 3>::Rotate(m);
      // 7, 4, 1
      // 8, 5, 2
      // 9, 6, 3 
      Assert::AreEqual(7, m->at(0)[0]);
      Assert::AreEqual(4, m->at(0)[1]);
      Assert::AreEqual(1, m->at(0)[2]);
      Assert::AreEqual(8, m->at(1)[0]);
      Assert::AreEqual(5, m->at(1)[1]);
      Assert::AreEqual(2, m->at(1)[2]);
      Assert::AreEqual(9, m->at(2)[0]);
      Assert::AreEqual(6, m->at(2)[1]);
      Assert::AreEqual(3, m->at(2)[2]);
    }
  };
}
#pragma once

#include "CppUnitTest.h"
#include "InsertionSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{
  TEST_CLASS(InsertionSortTests)
  {
    TEST_METHOD(InsertionSortTests_WhenSingleElement_ExpectNoChanges)
    {
      // Arrange
      static const int values[] = {1};
      vector<int> v(values, values + sizeof(values) / sizeof(values[0])); 
      auto sorter = new InsertionSort();
      // Act
      sorter->Sort(v);
      // Assert
      Assert::IsTrue(v[0] = 1);
    }

    TEST_METHOD(InsertionSortTests_WhenSortUnsortedArray_ExpectSortedLeastToGreatest)
    {
      // Arrange
      static const int values[] = {2,6,4,8,9,1,0,3,5,7};
      vector<int> v(values, values + sizeof(values) / sizeof(values[0])); 
      auto sorter = new InsertionSort();
      // Act
      sorter->Sort(v);
      // Assert
      std::stringstream ss;
      for(int n : v)
        ss << n;
      Assert::IsTrue("0123456789" == ss.str());
    }
  };
}
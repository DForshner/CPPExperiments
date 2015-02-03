#include "CppUnitTest.h"
#include "MedianOf3QuickSort.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{		
	TEST_CLASS(MedianOf3QuickSortTests)
	{
	public:

    TEST_METHOD(MedianOf3QuickSortTests_WhenSortListWithOneElement_ExpectNoError)
		{
      // Arrange
      auto sorter = new MedianOf3QuickSort();
      static const int values[] = {3};
      vector<int> v(values, values + sizeof(values) / sizeof(values[0]) );
      // Act
      sorter->Sort(v);
      // Assert
      Assert::IsTrue(v[0] = v[0]);
    }

    TEST_METHOD(MedianOf3QuickSortTests_WhenSortListWithTwoElements_ExpectSorted)
		{
      // Arrange
      auto sorter = new MedianOf3QuickSort();
      static const int values[] = {9,6};
      vector<int> v (values, values + sizeof(values) / sizeof(values[0]) );
      // Act
      sorter->Sort(v);
      // Assert
      Assert::IsTrue(v[0] < v[1]);
    }

    TEST_METHOD(MedianOf3QuickSortTests_WhenSortListWithThreeElements_ExpectSortedLeastToGreatest)
		{
      // Arrange
      auto sorter = new MedianOf3QuickSort();
      static const int values[] = {3,9,6};
      vector<int> v (values, values + sizeof(values) / sizeof(values[0]) );
      // Act
      sorter->Sort(v);
      // Assert
      Assert::IsTrue(v[0] < v[1]);
      Assert::IsTrue(v[1] < v[2]);
    }

    TEST_METHOD(MedianOf3QuickSortTests_WhenSortUnorderedList_ExpectSortedLeastToGreatest)
		{
      // Arrange
      auto sorter = new MedianOf3QuickSort();
      static const int values[] = {6,2,7,9,5,8,1,4,3,0};
      vector<int> v (values, values + sizeof(values) / sizeof(values[0]) );
      // Act
      sorter->Sort(v);
      // Assert
      std::stringstream ss;
      for (int n : v)
          ss << n;
      string str = ss.str();
      Assert::IsTrue(str == "0123456789");
    }
  };
}
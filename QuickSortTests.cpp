#include "CppUnitTest.h"
#include "QuickSort.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{		
	TEST_CLASS(QuickSortTests)
	{
	public:
    TEST_METHOD(QuickSort_WhenSortUnorderedList_ExpectSortedLeastToGreatest)
		{
      // Arrange
      auto sorter = new QuickSort();
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
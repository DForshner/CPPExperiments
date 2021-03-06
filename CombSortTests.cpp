#include "CppUnitTest.h"
#include "CombSort.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{		
	TEST_CLASS(CombSortTests)
	{
	public:
    TEST_METHOD(CombSort_WhenSortUnorderedList_ExpectSortedLeastToGreatest)
		{
      // Arrange
      auto sorter = new CombSort();
      static const int values[] = {6,2,7,9,5,8,1,4,3,0};
      vector<int> v (values, values + sizeof(values) / sizeof(values[0]) );
      // Act
      bool result = sorter->Sort(v);
      // Assert
      Assert::IsTrue(v[0] < v[1]);
      Assert::IsTrue(v[1] < v[2]);
      Assert::IsTrue(v[2] < v[3]);
    }
  };
}
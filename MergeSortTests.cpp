#include "CppUnitTest.h"
#include "MergeSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(MergeSortTests)
{
  TEST_METHOD(MergeSort_WhenSortUnorderedList_ExpectSortedLeastToGreatest)
  {
    // Arrange
    MergeSort* sorter = new MergeSort();
    int test[] = {9,5,4,3,2,1,8,7,6,0};
    // Act
    sorter->Sort(test, 10);
    // Assert
    std::stringstream ss;
    for(unsigned i = 0; i < 10; i++)
      ss << test[i];
    Assert::IsTrue(ss.str() == "0123456789");
  }
};
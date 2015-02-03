#include <memory>
#include <limits>
#include <functional>
#include "CppUnitTest.h"
#include "BinaryHeap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{		
	TEST_CLASS(BinaryHeapTests)
	{
	public:
		
		TEST_METHOD(BinaryHeap_Int_WhenInsertSingleElement_ExpectSameElementReturned)
		{
      // Arrange
      std::unique_ptr<BinaryHeap<int>> testHeap(new BinaryHeap<int>(10, INT32_MIN));
      // Act
      testHeap->Insert(1);
      auto result1 = testHeap->Delete_Min();
      // Assert
      Assert::AreEqual<int>(1, result1);
		}

    TEST_METHOD(BinaryHeap_Int_WhenInsertThreeElements_ExpectSmallestElementReturnedFirst)
		{
      // Arrange
      std::unique_ptr<BinaryHeap<int>> testHeap(new BinaryHeap<int>(10, INT32_MIN));
      // Act
      testHeap->Insert(100);
      testHeap->Insert(200);
      testHeap->Insert(300);
      auto result = testHeap->Delete_Min();
      // Assert
      Assert::AreEqual<int>(100, result);
		}

    TEST_METHOD(BinaryHeap_Int_WhenInsertThreeElements_ExpectLargetsElementReturnedLast)
		{
      // Arrange
      std::unique_ptr<BinaryHeap<int>> testHeap(new BinaryHeap<int>(10, INT32_MIN));
      // Act
      testHeap->Insert(100);
      testHeap->Insert(200);
      testHeap->Insert(300);
      testHeap->Delete_Min();
      testHeap->Delete_Min();
      auto result = testHeap->Delete_Min();
      // Assert
      Assert::AreEqual<int>(300, result);
		}

    TEST_METHOD(BinaryHeap_Int_WhenDeleteFromEmptyHeap_ExpectException)
		{
      // Arrange
      std::unique_ptr<BinaryHeap<int>> testHeap(new BinaryHeap<int>(10, INT32_MIN));
      function<void (void)> testPtr = [&testHeap] { testHeap->Delete_Min(); }; // When calling function() with a pointer like: ptr->func() include in capture.
      std::wstring message( L"Expected Exception to be thrown" );
      // Act & Assert
      Assert::ExpectException<std::exception>(testPtr, message.c_str());
		}

    TEST_METHOD(BinaryHeap_Int_WhenInsertIntoFullHeap_ExpectException)
		{
      // Arrange
      std::unique_ptr<BinaryHeap<int>> testHeap(new BinaryHeap<int>(10, INT32_MIN)); 
      
      // Fill heap to max
      for (int x = 0; x < 10; x++)
        testHeap->Insert(x);

      function<void (void)> testPtr = [&testHeap] { testHeap->Insert(10); }; // When calling function() with a pointer like: ptr->func() include in capture.
      std::wstring message( L"Expected Exception to be thrown" );
      // Act & Assert
      Assert::ExpectException<std::exception>(testPtr, message.c_str());
		}
	};
}
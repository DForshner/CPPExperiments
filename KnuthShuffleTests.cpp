#include "CppUnitTest.h"
#include "KnuthShuffle.h"
#include "Utilities/TestUtilities.h"
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace AlgorithmsTests
{		
	TEST_CLASS(KnuthShuffleTests)
	{
	public:
		
    TEST_METHOD(KnuthShuffle_WhenShuffleSingleElement_ExpectSameElementReturned)
		{
      // Arrange
      auto shuffler = new KnuthShuffle();
      string arr[] = { "2C" };
      vector<string> list(arr, arr+8);
      auto old_first_element = list[0];
      // Act
      shuffler->Shuffle(list);
      // Assert
      Assert::AreEqual<string>(list[0], old_first_element);
		}

		TEST_METHOD(KnuthShuffle_WhenShuffleMultipleElements_ExpectElementsShuffled)
		{
      // Arrange
      auto shuffler = new KnuthShuffle();
      string arr[] = { "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C"};
      vector<string> list(arr, arr+8);

      auto test_utility = new TestUtilities();

      auto old_hash = test_utility->hash_vector(list);
      // Act
      shuffler->Shuffle(list);
      // Assert
      auto new_hash = test_utility->hash_vector(list);
      Assert::AreNotEqual<unsigned int>(old_hash, new_hash);
		}
  };
}
  
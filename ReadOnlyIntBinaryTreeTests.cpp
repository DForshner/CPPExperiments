#include "CppUnitTest.h"
#include <array>
#include "ReadOnlyIntBinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace readonly_int_binary_tree;

TEST_CLASS(ReadOnlyIntBinaryTreeTests)
{
  TEST_METHOD(Insert_WhenInsertValue_ExpectValueToExistInBTree)
  {
    // Arrange
    ReadOnlyIntBinaryTree *tree = new ReadOnlyIntBinaryTree();
    tree->Insert(444);
    // Act
    auto result = tree->Search(444)->key_value;
    // Assert
    Assert::AreEqual(444,result);
  }

  TEST_METHOD(Insert_WhenInsertValues_ExpectAllValuesToExistInBinaryTree)
  {
    // Arrange
    ReadOnlyIntBinaryTree *tree = new ReadOnlyIntBinaryTree();
    std::array<int, 10> a = {1,2,3,10,10,10,9,7,5,4};
    for (auto&s: a)
      tree->Insert(s);
    // Act & Assert
    for (auto&s: a)
    {
        auto result = tree->Search(s);
        Assert::AreEqual(s,result->key_value);
    }
  }

  TEST_METHOD(Search_WhenForNumberNotInTree_ExpectNullReturned)
  {
    // Arrange
    ReadOnlyIntBinaryTree *tree = new ReadOnlyIntBinaryTree();
    tree->Insert(444);
    // Act
    auto result = tree->Search(1);
    // Assert
    Assert::IsTrue(result == nullptr);
  }

  TEST_METHOD(DestoryTree_WhenDestory_ExpectValueNotFoundInBTree)
  {
    // Arrange
    ReadOnlyIntBinaryTree *tree = new ReadOnlyIntBinaryTree();
    tree->Insert(444);
    // Act
    tree->DestoryTree();
    auto result = tree->Search(444);
    // Assert
    Assert::IsTrue(result == nullptr);
  }
};
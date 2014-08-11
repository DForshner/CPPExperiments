
#include "CppUnitTest.h"
#include <string>
#include <memory>
#include <cassert>

// Find the first value that matches the key if a BST was
// traversed in order.

namespace BSTFindFirstInOrderKey {

  template <class K, class V>
  class Node {
  public:
    Node(K k, V v) : key(k), value(v) {}
    K key;
    V value;
    void Insert(K k, V v) {
      if (k <= key) {
        if (left_ == nullptr) {
          left_ = std::shared_ptr<Node<K, V>>(new Node<K,V>(k, v));
        } else {
          left_->Insert(k, v);
        }
      } else { 
        if (right_ == nullptr) {
          right_ = std::shared_ptr<Node<K, V>>(new Node<K, V>(k, v));
        } else {
          right_->Insert(k, v);
        }
      }
    }

    Node<K,V>* FindFirstInOrder(K k) {
      if (k == key) {
        // Scan left and see if there are any more matching nodes
        auto leftNode = (left_ != nullptr) ? left_->FindFirstInOrder(k) : nullptr;
        return (leftNode != nullptr) ? leftNode : this;
      }

      if (k < key) {
        if (left_ == nullptr) {
          return nullptr;
        } else {
          return left_->FindFirstInOrder(k);
        }
      } else {
        if (right_ == nullptr) { 
          return nullptr;
        } else {
          return right_->FindFirstInOrder(k);
        }
      }

      return this;
    }

  private:
    std::shared_ptr<Node<K, V>> left_;
    std::shared_ptr<Node<V, K>> right_;
  };

  template <class K, class V>
  class BinarySearchTree {
  public:
    BinarySearchTree() : root_(nullptr) {}

    void Insert(K key, V value) {
      if (root_ == nullptr) {
        root_ = std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value));
      } else {
        root_->Insert(key, value);
      }
    }

    Node<K,V>* FindFirstInOrder(K key) {
      if (root_ == nullptr) { return nullptr; }
      return root_->FindFirstInOrder(key);
    }

  private:
    std::shared_ptr<Node<K, V>> root_;
  };

  using namespace Microsoft::VisualStudio::CppUnitTestFramework;

  TEST_CLASS(BSTFindFirstInOrderKey) {
  public:
    TEST_METHOD(WhenSearchEmptyBST_ExpectNull) {
      BinarySearchTree<std::string, std::string> tree;
      auto result = tree.FindFirstInOrder("4");
      Assert::IsNull(result);
    }

    TEST_METHOD(WhenSearchForNonExistantItem_ExpectNull) {
      BinarySearchTree<std::string, std::string> tree;
      tree.Insert("1", "A");
      tree.Insert("3", "C");
      tree.Insert("2", "B");
      auto result = tree.FindFirstInOrder("4");
      Assert::IsNull(result);
    }

    TEST_METHOD(WhenSearchForSecondItemInRightLeaningTree_ExpectSuccess) {
      BinarySearchTree<std::string, std::string> tree;
      tree.Insert("1", "A");
      tree.Insert("2", "B");
      tree.Insert("3", "C");
      auto result = tree.FindFirstInOrder("2");
      Assert::AreEqual(std::string("B"), result->value);
    }

    TEST_METHOD(WhenSearchForItemWithMultipleNodes_ExpectFirstInOrder) {
      BinarySearchTree<std::string, std::string> tree;
      tree.Insert("5", "A");
      tree.Insert("6", "B");
      tree.Insert("4", "C");
      tree.Insert("2", "D");
      tree.Insert("2", "E");
      tree.Insert("0", "F");
      tree.Insert("1", "G");
      tree.Insert("2", "H");
      auto result = tree.FindFirstInOrder("2");
      Assert::AreEqual(std::string("H"), result->value);
    }
  };

}
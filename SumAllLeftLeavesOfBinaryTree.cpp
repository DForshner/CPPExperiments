// Given a binary tree sum all of the left leaves.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <memory>
#include <vector>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SumAllLeftLeavesOfBinaryTree {

  class Node {
    public:
      int value;
      shared_ptr<Node> left;
      shared_ptr<Node> right;

      Node(int v) : value(v) {}

      void insert(shared_ptr<Node> node) {
        if (node->value <= value) {
          if (left == nullptr) {
            left = node;
          } else {
            left->insert(node);
          }
        } else {
          if (right == nullptr) {
            right = node;
          } else {
            right->insert(node);
          }
        }
      }
  };

  int sumOfAllLeftLeaves(shared_ptr<Node> node) {
    int sum = 0;

    if (node->left != nullptr) { // && node->right == nullptr) {
      if (node->left->left == nullptr) { // Base case
        return node->left->value;
      } else {
        sum += sumOfAllLeftLeaves(node->left);
      }
    }

    if (node->right != nullptr) {
      sum += sumOfAllLeftLeaves(node->right);
    }

    return sum;
  }

  shared_ptr<Node> buildTree(const vector<int> values) {
    auto root = make_shared<Node>(Node(values[0]));

    for (auto i = 1; i < values.size(); i++) {
      root->insert(make_shared<Node>(Node(values[i])));
    }

    return root;
  }

  TEST_CLASS(SumAllLeftLeavesOfBinaryTreeTests) {
  public:
    TEST_METHOD(WhenAllRightChildren_ExpectZero) {
      auto tree = buildTree({ 1, 2, 3, 4 });
      auto result = sumOfAllLeftLeaves(tree);
      Assert::AreEqual(0, result);
    }

    TEST_METHOD(WhenAllLeftChildren_ExpectLeftmostNode) {
      auto tree = buildTree({ 5, 4, 3, 2 });
      auto result = sumOfAllLeftLeaves(tree);
      Assert::AreEqual(2, result);
    }

    //     10
    //  5     15
    // 2  8 12  18
    TEST_METHOD(WhenBalancedTree_ExpectSumOfAllLeftLeaves) {
      auto tree = buildTree({ 10, 5, 15, 2, 8, 12, 18});
      auto result = sumOfAllLeftLeaves(tree);
      Assert::AreEqual(2 + 12, result);
    }
  };
}
// Given an unsorted array find the Kth smallest element.
//
// Construct a min heap from the unsorted array and then remove k elements.
// The last element removed will be the Kth smallest element.
// 
// A brute force solution for this problem would be to sort the entire array and 
// then take the element at position k which would take O(nLog(n)).  There is another 
// algorithm called Quick Select that has an average time complexity of O(n).
//
// Time Complexity: O(n + klog(n))
// Space Complexity: O(n) to copy elements into min heap.
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SelectKthElementInUnsortedArrayHeapSelect {

  class MinHeap {
    public:
      MinHeap(vector<int> arr) : 
        _size(arr.size()) {

        // Order the elements in the heap.
        _heap.assign(arr.cbegin(), arr.cend());
        for (int i = (_size - 1) / 2; i >= 0; i--) {
          heapify(i);
        }
      }

      int extractMin() {
        if (_size == size_t(0)) { return numeric_limits<int>::min(); }

        auto rootValue = _heap[ROOT];

        // Move the last item to the root and apply the heap order property.
        if (_size > 1) {
          _heap[ROOT] = _heap[_size - 1];
          heapify(ROOT);
        }
        _size--;

        return rootValue;
      }

    private:
      vector<int> _heap;
      int _size;
      const int ROOT = 0;

      // Recursively apply the heap-order property to all of the sub-tree's rooted at i.
      void heapify(int i) {
        auto smallest = i;

        auto leftChild = i * 2 + 1;
        if (leftChild < _size && _heap[leftChild] < _heap[smallest]) {
          smallest = leftChild;
        }

        auto rightChild = i * 2 + 2;
        if (rightChild < _size && _heap[rightChild] < _heap[smallest]) {
          smallest = rightChild;
        }

        if (smallest != i) {
          swap(_heap[i], _heap[smallest]);
          heapify(smallest);
        }
      }
  };

  int selectKthSmallest(vector<int>& v, int k) {
    if (k < 0 || k > int(v.size())) { return numeric_limits<int>::min(); }
    MinHeap heap(v);

    for (auto i = 0; i < k; i++) {
      heap.extractMin();
    }

    return heap.extractMin();
  }

  TEST_CLASS(SelectKthElementInUnsortedArrayHeapSelectTests) {
    public:
      TEST_METHOD(WhenKthNegative_ExpectIntMin) {
        vector<int> values{ 2, 4, 8, 7, 6, 9, 3 };
        auto result = selectKthSmallest(values, -1);
        Assert::AreEqual(numeric_limits<int>::min(), result);
      }

      TEST_METHOD(WhenKthLargerThanArray_ExpectIntMin) {
        vector<int> values{ 2, 4, 8, 7, 6, 9, 3 };
        auto result = selectKthSmallest(values, 10);
        Assert::AreEqual(numeric_limits<int>::min(), result);
      }

      TEST_METHOD(WhenKthExists_ExpectReturned) {
        vector<int> values{ 2, 4, 8, 7, 6, 9, 3 };
        auto result = selectKthSmallest(values, 3);
        Assert::AreEqual(6, result);
      }
  };
}
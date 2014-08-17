
#include "CppUnitTest.h"
#include <cassert>
#include <list>
#include <vector>

// Topologically sort a directed acyclic graph.
// Time Complexity O(V + E)
// Space Complexity O(V)

namespace TopologicalSortDAG {

  class Graph {
  public:
    Graph(int v) {
      adj.resize(v);
    }

    void insert(int v, int u) {
      assert(v >= 0 && v < adj.size());
      assert(u >= 0 && u < adj.size());
      adj[v].emplace_back(u);
    }

    std::vector<int> topologicalSort() {
      std::vector<int> stack;
      stack.reserve(adj.size());

      // Mark all nodes as unvisited
      std::vector<bool> visited(adj.size());
      std::fill(visited.begin(), visited.end(), false);

      // Visit every node in the graph 
      for (const auto &v : adj) {
        auto i = &v - &adj[0];
        if (!visited[i])
          sort(stack, visited, i);
      }

      return stack;
    }

  private:
    std::vector<std::list<int>> adj;

    void sort(std::vector<int>& stack, std::vector<bool>& visited, int v) {
      visited[v] = true; // Mark node as visited

      // Recursively sort all adjacent unvisited nodes adjacent to this one.
      for (const auto &u : adj[v]) {
        if (!visited[u])
          sort(stack, visited, u);
      }

      // Now that all of this node's neighbors have been visited push it onto stack. 
      stack.push_back(v);
    }
  };

  using namespace Microsoft::VisualStudio::CppUnitTestFramework;

  TEST_CLASS(TopologicalSortDAGTests) {
  public:
    TEST_METHOD(WhenSortEmpty_ExpectEmptyReturned) {
      Graph graph(0);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(size_t(0), sorted.size());
    }

    TEST_METHOD(WhenSortOnlyUnconnectedNodes_ExpectAllNodesReturned) {
      Graph graph(5);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(size_t(5), sorted.size());
    }

    TEST_METHOD(WhenSortLinearDep_ExpectLinearDepReturned) {
      // 4 -> 3 -> 2 -> 1 -> 0
      Graph graph(5);
      graph.insert(3, 2);
      graph.insert(1, 0);
      graph.insert(2, 1);
      graph.insert(4, 3);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(0, sorted[0]);
      Assert::AreEqual(1, sorted[1]);
      Assert::AreEqual(2, sorted[2]);
      Assert::AreEqual(3, sorted[3]);
      Assert::AreEqual(4, sorted[4]);
    }

    TEST_METHOD(WhenSortCommonAncestor_ExpectAncestorAtTop) {
      // 4 -> 3 -> 1 
      //  \-> 2 -> 0 
      Graph graph(5);
      graph.insert(4, 3);
      graph.insert(4, 2);
      graph.insert(3, 1);
      graph.insert(2, 0);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(4, sorted[4]);
    }

    TEST_METHOD(WhenSortCommonDecendant_ExpectDecendantAtBottom) {
      // 4 -> 3 -> 1 -> 0
      //           2 -/
      Graph graph(5);
      graph.insert(2, 0);
      graph.insert(4, 3);
      graph.insert(3, 1);
      graph.insert(1, 0);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(0, sorted[0]);
    }
  };
}
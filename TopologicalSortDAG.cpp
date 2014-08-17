
#include "CppUnitTest.h"
#include <cassert>
#include <list>
#include <vector>
#include <limits>
#include <set>
#include <functional>

// Topologically sort a directed acyclic graph.
// Complexity O(V + E)

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

      // If there is no starting node then there is nothing to sort.
      auto start = findNodeWithZeroInDegree();
      if (start == std::numeric_limits<int>::min())
        return stack;

      // Mark all nodes as unvisited
      std::vector<bool> visited(adj.size());
      std::fill(visited.begin(), visited.end(), false);

      sort(stack, visited, start);

      return stack;
    }

  private:
    std::vector<std::list<int>> adj;

    void sort(std::vector<int>& stack, std::vector<bool>& visited, int v) {
      visited[v] = true; // Mark node as visited

      // Recursively sort all adjacent unvisited nodes
      for (const auto &u : adj[v]) {
        if (!visited[u])
          sort(stack, visited, u);
      }

      // Now that all of this node's neighbors have been visited push it onto stack. 
      stack.push_back(v);
    }

    // Traverses entire graph to find a node with zero in-degree.
    // Returns int::min if no node with zero in-degree found.
    int findNodeWithZeroInDegree() {
      std::set<int> indegrees;
      for (const std::list<int>& vadj : adj) {
        for (const int& v : vadj) {
          if (indegrees.find(v) == indegrees.end())
            indegrees.insert(v);
        }
      }

      // If all of the nodes have incoming edges then there is cycle in the graph.
      if (indegrees.size() >= adj.size())
        throw std::exception("Cycle in DAG");

      // If no nodes in graph
      if (indegrees.size() == 0)
        return std::numeric_limits<int>::min();

      for (auto i = 0; i < adj.size(); i++) {
        if (indegrees.find(i) == indegrees.end()) {
          return i;
        }
      }

      return std::numeric_limits<int>::min();
    }
  };

  using namespace Microsoft::VisualStudio::CppUnitTestFramework;

  TEST_CLASS(TopologicalSortDAGTests) {
  public:
    TEST_METHOD(WhenSortEmpty_ExpectEmptyReturned) {
      Graph graph(100);
      auto sorted = graph.topologicalSort();
      Assert::AreEqual(size_t(0), sorted.size());
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

    TEST_METHOD(WhenCycle_ExpectException) {
      Graph graph(3);
      graph.insert(2, 1);
      graph.insert(1, 0);
      graph.insert(0, 2);
      std::function<std::vector<int>(void)> f1 = std::bind(&Graph::topologicalSort, graph);
      Assert::ExpectException<std::exception>(f1);
    }
  };
}
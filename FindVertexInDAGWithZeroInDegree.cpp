
#include "CppUnitTest.h"
#include <cassert>
#include <list>
#include <vector>
#include <limits>
#include <set>
#include <functional>

// Find a vertex with zero in-degree in a directed acyclic graph 
// Time Complexity: O(V + E) 
// Space Complexity: O(V)

namespace FindVertexInDAGWithZeroInDegree {

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

      // If no nodes in graph
      if (indegrees.size() == 0)
        return std::numeric_limits<int>::min();

      // If all of the nodes have incoming edges then there is cycle in the graph.
      if (indegrees.size() >= adj.size())
        throw std::exception("Cycle in DAG");

      for (auto i = 0; i < adj.size(); i++) {
        if (indegrees.find(i) == indegrees.end()) {
          return i;
        }
      }

      return std::numeric_limits<int>::min();
    }
  
  private:
    std::vector<std::list<int>> adj;
  };

  using namespace Microsoft::VisualStudio::CppUnitTestFramework;

  TEST_CLASS(FindVertexInDAGWithZeroInDegreeTests) {
  public:
    TEST_METHOD(WhenEmpty_ExpectMinReturned) {
      Graph graph(0);
      auto result = graph.findNodeWithZeroInDegree();
      Assert::AreEqual(std::numeric_limits<int>::min(), result);
    }

    TEST_METHOD(WhenLinear_ExpectTopReturned) {
      // 4 -> 3 -> 2 -> 1 -> 0
      Graph graph(5);
      graph.insert(3, 2);
      graph.insert(1, 0);
      graph.insert(2, 1);
      graph.insert(4, 3);
      auto result = graph.findNodeWithZeroInDegree();;
      Assert::AreEqual(4, result);
    }

    TEST_METHOD(WhenCycle_ExpectException) {
      Graph graph(3);
      graph.insert(2, 1);
      graph.insert(1, 0);
      graph.insert(0, 2);
      std::function<int(void)> f = std::bind(&Graph::findNodeWithZeroInDegree, graph);
      Assert::ExpectException<std::exception>(f);
    }
  };
}
// A directed graph is strongly connected if there is a path between all
// pairs of vertices.  A strongly connected component is a maximal connected
// subgraph.
//
// Tarjan's algorithm finds the strongly connected components of a graph using
// a single DFS traversal.
//
// Time Complexity: O(E + V)
// Space Complexity: O(V)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StronglyConnectedComponentsInDirectedGraphTarjansAlgorithm {

  class Graph {
    public:
      Graph(int numVertices) {
        _adjacency.resize(numVertices);
      }

      Graph(Graph& other) = delete;
      Graph& operator=(Graph& other) = delete;

      int getNumVertices() const { return _adjacency.size(); }

      void addEdge(int u, int v) {
        assert(u < getNumVertices());
        assert(v < getNumVertices());
        _adjacency[u].emplace_back(v);
      }

      // Returns a partition of the graph's vertices into the graph's strongly
      // connected components.  Each vertex of the graph will appear in exactly one
      // of the strongly connected components.
      vector<vector<int>> findStronglyConnectedComponents() {
        vector<int> disc(getNumVertices(), numeric_limits<int>::min());
        vector<int> low(getNumVertices(), numeric_limits<int>::min());

        // Provides O(1) check if member is on stack.
        vector<bool> stackMember(getNumVertices(), false);

        // Stores the nodes that have been explored by are not yet part of the strongly connected component.
        stack<int> s;

        // Find DFS tree of each unvisited vertex.
        vector<vector<int>> results;
        for (auto u = 0; u < getNumVertices(); u++) {
          if (disc[u] < 0) {
            // u is not already part of any discovered sub-graphs so find the 
            // strongly connected subgraph with u as the root.
            int step = 0;
            findStronglyConnectedComponents(u, disc, low, s, stackMember, step, results);
          }
        }

        return move(results);
      }

    private:
      vector<vector<int>> _adjacency;

      // Find strongly connected components of u's subgraph using depth first search.
      void findStronglyConnectedComponents(int u, vector<int>& disc, vector<int>& low, 
        stack<int>& s, vector<bool>& stackMember, int& step, vector<vector<int>>& results) {

        step++;
        disc[u] = step;
        low[u] = step;

        s.push(u);
        stackMember[u] = true;

        // check all adjacent vertices
        for (const auto& v : _adjacency[u]) {

          if (disc[v] < 0) {
            // We haven't seen v before so discover its' strongly connected subgraph.
            findStronglyConnectedComponents(v, disc, low, s, stackMember, step, results);
            // Check if the subtree rooted at v has a connection with an ancestor u (has lower discovery step).
            low[u] = min(low[u], low[v]);
          } else if (stackMember[v]) {
            // V is already part of the current strongly connected subgraph so this is a back-link!
            // Update the low value of u if v is a back edge.
            low[u] = min(low[u], disc[v]);
          }
        }

        // If this the root node of the strongly connected subgraph then
        // return the values on the stack.
        if (low[u] == disc[u]) {
          vector<int> subGraph;

          // Pop all nodes that are under root of current subgraph.
          while (s.top() != u) {
            auto w = s.top();
            subGraph.emplace_back(w);
            stackMember[w] = false;
            s.pop();
          }

          // Pop root
          subGraph.emplace_back(u);
          stackMember[u] = false;
          s.pop();

          results.emplace_back(subGraph);
        }
      }
  };

  TEST_CLASS(StronglyConnectedComponentsInDirectedGraphTarjansAlgorithmTests) {
    public:
      TEST_METHOD(WhenOneStronglyConnectedSubgraph_ExpectFound) {
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);
        auto result = graph.findStronglyConnectedComponents();
        Assert::AreEqual(size_t(1), result.size());
        Assert::AreEqual(3, result[0][0]);
        Assert::AreEqual(2, result[0][1]);
        Assert::AreEqual(1, result[0][2]);
        Assert::AreEqual(0, result[0][3]);
      }

      TEST_METHOD(WhenOneStronglyConnectedSubgraphAndSingleNode_ExpectTwoFound) {
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 0);
        auto result = graph.findStronglyConnectedComponents();
        Assert::AreEqual(size_t(2), result.size());
        Assert::AreEqual(2, result[0][0]);
        Assert::AreEqual(1, result[0][1]);
        Assert::AreEqual(0, result[0][2]);

        // 3 is in a subgraph by itself
        Assert::AreEqual(3, result[1][0]);
      }

      TEST_METHOD(WhenTwoDisconnectedStronglyConnectedSubgraphs_ExpectBothFound) {
        Graph graph(4);
        // Subgraph 1
        graph.addEdge(0, 1);
        graph.addEdge(1, 0);
        // Subgraph 2 
        graph.addEdge(2, 3);
        graph.addEdge(3, 2);
        auto result = graph.findStronglyConnectedComponents();
        Assert::AreEqual(size_t(2), result.size());
        // Subgraph 1
        Assert::AreEqual(1, result[0][0]);
        Assert::AreEqual(0, result[0][1]);
        // Subgraph 2 
        Assert::AreEqual(3, result[1][0]);
        Assert::AreEqual(2, result[1][1]);
      }

      TEST_METHOD(WhenThreeConnectedStronglyConnectedSubgraphs_ExpectAll) {
        Graph graph(8);
        // Subgraph 1
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 1);
        // Subgraph 2 
        graph.addEdge(4, 5);
        graph.addEdge(5, 4);
        // Subgraph 3 
        graph.addEdge(6, 7);
        graph.addEdge(7, 6);
        // Link subgraphs together
        graph.addEdge(4, 2);
        graph.addEdge(6, 3);
        graph.addEdge(5, 6);
        auto result = graph.findStronglyConnectedComponents();
        Assert::AreEqual(size_t(4), result.size());
        Assert::AreEqual(0, result[0][0]);
        // Subgraph 1
        Assert::AreEqual(3, result[1][0]);
        Assert::AreEqual(2, result[1][1]);
        Assert::AreEqual(1, result[1][2]);
        // Subgraph 3 
        Assert::AreEqual(7, result[2][0]);
        Assert::AreEqual(6, result[2][1]);
        // Subgraph 2 
        Assert::AreEqual(5, result[3][0]);
        Assert::AreEqual(4, result[3][1]);
      }
  };
}
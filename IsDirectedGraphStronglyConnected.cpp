// Given a directed graph determine if it is strongly connected
// or not.  As strongly connected graph has a path between
// any two arbitrary vertices.
//
// Performs Kosaraju's Strongly Connected Component Algorithm.
// http://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
// Perform a DFS search on both the graph the graph's transpose checking 
// that all nodes can be visited from vertex zero.
// 
// If every node can be reached from vertex zero and every vertex can 
// also reach vertex zero then the graph must be strongly connected.
//
// Time Complexity: O(V + E)
// Space Complexity: O(V + E) for transpose of graph that is created.
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <cassert>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IsDirectedGraphStronglyConnected {

  class Graph {
    public:
      Graph(int numVertices) : _numVertices(numVertices) {
        if (_numVertices <= 0) { throw new exception("Invalid graph size."); }
        _adjacencyList.resize(numVertices);
      }
      
      void addEdge(int u, int v) {
        assert(u < _adjacencyList.size());
        _adjacencyList[u].emplace_back(v);
      }

      bool isStronglyConnectedGraph() {
        return (ableToVisitEveryVertexFromFirstVertex(*this)
          && ableToVisitEveryVertexFromFirstVertex(getTranspose()));
      }

  private:
    int _numVertices;
    vector<vector<int>> _adjacencyList;

    // Perform an O(E + V) DFS visiting vertices reachable from vertex 0.
    void visitAllConnectedNodes(int u, vector<bool>& visited) const {
      // Mark the current node as having been visited.
      visited[u] = true;

      // Visit all unvisited neighbors of current node 
      // marking them and their children as visited.
      for (const auto& v : _adjacencyList[u]) {
        if (!visited[v]) {
          visitAllConnectedNodes(v, visited);
        }
      }
    }

    // Returns the reverse/transpose of this graph.
    Graph getTranspose() {
      Graph transpose(_numVertices);

      for (auto u = 0; u < _adjacencyList.size(); u++) {
        for (const auto& v : _adjacencyList[u]) {
          transpose.addEdge(v, u);
        }
      }

      return move(transpose);
    }

    bool ableToVisitEveryVertexFromFirstVertex(const Graph& graph) {
      // Visit every vertex reachable from the first vertex of the graph.
      vector<bool> visited(_numVertices, false);
      graph.visitAllConnectedNodes(0, visited);

      // Check that we visited all possible nodes during the search
      return find(visited.cbegin(), visited.cend(), false) == visited.cend();
    }
  };

  TEST_CLASS(IsDirectedGraphStronglyConnectedTests) {
    public:
      TEST_METHOD(WhenOneVertex_ExpectStronglyConnected) {
        Graph graph{ 1 };
        Assert::IsTrue(graph.isStronglyConnectedGraph());
      }

      TEST_METHOD(WhenNotStronglyConnectedTwoVertex_ExpectFalse) {
        Graph graph{ 2 };
        graph.addEdge(0, 1);
        Assert::IsFalse(graph.isStronglyConnectedGraph());
      }

      TEST_METHOD(WhenStronglyConnectedTwoVertex_ExpectTrue) {
        Graph graph{ 2 };
        graph.addEdge(0, 1);
        graph.addEdge(1, 0);
        Assert::IsTrue(graph.isStronglyConnectedGraph());
      }

      TEST_METHOD(WhenNotStronglyConnectedThreeVertex_ExpectTrue) {
        Graph graph{ 3 };
        graph.addEdge(1, 2);
        graph.addEdge(2, 0);
        Assert::IsFalse(graph.isStronglyConnectedGraph());
      }

      TEST_METHOD(WhenStronglyConnectedThreeVertex_ExpectTrue) {
        Graph graph{ 3 };
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 0);
        Assert::IsTrue(graph.isStronglyConnectedGraph());
      }
  };
}
// Kosaraju's algorithm to get all strongly connected sub-graphs.
//
// Time Complexity: O(E + V)
// Space Complexity: O(E + V) (Stores the transpose of the graph)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StronglyConnectedComponentsInDirectedGraphKosarajuAlgorithm {

  class Graph {
    public:
      Graph(int numVertices) {
        _adjacency.resize(numVertices);
      }

      Graph(Graph&& other) {
        *this = move(other);
      }

      Graph& operator=(Graph&& other) {
        if (this != &other) {
          _adjacency = move(other._adjacency);
        }
        return *this;
      }

      Graph(Graph& other) = delete; // Remove copy constructor
      Graph& operator=(Graph&) = delete; // Remove assignment operator

      int getNumVertices() { return _adjacency.size(); }

      void addEdge(int u, int v) {
        assert(u < getNumVertices());
        assert(v < getNumVertices());
        _adjacency[u].emplace_back(v);
      }

      // Creates the transpose (reverse) of a graph.
      Graph getTranspose() {
        Graph transpose(getNumVertices());
        for (auto u = 0; u < getNumVertices(); u++) {
          for (const auto& v : _adjacency[u]) {
            transpose.addEdge(v, u);
          }
        }
        return transpose;
      }

      // Performs a depth first search of unvisited nodes.
      void getDepthFirstSearchFromVector(int u, vector<bool>& visited, vector<int>& result) {
        visited[u] = true;
        result.emplace_back(u);

        // Search all adjacent nodes
        for (const auto& v : _adjacency[u]) {
          if (!visited[v]) {
            getDepthFirstSearchFromVector(v, visited, result);
          }
        }
      }

      void visitAllReachableNodes(int u, vector<bool>& visited, stack<int>& s) {
        visited[u] = true;

        // visit all unvisited adjacent nodes
        for (const auto& v: _adjacency[u]) {
          if (!visited[v]) {
            visitAllReachableNodes(v, visited, s);
          }
        }

        // All vertices reachable by u are now visited so push to stack.
        s.emplace(u);
      }

      vector<vector<int>> getStronglyConnectedComponents() {

        // Perform a DFS traversal of all reachable nodes and push the vertex
        // onto the stack after all over it's adjacent vertices are explored.
        vector<bool> visited(getNumVertices(), false);
        stack<int> s;

        for (auto u = 0; u < _adjacency.size(); u++) {
          if (!visited[u]) {
            visitAllReachableNodes(u, visited, s);
          }
        }

        // Reset the visited array for second DFS
        fill(visited.begin(), visited.end(), false);

        // Reverse the directions of all of the arcs of the graph.
        auto transpose = getTranspose();

        // Pop each vertex off the stack, all reachable nodes from the DFS
        // are part of a strongly connected subgraph.
        vector<vector<int>> result;
        while (!s.empty()) {
          auto v = s.top();
          s.pop();

          if (!visited[v]) {
            vector<int> subGraph;
            transpose.getDepthFirstSearchFromVector(v, visited, subGraph);
            result.emplace_back(subGraph);
          }
        }

        return result;
      }

    private:
      vector<vector<int>> _adjacency;
  };

  TEST_CLASS(StronglyConnectedComponentsInDirectedGraphKosarajuAlgorithmTests) {
    public:
      TEST_METHOD(WhenOneStronglyConnectedSubgraph_ExpectFound) {
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);
        auto result = graph.getStronglyConnectedComponents();
        Assert::AreEqual(size_t(1), result.size());
        Assert::AreEqual(0, result[0][0]);
        Assert::AreEqual(3, result[0][1]);
        Assert::AreEqual(2, result[0][2]);
        Assert::AreEqual(1, result[0][3]);
      }
      
      TEST_METHOD(WhenOneStronglyConnectedSubgraphAndSingleNode_ExpectTwoFound) {
        Graph graph(4);
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 0);
        auto result = graph.getStronglyConnectedComponents();
        Assert::AreEqual(size_t(2), result.size());
        // 3 is in a subgraph by itself
        Assert::AreEqual(3, result[0][0]);

        Assert::AreEqual(2, result[1][1]);
        Assert::AreEqual(1, result[1][2]);
        Assert::AreEqual(0, result[1][0]);
      }
      
      TEST_METHOD(WhenTwoDisconnectedStronglyConnectedSubgraphs_ExpectBothFound) {
        Graph graph(4);
        // Subgraph 1
        graph.addEdge(0, 1);
        graph.addEdge(1, 0);
        // Subgraph 2 
        graph.addEdge(2, 3);
        graph.addEdge(3, 2);
        auto result = graph.getStronglyConnectedComponents();
        Assert::AreEqual(size_t(2), result.size());
        // Subgraph 2 
        Assert::AreEqual(2, result[0][0]);
        Assert::AreEqual(3, result[0][1]);
        // Subgraph 1
        Assert::AreEqual(0, result[1][0]);
        Assert::AreEqual(1, result[1][1]);
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
        auto result = graph.getStronglyConnectedComponents();
        Assert::AreEqual(size_t(4), result.size());
        // Subgraph 2 
        Assert::AreEqual(4, result[0][0]);
        Assert::AreEqual(5, result[0][1]);
        // Subgraph 3 
        Assert::AreEqual(6, result[1][0]);
        Assert::AreEqual(7, result[1][1]);
        // Subgraph 1
        Assert::AreEqual(1, result[2][0]);
        Assert::AreEqual(3, result[2][1]);
        Assert::AreEqual(2, result[2][2]);
      }
  };
}
#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <deque>
#include <forward_list>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

/**
 * Given an undirected graph, print all Hamiltonian paths present in it. The
 * Hamiltonian path in an undirected or directed graph is a path that visits
 * each vertex exactly once.
 *
 */

struct Edge {
  int src, dest;
};

class Graph {
public:
  vector<vector<int>> adj_list;
  Graph(vector<Edge> const &edges, int n) {
    adj_list.resize(n);

    for (Edge edge : edges) {
      int src = edge.src;
      int dest = edge.dest;

      adj_list[src].push_back(dest);
      adj_list[dest].push_back(src);
    }
  }
};

void print_path(vector<int> const &path) {
  for (int i : path) {
    cout << i << ' ';
  }
  cout << endl;
}

void hamiltonian_paths(Graph const &graph, int v, vector<bool> &visited,
                      vector<int> &path, int n) {
  if (path.size() == n) {
    print_path(path);
    return;
  }

  for (int w : graph.adj_list[v]) {
    // process only unvisited vertices as the Hamiltonian path visit each vertex exactly once
    if (!visited[w]) {
      visited[w] = true;
      path.push_back(w);
      // check if adding vertex `w` to the path leads to the solution or not
      hamiltonian_paths(graph, w, visited, path, n);
      // backtrack
      visited[w] = false;
      path.pop_back();
    }
  }
}

void find_hamiltonian_paths(Graph const &graph, int n) {
  for (int start = 0; start < n; start++) {
    vector<int> path;
    path.push_back(start);

    vector<bool> visited(n);
    visited[start] = true;

    hamiltonian_paths(graph, start, visited, path, n);
  }
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  vector<Edge> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}};
  int n = 4;
  Graph graph(edges, n);

  find_hamiltonian_paths(graph, n);

  return 0;
}

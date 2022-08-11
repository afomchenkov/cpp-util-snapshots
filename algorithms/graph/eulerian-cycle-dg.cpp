#include <new>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>
#include <future>
#include <utility>
#include <tuple>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>
#include <functional>
#include <regex>
#include <bitset>
#include <iostream>

using namespace std;

/**
 * Given a directed graph, check if it is possible to construct a cycle that
 * visits each edge exactly once, i.e., check whether the graph has an Eulerian cycle or not.
 *
 * An Eulerian trail (or Eulerian path) is a path that visits every edge in a graph exactly once.
 * An Eulerian circuit (or Eulerian cycle) is an Eulerian trail that starts and ends on the same vertex.
 * A directed graph has an Eulerian cycle if and only if
 *   - Every vertex has equal in-degree and out-degree, and
 *   - All of its vertices with a non-zero degree belong to a single strongly connected component.
 *
 * The graph is strongly connected if it contains a directed path from u to v and a directed
 * path from v to u for every pair of vertices (u, v).
 */

struct Edge
{
  int src, dest;
};

class Graph
{
public:
  vector<vector<int>> adj_list;
  vector<int> in; // in-degree of each vertex in the graph
  Graph(int n, vector<Edge> const &edges = {})
  {
    adj_list.resize(n);
    in.resize(n);
    for (auto &edge : edges)
    {
      add_edge(edge.src, edge.dest);
    }
  }

  void add_edge(int u, int v)
  {
    adj_list[u].push_back(v);
    in[v]++;
  }
};

void DFS(Graph const &graph, int u, vector<bool> &visited)
{
  visited[u] = true;
  for (int v : graph.adj_list[u])
  {
    if (!visited[v])
    {
      DFS(graph, v, visited);
    }
  }
}

// create transpose of a graph, i.e., the same graph with the direction of every edge reversed
Graph build_transpose(Graph const &graph, int n)
{
  Graph g(n);

  for (int u = 0; u < n; u++)
  {
    // for every edge (u, v), create a reverse edge (v, u) in the transpose graph
    for (int v : graph.adj_list[u])
    {
      g.add_edge(v, u);
    }
  }
  return g;
}

// check if all vertices of a graph with a non-zero degree are visited
bool isVisited(Graph const &graph, const vector<bool> &visited)
{
  for (int i = 0; i < visited.size(); i++)
  {
    if (graph.adj_list[i].size() && !visited[i])
    {
      return false;
    }
  }
  return true;
}

// check if all vertices with a non-zero degree in a graph belong to a
// single strongly connected component using Kosaraju’s algorithm
bool is_sc(Graph const &graph, int n)
{
  vector<bool> visited(n);
  int i;
  for (i = 0; i < n; i++)
  {
    if (graph.adj_list[i].size())
    {
      DFS(graph, i, visited);
      break;
    }
  }
  // return false if DFS couldn't visit all vertices with a non-zero degree
  if (!isVisited(graph, visited))
  {
    return false;
  }

  fill(visited.begin(), visited.end(), false);
  Graph g = build_transpose(graph, n);

  // perform DFS on the transpose graph using the same starting vertex as used in the previous DFS call
  DFS(g, i, visited);
  // return true if second DFS also explored all vertices with a non-zero degree
  return isVisited(g, visited);
}

// check if a directed graph has an Eulerian cycle
bool has_eulerian_cycle(Graph const &graph, int n)
{
  for (int i = 0; i < n; i++)
  {
    if (graph.adj_list[i].size() != graph.in[i])
    {
      return false;
    }
  }

  // check if all vertices with a non-zero degree belong to a single strongly connected component
  return is_sc(graph, n);
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{
  vector<Edge> edges = {
      {0, 1}, {1, 2}, {2, 3}, {3, 1}, {1, 4}, {4, 3}, {3, 0}};
  int n = 5;

  Graph graph(n, edges);
  if (has_eulerian_cycle(graph, n))
  {
    cout << "The graph has an Eulerian cycle" << endl;
  }
  else
  {
    cout << "The Graph does not contain Eulerian cycle" << endl;
  }

  return 0;
}

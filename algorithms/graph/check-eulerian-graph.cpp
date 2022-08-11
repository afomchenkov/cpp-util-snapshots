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
 * Given an undirected graph, check whether it has an Eulerian path or not.
 * In other words, check if it is possible to construct a path that visits each edge exactly once.
 *
 * > Eulerian trail
 * An {{Eulerian trail}} is a path that visits every edge in a graph exactly once.
 * An undirected graph has an Eulerian trail if and only if:
 *    - Exactly zero or two vertices have odd degree, and
 *    - All of its vertices with a non-zero degree belong to a single connected component.
 *
 * > Eulerian circuit
 * An {{Eulerian circuit}} is an Eulerian trail that starts and ends on the same vertex,
 * i.e., the path is a cycle. An undirected graph has an Eulerian cycle if and only if:
 *    - Every vertex has an even degree, and
 *    - All of its vertices with a non-zero degree belong to a single connected component.
 *
 * > Semi–Eulerian
 * A graph that has an {{Eulerian trail}} but not an Eulerian circuit is called Semi–Eulerian.
 * An undirected graph is Semi–Eulerian if and only if:
 *     - Exactly two vertices have odd degree, and
 *     - All of its vertices with a non-zero degree belong to a single connected component.
 *
 */

struct Edge
{
  int src, dest;
};

class Graph
{
public:
  vector<vector<int>> adj_list;
  Graph(vector<Edge> const &edges, int n)
  {
    adj_list.resize(n);
    for (auto &edge : edges)
    {
      adj_list[edge.src].push_back(edge.dest);
      adj_list[edge.dest].push_back(edge.src);
    }
  }
};

void DFS(Graph const &graph, int v, vector<bool> &visited)
{
  visited[v] = true;
  for (int u : graph.adj_list[v])
  {
    if (!visited[u])
    {
      DFS(graph, u, visited);
    }
  }
}

// check if all vertices with a non-zero degree in a graph belong to a single connected component
bool check_if_connected(Graph const &graph, int n)
{
  vector<bool> visited(n);
  for (int i = 0; i < n; i++)
  {
    if (graph.adj_list[i].size())
    {
      DFS(graph, i, visited);
      break;
    }
  }

  // if a single DFS call couldn't visit all vertices with a non-zero degree,
  // the graph contains more than one connected component
  for (int i = 0; i < n; i++)
  {
    if (!visited[i] && graph.adj_list[i].size() > 0)
    {
      return false;
    }
  }

  return true;
}

// return the total number of vertices with an odd degree in a graph
int count_odd_vertices(Graph const &graph)
{
  int count = 0;
  for (vector<int> list : graph.adj_list)
  {
    if (list.size() & 1)
    {
      count++;
    }
  }
  return count;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{
  vector<Edge> edges = {
      {0, 1}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};
  int n = 5; // total number of nodes in the graph (labelled from 0 to 4)
  Graph graph(edges, n);

  bool is_connected = check_if_connected(graph, n);
  int odd = count_odd_vertices(graph);

  // An Eulerian path exists if all non-zero degree vertices are connected, and zero or two vertices have an odd degree
  if (is_connected && (odd == 0 || odd == 2))
  {
    cout << "The graph has an Eulerian path" << endl;
    // A connected graph has an Eulerian cycle if every vertex has an even degree
    if (odd == 0)
    {
      cout << "The graph has an Eulerian cycle" << endl;
    }
    // The graph has an Eulerian path but not an Eulerian cycle
    else
    {
      cout << "The Graph is Semi–Eulerian" << endl;
    }
  }
  else
  {
    cout << "The Graph is not Eulerian" << endl;
  }

  return 0;
}

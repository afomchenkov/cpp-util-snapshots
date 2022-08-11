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
 * Check if a set of words can be rearranged to form a circle
 *
 * Given a set of words, check if the individual words can be rearranged to form a circle.
 * Two words, X and Y, can be put together in a circle if the last character of X is the
 * same as the first character of Y or vice-versa.
 *
 * Consider the following set of words:
 * [ANT, OSTRICH, DEER, TURKEY, KANGAROO, TIGER, RABBIT, RAT, TOAD, YAK, HYENA]
 *
 * The words can be rearranged as follows to form a circle.
 * Note that, for any pair of consecutive words (X → Y) in the circle,
 * the last character of the word X is the same as the first character of the word Y.
 *
 *   ANT → TIGER → RABBIT → TOAD
 *    ↑                      ↓
 *  HYENA                   DEER
 *    ↑                      ↓
 *  OSTRICH                  RAT
 *    ↑                      ↓
 * KANGAROO   ←  YAK   ←   TURKEY
 *
 * The idea is to build a directed graph and for each word in the given set,
 * add an edge from the first character to the last character in the graph.
 * Now the problem is reduced to finding an Eulerian cycle in the constructed graph.
 * If the graph has an eulerian circuit, then a circle can be formed; otherwise, not.
 * A directed graph has an Eulerian cycle if and only if:
 *
 * - Every vertex has in-degree == out-degree, and
 * - All of its non-isolated vertices belong to a single strongly connected component.
 */

// Define the alphabet size for graph vertices
#define CHAR_SIZE 128

class Graph
{
public:
  vector<vector<int>> adj_list;
  Graph(int n)
  {
    adj_list.resize(n);
  }
  void add_edge(int u, int v)
  {
    adj_list[u].push_back(v);
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

Graph transpose(Graph const &graph, int n)
{
  Graph g(n);

  for (int u = 0; u < n; u++)
  {
    for (int v : graph.adj_list[u])
    {
      g.add_edge(v, u);
    }
  }
  return g;
}

bool is_visited(Graph const &graph, const vector<bool> &visited)
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

// check if all non-isolated vertices in a graph belong to a single strongly connected component
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

  // return false if DFS could not explore all non-isolated vertices
  if (!is_visited(graph, visited))
  {
    return false;
  }

  // reset the visited vertices array for another DFS call
  fill(visited.begin(), visited.end(), false);
  // create a transpose graph with the direction of every edge reversed
  Graph g = transpose(graph, n);
  // perform DFS on the transpose graph using the same starting vertex `i`
  DFS(g, i, visited);
  // check if the second DFS also explored all non-isolated vertices
  return is_visited(g, visited);
}

// check if a given set of words can be rearranged to form a circle
bool check_arrangement(vector<string> const &words)
{
  // create a directed graph with the same number of nodes as the alphabet size
  Graph graph(CHAR_SIZE);
  // create an empty array to store in-degree for each vertex, assign in-degree 0 to each vertex
  vector<int> in(CHAR_SIZE);
  // process each word
  for (const string &s : words)
  {
    int src = s.front();
    int dest = s.back();
    // add an edge to the graph from the first character to the last character
    graph.add_edge(src, dest);
    // increment the in-degree of the destination vertex by 1
    in[dest]++;
  }

  /**
   * @brief 
   * If the constructed graph has an Eulerian cycle, only
   * then can the given words be rearranged to form a circle
   */

  // 1. check if every vertex has the same in-degree and out-degree
  for (int i = 0; i < CHAR_SIZE; i++)
  {
    if (graph.adj_list[i].size() != in[i])
    {
      return false;
    }
  }
  // 2. check if all non-isolated vertices belong to a single strongly connected component
  return is_sc(graph, CHAR_SIZE);
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{
  vector<string> words = {
      "ANT", "OSTRICH", "DEER", "TURKEY", "KANGAROO",
      "TIGER", "RABBIT", "RAT", "TOAD", "YAK", "HYENA"};

  if (check_arrangement(words))
  {
    cout << "The given words can be rearranged";
  }
  else
  {
    cout << "The given words cannot be rearranged";
  }

  return 0;
}

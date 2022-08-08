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
 * @file dijkstra.cpp
 * @author Aliaksandr Famchankou (afamchankou@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-07-31
 *
 * @copyright Copyright (c) 2022
 *
 * Single-Source Shortest Paths – Dijkstra’s Algorithm
 *
 * Given a source vertex s from a set of vertices V in a weighted digraph where all
 * its edge weights w(u, v) are non-negative, find the shortest path weights d(s, v)
 * from source s for all vertices v present in the graph.
 *
 * Vertex 	Minimum Cost 	Route
 * A —> B 	   4 	         A —> E —> B
 * A —> C 	   6 	         A —> E —> B —> C
 * A —> D 	   5 	         A —> E —> D
 * A —> E 	   3 	         A —> E
 *
 * Pseudo:
 *
 * function Dijkstra(Graph, source)
 *     dist[source] = 0    // Initialization
 *     create vertex set Q
 *
 *     for each vertex v in Graph
 *     {
 *         if v != source
 *         {
 *             dist[v] = INFINITY        // Unknown distance from source to v
 *             prev[v] = UNDEFINED       // Predecessor of v
 *         }
 *         Q.add_with_priority(v, dist[v])
 *     }
 *     while Q is not empty
 *     {
 *         u = Q.extract_min()           // Remove minimum
 *         for each neighbor v of u that is still in Q
 *         {
 *             alt = dist[u] + length(u, v)
 *             if alt < dist[v]
 *             {
 *                 dist[v] = alt
 *                 prev[v] = u
 *                 Q.decrease_priority(v, alt)
 *             }
 *         }
 *     }
 *     return dist[], prev[]
 */


struct Edge
{
  int source, dest, weight;
};

struct Node
{
  int vertex, weight;
};

class Graph
{
public:
  vector<vector<Edge>> adj_list;
  Graph(vector<Edge> const &edges, int n)
  {
    adj_list.resize(n);
    for (Edge const &edge : edges)
    {
      adj_list[edge.source].push_back(edge);
    }
  }
};

void print_path(vector<int> const &prev, int i, int source)
{
  if (i < 0)
  {
    return;
  }
  print_path(prev, prev[i], source);
  if (i != source)
  {
    cout << ", ";
  }
  cout << i;
}

struct comp
{
  bool operator()(const Node &lhs, const Node &rhs) const
  {
    return lhs.weight > rhs.weight;
  }
};

// Run Dijkstra’s algorithm on the given graph
void find_shortest_path(Graph const &graph, int source, int n)
{
  // create a min-heap and push source node having distance 0
  priority_queue<Node, vector<Node>, comp> min_heap;
  min_heap.push({source, 0});

  // set initial distance from the source to `v` as infinity
  vector<int> dist(n, INT_MAX);

  // distance from the source to itself is zero
  dist[source] = 0;

  // boolean array to track vertices for which minimum
  // cost is already found
  vector<bool> done(n, false);
  done[source] = true;

  // stores predecessor of a vertex (to a print path)
  vector<int> prev(n, -1);

  // run till min-heap is empty
  while (!min_heap.empty())
  {
    // Remove and return the best vertex
    Node node = min_heap.top();
    min_heap.pop();

    // get the vertex number
    int u = node.vertex;

    // do for each neighbor `v` of `u`
    for (auto i : graph.adj_list[u])
    {
      int v = i.dest;
      int weight = i.weight;

      // Relaxation step
      if (!done[v] && (dist[u] + weight) < dist[v])
      {
        dist[v] = dist[u] + weight;
        prev[v] = u;
        min_heap.push({v, dist[v]});
      }
    }

    // mark vertex `u` as done so it will not get picked up again
    done[u] = true;
  }

  for (int i = 0; i < n; i++)
  {
    if (i != source && dist[i] != INT_MAX)
    {
      cout << "Path (" << source << " —> " << i << "): Minimum cost = "
           << dist[i] << ", Route = [";
      print_path(prev, i, source);
      cout << "]" << endl;
    }
  }
}

int main()
{
  // initialize edges as per the above diagram
  // (u, v, w) represent edge from vertex `u` to vertex `v` having weight `w`
  vector<Edge> edges =
      {
          {0, 1, 10}, {0, 4, 3}, {1, 2, 2}, {1, 4, 4}, {2, 3, 9}, {3, 2, 7}, {4, 1, 1}, {4, 2, 8}, {4, 3, 2}};

  // total number of nodes in the graph (labelled from 0 to 4)
  int n = 5;

  // construct graph
  Graph graph(edges, n);

  // run the Dijkstra’s algorithm from every node
  for (int source = 0; source < n; source++)
  {
    find_shortest_path(graph, source, n);
  }

  return 0;
}
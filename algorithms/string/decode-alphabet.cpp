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
 * Given a dictionary of random origin language where the words are arranged alphabetically,
 * find the correct order of alphabets in the language.
 *
 * Input: dictionary { ¥€±, €±€, €±‰ð, ðß, ±±ð, ±ßß }
 * Output: The correct order of alphabets in the language is {¥ € ‰ ð ± ß}.
 *
 * Input: dictionary { ÿ€±š, €€€ß, €€‰ð, ðß, ±ß¥š }
 * Output: The correct order of alphabets in the language is {ÿ € ‰ ð ±}.
 * The alphabets {š, ß, ¥} are not included in the order as they are not properly defined.
 * 
 * ----------------------------------------------------------------------------------------
 * Use topological sort for the alphabet:
 * For example, consider the dictionary { ¥€±, €±€, €±‰ð, ðß, ±±ð, ±ßß } of words.
 * For each of the edges (x —> y) shown below, x should appear before y in the final ordering.
 * ¥ ——> €
 * € ——> ð, ‰
 * ± ——> ß
 * ð ——> ±
 * If we perform topological sorting on the above graph, we get the correct order of
 * alphabets in the ancient language: { ¥ € ‰ ð ± ß } or { ¥ € ð ± ß ‰ }.
 */

// the maximum number of alphabets in the dictionary
#define N 100

class Graph
{
public:
  vector<unordered_set<int>> adj_list;
  Graph()
  {
    adj_list.resize(N);
  }
};

// Perform DFS on the graph and set the departure time of all vertices of the graph
void DFS(Graph const &graph, int v, vector<bool> &discovered, vector<int> &departure, int &time)
{
  // mark the current node as discovered
  discovered[v] = true;
  // set the arrival time of vertex `v`
  time++;
  // do for every edge `v —> u`
  for (int u : graph.adj_list[v])
  {
    // if `u` is not yet discovered
    if (!discovered[u])
    {
      DFS(graph, u, discovered, departure, time);
    }
  }
  // ready to backtrack - set departure time of vertex `v`
  departure[time] = v;
  time++;
}

// Utility function to perform topological sort on a given DAG
void topological_sort(Graph const &graph, unordered_map<int, string> &map)
{
  // `departure[]` stores the vertex number using departure time as an index
  vector<int> departure(2 * N, -1);

  /* If we had done it the other way around, i.e., fill the array
     with departure time using vertex number as an index, we would
     need to sort it later */

  // to keep track of whether a vertex is discovered or not
  vector<bool> discovered(N);
  int time = 0;

  // perform DFS on all undiscovered connected vertices
  for (int i = 0; i < N; i++)
  {
    if (!discovered[i] && graph.adj_list[i].size() != 0)
    {
      DFS(graph, i, discovered, departure, time);
    }
  }

  cout << "The correct order of alphabets in the language is ";

  // Print the vertices in order of their decreasing
  // departure time in DFS, i.e., in topological order
  for (int i = 2 * N - 1; i >= 0; i--)
  {
    if (departure[i] != -1)
    {
      cout << map[departure[i]] << " ";
    }
  }
}

void print_graph(Graph const &graph, unordered_map<int, string> &map)
{
  for (int i = 0; i < N; i++)
  {
    // ignore vertices with no outgoing edges
    if (graph.adj_list[i].size() != 0)
    {
      cout << map[i] << " ——> ";
      for (int v : graph.adj_list[i])
      {
        cout << map[v] << " ";
      }
      cout << endl;
    }
  }
  cout << endl;
}

// Utility function to construct an inverse map from the original map to do the reverse lookup in constant time
template <typename K, typename V>
unordered_map<V, K> inverse_map(unordered_map<K, V> &map)
{
  unordered_map<V, K> inv;
  for_each(map.begin(), map.end(),
           [&inv](const pair<K, V> &p)
           {
             inv.insert(make_pair(p.second, p.first));
           });
  return inv;
}

void find_alphabets_order(vector<vector<string>> &dict)
{
  // create an `unordered_map` to map each non-ASCII character present in the given dictionary with a unique integer
  unordered_map<string, int> map;
  int k = 0;

  for (auto word : dict)
  {
    // do for each non-ASCII character of the word
    for (string s : word)
    {
      // if the current character is not present on the map, insert it
      if (map.find(s) == map.end())
      {
        map[s] = k++;
      }
    }
  }

  Graph graph;

  // iterate through the complete dictionary and compare adjacent words for character mismatch
  for (int i = 1; i < dict.size(); i++)
  {
    // previous word in the dictionary
    auto prev = dict[i - 1];
    // current word in the dictionary
    auto curr = dict[i];
    // iterate through both `prev` and `curr` simultaneously and find the first mismatching character
    for (int j = 0; j < prev.size() && j < curr.size(); j++)
    {
      // mismatch found
      if (prev[j] != curr[j])
      {
        // add an edge from the current character of `prev` to the current character of `curr` in the graph
        graph.adj_list[map[prev[j]]].insert(map[curr[j]]);
        break;
      }
    }
  }

  unordered_map<int, string> reverse = inverse_map(map);
  // print_graph(graph, reverse);
  topological_sort(graph, reverse);
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  // an dictionary containing words ¥€±, €±€, €±‰ð, ðß, ±±ð, ±ßß individual characters of each word
  // are stored as a string since they are non-ASCII
  vector<vector<string>> dict{
      {"¥", "€", "±"},
      {"€", "±", "€"},
      {"€", "±", "‰", "ð"},
      {"ð", "ß"},
      {"±", "±", "ð"},
      {"±", "ß", "ß"}};

  find_alphabets_order(dict);

  return 0;
}
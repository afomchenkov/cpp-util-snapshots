#include <cstdio>
#include <stdexcept>

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
 * Given a dictionary of ancient origin where the words are arranged
 * alphabetically, find the correct order of alphabets in the ancient language.
 *
 * Input:  Ancient dictionary { ¥€±, €±€, €±‰ð, ðß, ±±ð, ±ßß }
 * Output: The correct order of alphabets in the ancient language is {¥ € ‰ ð ±
 * ß}.
 *
 * Since the input is small, more than one ordering is possible. Another such
 * ordering is {¥ € ð ± ß ‰}.
 *
 *
 *
 * If we carefully analyze the problem, we can see that it is a variation of
 * Topological sorting of a DAG. A topological sorting of a directed acyclic
 * graph is a linear ordering of its vertices such that for every directed edge
 * (u —> v) from vertex u to vertex v, u comes before v in the ordering.
 *
 * For example, consider the dictionary { ¥€±, €±€, €±‰ð, ðß, ±±ð, ±ßß } of
 * ancient words. For each of the edges (x —> y) shown below, x should appear
 * before y in the final ordering. ¥ —> € € —> ð, ‰ ± —> ß ð —> ±
 *
 * If we perform topological sorting on the above graph, we get the correct
 * order of alphabets in the ancient language: {¥ € ‰ ð ± ß} or {¥ € ð ± ß ‰}.
 *
 * The idea is to iterate through the complete dictionary and compare adjacent
 * words for a character mismatch. If a mismatch between adjacent words is seen,
 * insert such a pair into a graph. The resultant graph is a DAG since all words
 * in the dictionary are arranged alphabetically. Since the graph has no
 * directed cycles, perform topological sorting on it, resulting in the correct
 * order of alphabets in the ancient language.
 */

#define N 100

class Graph {
public:
  vector<unordered_set<int>> adj_list;
  Graph() { adj_list.resize(N); }
};

void DFS(Graph const &graph, int v, vector<bool> &discovered,
         vector<int> &departure, int &time) {
  discovered[v] = true;
  time++;
  // do for every edge `v —> u`
  for (int u : graph.adj_list[v]) {
    if (!discovered[u]) {
      DFS(graph, u, discovered, departure, time);
    }
  }
  departure[time] = v;
  time++;
}

void do_topological_sort(Graph const &graph, unordered_map<int, string> &map) {
  vector<int> departure(2 * N, -1);
  vector<bool> discovered(N);
  int time = 0;

  for (int i = 0; i < N; i++) {
    if (!discovered[i] && graph.adj_list[i].size() != 0) {
      DFS(graph, i, discovered, departure, time);
    }
  }
  // Print the vertices in order of their decreasing departure time in DFS in
  // topological order
  for (int i = 2 * N - 1; i >= 0; i--) {
    if (departure[i] != -1) {
      cout << map[departure[i]] << " ";
    }
  }
}

template <typename K, typename V>
unordered_map<V, K> inverse_map(unordered_map<K, V> &map) {
  unordered_map<V, K> inv;
  for_each(map.begin(), map.end(), [&inv](const pair<K, V> &p) {
    inv.insert(make_pair(p.second, p.first));
  });

  return inv;
}

void print_graph(Graph const &graph, unordered_map<int, string> &map) {
  for (int i = 0; i < N; i++) {
    if (graph.adj_list[i].size() != 0) {
      cout << map[i] << " —> ";
      for (int v : graph.adj_list[i]) {
        cout << map[v] << " ";
      }
      cout << endl;
    }
  }
  cout << endl;
}

void find_alphabets_order(vector<vector<string>> &dict) {
  unordered_map<string, int> map;
  int k = 0;

  for (auto word : dict) {
    for (string s : word) {
      if (map.find(s) == map.end()) {
        map[s] = k++;
      }
    }
  }

  Graph graph;
  for (int i = 1; i < dict.size(); i++) {
    auto prev = dict[i - 1];
    auto curr = dict[i];

    for (int j = 0; j < prev.size() && j < curr.size(); j++) {
      if (prev[j] != curr[j]) {
        graph.adj_list[map[prev[j]]].insert(map[curr[j]]);
        break;
      }
    }
  }

  unordered_map<int, string> reverse = inverse_map(map);
  // print_graph(graph, reverse);
  do_topological_sort(graph, reverse);
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  vector<vector<string>> dict{{"¥", "€", "±"},      {"€", "±", "€"},
                              {"€", "±", "‰", "ð"}, {"ð", "ß"},
                              {"±", "±", "ð"},      {"±", "ß", "ß"}};

  find_alphabets_order(dict);

  return 0;
}

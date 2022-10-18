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
 * Given a sorted dictionary of an alien language, find order of characters
 *
 * Input:  words[] = {"baa", "abcd", "abca", "cab", "cad"}
 *
 * Output: Order of characters is 'b', 'd', 'a', 'c'
 * Note that words are sorted and in the given language "baa" comes before
 * "abcd", therefore 'b' is before 'a' in output. Similarly we can find other
 * orders.
 *
 * Input:  words[] = {"caa", "aaa", "aab"}
 * Output: Order of characters is 'c', 'a', 'b'
 *
 * The idea is to create a graph of characters and then find topological sorting
 * of the created graph.
 * 1. create graph G with num of vertices equal to the size of alphabet in the
 * given language
 * 2. do the following for every pair of adjacent words in given sorted array: [
 *   - Let the current pair of words be word1 and word2. One by one compare
 * characters of both words and find the first mismatching characters.
 *   - Create an edge in g from mismatching character of word1 to that of word2.
 * ]
 * 3. do topological sorting of the above created graph.
 */

class Graph {
  int v;
  list<int> *adj;
  void topological_sort_util(int v, bool visited[], stack<int> &st);

public:
  Graph(int v);
  void add_edge(int v, int w);
  void topological_sort();
};

Graph::Graph(int v) {
  this->v = v;
  adj = new list<int>[v];
}

void Graph::add_edge(int v, int w) { adj[v].push_back(w); }

void Graph::topological_sort_util(int v, bool visited[], stack<int> &st) {
  visited[v] = true;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    if (!visited[*i]) {
      topological_sort_util(*i, visited, st);
    }
  }

  st.push(v);
}

void Graph::topological_sort() {
  stack<int> Stack;

  bool *visited = new bool[v];
  for (int i = 0; i < v; i++) {
    visited[i] = false;
  }

  for (int i = 0; i < v; i++) {
    if (visited[i] == false) {
      topological_sort_util(i, visited, Stack);
    }
  }

  while (Stack.empty() == false) {
    cout << (char)('a' + Stack.top()) << " ";
    Stack.pop();
  }
}

int _min(int x, int y) { return (x < y) ? x : y; }

void print_order(string words[], int n, int alpha) {
  Graph g(alpha);
  for (int i = 0; i < n - 1; i++) {
    string word1 = words[i], word2 = words[i + 1];

    for (int j = 0; j < _min(word1.length(), word2.length()); j++) {
      if (word1[j] != word2[j]) {
        g.add_edge(word1[j] - 'a', word2[j] - 'a');
        break;
      }
    }
  }

  g.topological_sort();
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  string words[] = {"caa", "aaa", "aab"};
  print_order(words, 3, 3);
  return 0;
}

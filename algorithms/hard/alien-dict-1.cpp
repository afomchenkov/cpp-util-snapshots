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
 * Three is a new alien language which uses the latin alphabet. However, the order among letters ar unknown,
 * and we receive a list of non-empty words from the dictionary, where words are sorted lexicographically by
 * the rules of this new language. Derive the order of letters in this language.
 *
 * Input = [
 *  "wrt",
 *  "wrf",
 *  "er",
 *  "ett",
 *  "rftt"
 * ]
 * Output: "wertf"
 *
 * Input = ["z" , "x"], Output = "zx"
 * Input = ["z", "x", "z"], Output = ""
 */

class Node {
public:
  char c;
  int parentCount;
  vector<char> children;
};

void addOrder(char p, char c, const vector<Node*> &graph) {
  Node* parent = graph[p - 'a'];
  Node* child = graph[c - 'a'];
  child->parentCount++;
  parent->children.push_back(c);
}

void processColumn(
  int col,
  vector<vector<int>> currentGroups,
  vector<vector<int>> &nextGroups,
  vector<string> &dict
) {
  if (currentGroups.empty()) {
    return;
  }
  int beginGroup = -1;

  for (vector<int> &g : currentGroups) {
    vector<int> group;
    beginGroup = g[0];

    for (int start = g[0]; start <= g[1]; ++start) {
      if (dict[start][col] == dict[start + 1][col]) {
        continue;
      }
      if (col >= dict[start].size() || col >= dict[start + 1].size()) {
        continue;
      }

      addOrder(dict[start][col], dict[start + 1][col], graph);
      group = { begin_group, start };
      nextGroups.push_back(group);
      beginGroup = start + 1;
    }
  }
  nextGroups.push_back({ beginGroup, dict.size() - 1 });
}


// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  return 0;
}

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
 * Given a DAG and two nodes S, E, design a solution to find out
 * whether there is a route from S to E
 * 
 * Solution: DFS or BFS
 * BFS - find shortest path
 * DFS - traverse one adjacent node deeply
 */

enum class State
{
  Unvisited,
  Visited,
  Visiting
};

struct Node {
  string name;
  vector<Node*> children; // adjacent nodes
  State state;
};

struct Graph {
  vector<Node*> nodes;
};

bool search(Graph* g, Node* start, Node* end) {
  if (start == end) {
    return true;
  }

  queue<Node*> q;

  for (auto u : g->nodes) {
    u->state = State::Unvisited;
  }
  start->state = State::Visiting;
  q.push(start);

  Node* u;
  while (!q.empty()) {
    u = q.front();
    q.pop();

    if (u != nullptr) {
      for (auto v : u->children) {
        if (v->state == State::Unvisited) {
          if (v == end) {
            return true;
          } else {
            v->state = State::Visiting;
            q.push(v);
          }
        }
      }

      u->state = State::Visited;
    }
  }
  return false;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  auto graph = new Graph();
  // assign nodes

  return 0;
}
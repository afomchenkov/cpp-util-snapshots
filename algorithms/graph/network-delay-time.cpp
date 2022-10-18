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

#define INF = INT_MAX

/**
 * You are given a network of n nodes, labeled from 1 to n. You are also given times, a list
 * of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node,
 * vi is the target node, and wi is the time it takes for a signal to travel from source to target.
 *
 * Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible
 * for all the n nodes to receive the signal, return -1.
 *
 * Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
 * Output: 2
 */

int network_delay_time(vector<vector<int>> &times, int n, int k)
{
  map<int, vector<pair<int, int>>> edges;
  for (auto edge : times)
  {
    int u = edge[0];
    int v = edge[1];
    int w = edge[2];

    if (edges.count(u))
    {
      edges[u].push_back(pair(v, w));
    }
    else
    {
      edges[u] = {{v, w}};
    }
  }

  auto compare = [](auto a, auto b)
  { return a.first > b.first; };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> min_heap(compare);
  min_heap.push(pair(0, k));
  set<int> visited;
  int t = 0;

  while (!min_heap.empty())
  {
    auto min_path = min_heap.top();
    min_heap.pop();
    int w1 = min_path.first;
    int n1 = min_path.second;

    if (visited.count(n1))
    {
      continue;
    }
    visited.insert(n1);
    t = max(t, w1);

    for (auto next : edges[n1])
    {
      int n2 = next.first;
      int w2 = next.second;

      if (!visited.count(n2))
      {
        min_heap.push({w1 + w2, n2});
      }
    }
  }

  return visited.size() == n ? t : -1;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{
  priority_queue<int, vector<int>, greater<int>> q;

  for (int i = 0; i != 10; ++i)
  {
    q.push(rand() % 10);
  }

  cout << "Min-heap, popped one by one: ";
  while (!q.empty())
  {
    cout << q.top() << ' ';
    q.pop();
  }
  cout << endl;

  return 0;
}
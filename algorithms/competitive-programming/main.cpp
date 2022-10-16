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
#include <ctime>

using namespace std;

/**
 * Complexity worst cases
 *
 *     N   |   Worst case AC    |   Example
 * --------------------------------------------------
 *   < 11     O(!N), O(N^6)        Permutation
 *   < 18     O(2^N x N^2)         DP + TSP
 *   < 22     O(2^N x N)
 *   < 100    O(N^4)
 *   < 400    O(N^3)               Floyd-Warshall
 *   < 2k     O(N^2log2N)          Nested Loops
 *   < 10k    O(N^2)               Nested Loops, Bubble sort
 *   < 1m     O(NlogN)             Merge Sort
 *   <= 100m  O(N), O(logN), O(1)  Linear search, etc.
 * --------------------------------------------------
 *
 *
 * STL containers
 *
 * Sequence        |     Associative      |    Unordered       | Containers
 * Containers      |     Containers       |    Associative     | Adaptors
 *                 |                      |    Containers      |
 * ----------------------------------------------------------------------------
 * Array           |     Set              | Unordered Set      | Stack
 * ----------------------------------------------------------------------------
 * Vector          |     Map              | Unordered Map      | Queue
 * ----------------------------------------------------------------------------
 * Deque           |     Multiset         | Unordered Multiset | Priority Queue
 * ----------------------------------------------------------------------------
 * Forward List    |     Multimap         | Unordered Multimap |
 * ----------------------------------------------------------------------------
 * List            |                      |                    |
 * ----------------------------------------------------------------------------
 */

class Compare
{
public:
  bool operator()(int a, int b)
  {
    return a > b;
  }
};


// g++ -std=c++0x -pthread -o out ./algorithms/competitive-programming/main.cpp; ./out
int main()
{

  // check how much time an axecution takes - timestamp
  // auto start_time = clock();
  //  > do smth
  // auto end_time = clock();
  // auto diff = end_time - start_time;

  // array container -- all STL conatiners pass-by-value
  array<int, 6> arr1 = {1, 2, 3, 4, 5, 6}; // array object
  int len1 = arr1.size();

  vector<int> arr2 = {1, 2, 3, 4, 10};
  int len2 = arr2.size();

  deque<int> q1 = {1, 2, 3, 4, 5};
  // pop_back, pop_front, push_back, push_front, resize, size
  // at, back, begin, capacity, clear, empty, end, erase, front, insert

  stack<string> st1;
  st1.push("C++");
  st1.push("Java");
  st1.push("JavaScript");
  st1.push("Python");

  queue<int> q2;
  q2.push(2);
  q2.push(4);
  q2.push(1);
  q2.push(5);

  // priority queue as a Heap
  int arr[] = {10, 15, 20, 13, 6, 90};
  int n = sizeof(arr) / sizeof(int);
  priority_queue<int, vector<int>, greater<int>> heap; // internally built as a tree
  // greater<int> - in-built comparator
  for (int x : arr)
  {
    heap.push(x);
  }

  while (!heap.empty())
  {
    cout << heap.top() << "\n";
    heap.pop();
  }
  
  return 0;
}

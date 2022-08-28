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
 * The bounded knapsack problem is like the 0/1 knapsack problem, except in this we are also given a count
 * for each item. In other words, each item has a count si associated with it and we can select an item si
 * times (1 ≤ i ≤ N).
 *
 *
 * The solution is simple. Let dp[i][j] be the minimum count of ith item that has to be used to get a total
 * cost of j while using some number (possibly 0) of first i items. If a total cost of j can not be obtained
 * using first i items, then dp[i][j] =  - 1. The following code is used to calculate dp[i][j]
 *
 * Here, c[i] is the cost and s[i] is the count for ith item. Also, dp[0][j] =  - 1 for all 1 ≤ j ≤ W
 * and dp[0][0] = 0. Time complexity is O(NW).
 *
 * if (dp[i-1][j] >= 0)
 *    dp[i][j] = 0;
 * else if (dp[i][j - c[i]] >= 0 and dp[i][j - c[i]] < s[i])
 *   dp[i][j] = dp[i][j - c[i]] + 1;
 * else
 *   dp[i][j] = -1;
 */

int bounded_knapsack() {
  return 0;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {

  return 0;
}

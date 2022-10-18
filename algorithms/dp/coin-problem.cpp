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
 * Given a set of coin values coins={c1,c2,...,ck} and a target sum of money n,
 * the task is to form the sum n using as few coins as possible.
 * 
 * - recursive problem is: what is the smallest number of coins required to form a sum x?
 * 
 * Example:
 *  coins = [1, 3, 4], target = 10
 * Recursive formula:
 *  solve(x) = min(
 *        solve(x − 1) + 1,
 *        solve(x − 3) + 1,
 *        solve(x − 4) + 1
 *  )
 */

// not efficient, exponential num of ways
int solve(vector<int>& coins, int x) {
  if (x < 0) return INT_MAX;
  if (x == 0) return 0;

  int best = INT_MAX;
  for (auto c : coins) {
    best = min(best, solve(coins, x - c) + 1);
  }

  return best;
}

vector<int> form_sum(vector<int>& coins, int target) {
  return {};
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  return 0;
}
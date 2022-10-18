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

// top-down solution
int dp_topdown(vector<map<int, int>>& cache, vector<int>& prices, int fee, int pos, bool bought) {
  if (pos == prices.size()) {
    return 0;
  }

  // TODO: handle cache
  int current_price = prices[pos];
  int max_profit = 0;
  if (!bought) {
    auto here1 = dp_topdown(cache, prices, fee, pos + 1, true);
    // buy stock
    max_profit = max(max_profit, here1 - current_price - fee);
  } else {
    auto here2 = dp_topdown(cache, prices, fee, pos + 1, false);
    // sell stock
    max_profit = max(max_profit, here2 + current_price);
  }
  // do nothing
  max_profit = max(max_profit, dp_topdown(cache, prices, fee, pos + 1, bought));

  return max_profit;
}

// bottom-up solution
// LRU cache can be represented in the following table way:
// ---------------------
//    x  | 0 1 2 3 4 5 6
// ---------------------
// true  | 0 0 0 0 0 0 0
// false | 0 0 0 0 0 0 0
int dp_bottomup(vector<int> prices, int fee) {
  int len = prices.size();
  vector<vector<int>> dp(len + 1, vector<int>(2, 0));
  // reverse(prices.begin(), prices.end());

  for (int pos = len - 1; pos >= 0; pos--) {
    for (bool bought : { true, false }) {
      int max_profit = 0;

      if (!bought) {
        // buy stock
        max_profit = max(max_profit, dp[pos + 1][1] - prices[pos] - fee);
      } else {
        // sell stock
        max_profit = max(max_profit, dp[pos + 1][0] + prices[pos]);
      }

      // do nothing
      max_profit = max(max_profit, dp[pos + 1][bought]);
      dp[pos][bought] = max_profit;
    }
  }

  return dp[0][0];
}

// The time complexity: O(N)
// Space complexity:    O(1)
int dp_bottomup_optimized(vector<int> prices, int fee) {
  int len = prices.size();
  vector<int> dp{0, 0};

  for (int pos = len - 1; pos >= 0; pos--) {
    auto dp_old = dp;
    dp = {0, 0};

    for (bool bought : { true, false }) {
      int max_profit = 0;

      if (!bought) {
        // buy stock
        max_profit = max(max_profit, dp_old[1] - prices[pos] - fee);
      } else {
        // sell stock
        max_profit = max(max_profit, dp_old[0] + prices[pos]);
      }

      max_profit = max(max_profit, dp_old[bought]);
      dp[bought] = max_profit;
    }
  }

  return dp[0];
}


int max_profit(vector<int>& nums, int fee) {
  // lru_cache: false - 0, true - 1
  vector<map<int, int>> cache(2);
  // auto result = dp_topdown(cache, nums, fee, 0, false);
  // auto result = dp_bottomup(nums, fee);
  auto result = dp_bottomup_optimized(nums, fee);

  return result;
}


// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  vector<int> prices{1, 3, 2, 8, 4, 9};
  int fee = 2;
  auto profit = max_profit(prices, fee);

  cout << "Profit: " << profit << endl;

  return 0;
}
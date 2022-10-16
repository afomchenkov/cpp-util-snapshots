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
 * Given n weights having a certain value put these weights in a knapsack with a
 * given capacity (maxWeight). The total weight of the knapsack after adding
 * weights must remain smaller than or equal to capacity(maxWeight). The goal
 * here is to find possible maximum total value in the knapsack.
 *
 * - Any weight can be selected multiple times i.e. repetitions are allowed.
 */

// Recursive approach
// time: O(n * maxWeight * maxWeight)
// space: O(n * maxWeight)
int rec_helper(int curWeightSum, int i, int n, int wt[], int val[],
               int maxWeight, int **dp) {
  if (i == n) {
    return 0;
  }

  if (dp[i][curWeightSum] != -1) {
    return dp[i][curWeightSum];
  }

  dp[i][curWeightSum] =
      rec_helper(curWeightSum, i + 1, n, wt, val, maxWeight, dp);

  if (curWeightSum + wt[i] <= maxWeight) {
    dp[i][curWeightSum] =
        max(dp[i][curWeightSum], val[i] + rec_helper(curWeightSum + wt[i], i, n,
                                                     wt, val, maxWeight, dp));
  }
  return dp[i][curWeightSum];
}
int unbounded_knapsack(int n, int wt[], int val[], int maxWeight) {
  int **dp = new int *[n];

  for (int i = 0; i < n; i++) {
    dp[i] = new int[maxWeight + 1];

    for (int j = 0; j < maxWeight + 1; j++) {
      dp[i][j] = -1;
    }
  }

  return rec_helper(0, 0, n, wt, val, maxWeight, dp);
}

// Dynamic approach
// Tabulation is done using a one-dimensional array(dp), whose dimension is the
// same as (maxWeight + 1)
// time: O(n * maxWeight)
// spae: O(maxWeight)
int unbounded_knapsack_dp(int n, int wt[], int val[], int maxWeight) {
  int dp[maxWeight + 1];

  for (int i = 0; i < maxWeight + 1; i++) {
    dp[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = wt[i]; j < maxWeight + 1; j++) {
      dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
    }
  }

  return dp[maxWeight];
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  int n = 2;
  int maxWeight = 3;
  vector<int> weights = {2, 1};
  vector<int> values = {1, 1};

  return 0;
}

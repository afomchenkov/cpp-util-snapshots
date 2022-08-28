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
 * given a set of items, each with a weight and a value, determine the number of each item 
 * to include in a collection so that the total weight is less than or equal to a given limit 
 * and the total value is as large as possible.
 */

// Since this is the 0–1 knapsack problem, we can either include an
// item in our knapsack or exclude it, but not include a fraction of
// it, or include it multiple times.
int knapsack_0_1(int weights[], int values[], int n, int limit) {
  vector< vector<int> > mat(n + 1, vector<int>(limit + 1));
  // > A row number i represents the set of all the items from rows 1— i.
  //    For instance, the values in row 3 assumes that we only have items 1, 2, and 3.
  // > A column number j represents the weight capacity of our knapsack. Therefore, the 
  //    values in column 5, for example, assumes that our knapsack can hold 5 weight units.
  for (int r = 0; r < limit + 1; r++) {
    mat[0][r] = 0;
  }
  for (int c = 0; c < n + 1; c++) {
    mat[c][0] = 0;
  }

  for (int item = 1; item <= n; item++) {
    for (int capacity = 1; capacity <= limit; capacity++) {
      int maxValWithoutCurr = mat[item - 1][capacity];
      int maxValWithCurr = 0;

      int weightOfCurr = weights[item - 1];
      if (capacity >= weightOfCurr) {
        maxValWithCurr = values[item - 1];

        int remainingCapacity = capacity - weightOfCurr;
        maxValWithCurr += mat[item - 1][remainingCapacity];
      }

      mat[item][capacity] = max(maxValWithoutCurr, maxValWithCurr);
    }
  }

  return mat[n][limit];
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  int w = 10; // knapsack can hold weight units
  int n = 4; // total items 
  int val[] = { 10, 40, 30, 50 }; // items values
  int wt[] = { 5, 4, 6, 3 }; // items weights

  // We need to compare the maximum value that we can obtain with and without item i, therefore
  // at row i and column j (which represents the maximum value we can obtain there), we 
  // would pick either the maximum value that we can obtain without item i, or the maximum 
  // value that we can obtain with item i, whichever is larger.
  // The maximum value that we can obtain without item i can be found at row i-1, column j.
  auto result = knapsack_0_1(wt, val, n, w);

  return 0;
}

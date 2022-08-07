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
 * Given a set of non-overlapping intervals, insert a new interval into the
 * intervals (merge if necessary)
 *
 * intervals = [[1,3], [6,9]], merge = [2,5] => [[1,5][6,9]]
 * intervals = [[1,2], [3,5], [6,7], [8,10], [12,16]], merge = [4,9] => [[1,2],
 * [3,10], [12,16]]
 */

vector< pair<int, int> > insert(vector< pair<int, int> > &intervals,
                              pair<int, int> &interval) {
  vector< pair<int, int> > result;
  int i = 0;
  // add all intervals ending before newInterval starts
  while (i < intervals.size() && intervals[i].second < interval.first) {
    result.push_back(intervals[i++]);
  }

  // merge all overlapping intervals to one considering newInterval
  pair<int, int> new_interval;
  while (i < intervals.size() && intervals[i].first <= interval.second) {
    new_interval.first = min(interval.first, intervals[i].first);
    new_interval.second = max(interval.second, intervals[i].second);
    i++;
  }
  // add the union of intervals we got
  result.push_back(new_interval);

  // add all the rest
  while (i < intervals.size())
    result.push_back(intervals[i]);

  return result;
}

// g++ -std=c++0x -pthread -o out knuth-morris-pratt.cpp; ./out
int main() { return 0; }
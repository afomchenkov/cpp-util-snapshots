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

// return all possible subsets from integers containing duplicates
void backtrack_dup(vector< vector<int> >& list, vector<int> temp, vector<int> &nums, int start) {
  list.push_back(temp);

  for (int i = start; i < nums.size(); ++i) {
    if (i > start && nums[i] == nums[i - 1]) {
      // skip dupliates
      continue;
    }
    temp.push_back(nums[i]);
    backtrack_dup(list, temp, nums, start + 1);
    temp.pop_back();
  }
}
vector< vector<int> > subsets_dup(vector<int> &nums) {
  vector< vector<int> > list;
  sort(nums.begin(), nums.end());
  vector<int> temp;
  backtrack_dup(list, temp, nums, 0);
  return list;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {

  return 0;
}
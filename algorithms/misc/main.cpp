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

void generate(
    vector<string> &res,
    vector<string> &map,
    string digits,
    string curr,
    int idx)
{
  if (idx == digits.length())
  {
    res.push_back(curr);
    return;
  }

  string letters = map[digits.at(idx) - '0'];
  int n = letters.length();
  for (int i = 0; i < n; ++i)
  {
    generate(res, map, digits, curr + letters.at(i), idx + 1);
  }
}

vector<string> letter_combinations(string digits)
{
  int n = digits.length();
  vector<string> result;
  if (n == 0)
  {
    return result;
  }
  vector<string> map = {
      "",
      "",
      "abc",
      "def",
      "ghi",
      "jkl",
      "mno",
      "pqrs",
      "tuv",
      "wxyz",
  };
  generate(result, map, digits, "", 0);

  return result;
}

int lengthOfLongestSubstring(string s)
{
  int len = s.length();

  int longest = 0;
  map<char, int> dict;
  for (int i = 0, j = 0; i < len; ++i)
  {
    char letter = s.at(i);

    if (dict.count(letter) > 0)
    {
      // reassign max j
      j = max(dict[letter] + 1, j);
    }
    dict[letter] = i;
    longest = max(longest, i - j + 1);
  }

  return longest;
}

void dfs(
    vector<int> &nums,
    vector<vector<int>> &res,
    int start,
    vector<int> current,
    int sum,
    int target)
{
  if (sum == target)
  {
    res.push_back(current);
    return;
  }

  for (int i = start; i < nums.size(); ++i)
  {
    if (i > start && nums[i] == nums[i - 1])
    {
      continue;
    }
    if (nums[i] + sum > target)
    {
      break;
    }

    current.push_back(nums[i]);
    dfs(nums, res, i, current, sum + nums[i], target);
    current.pop_back();
  }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
  vector<vector<int>> result;

  sort(candidates.begin(), candidates.end());
  dfs(candidates, result, 0, {}, 0, target);
  return result;
}

int main()
{

  return 0;
}
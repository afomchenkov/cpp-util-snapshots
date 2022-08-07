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

/**
 * KMP algorithm for pattern searching
 *
 * Given a text[0...n-1] and a pattern pat[0...m-1], find all occurrences of pat in text
 * Assumption: n > m
 *
 * Example:
 * in: txt[] = "this is a test text"
 * pat[] = "test"
 * out: pattern found at index: 10
 *
 * in: txt[] = "aabaacaadaabaaba"
 * pat[] = "aaba"
 * out: pattern found at index: 0, 9, 12
 */

vector<int> KMP(string text, string pattern)
{
  int m = text.length();
  int n = pattern.length();
  vector<int> result;

  // if pattern is an empty string - "The pattern occurs with shift 0"
  if (n == 0)
  {
    return result;
  }

  // if text's length is less than that of pattern's - "Pattern not found"
  if (m < n)
  {
    return result;
  }

  // next[i] stores the index of the next best partial match
  int next[n + 1];
  for (int i = 0; i < n + 1; i++)
  {
    next[i] = 0;
  }

  for (int i = 1; i < n; i++)
  {
    int j = next[i + 1];

    while (j > 0 && pattern[j] != pattern[i])
    {
      j = next[j];
    }

    if (j > 0 || pattern[j] == pattern[i])
    {
      next[i + 1] = j + 1;
    }
  }

  for (int i = 0, j = 0; i < m; i++)
  {
    if (text[i] == pattern[j])
    {
      if (++j == n)
      {
        int occur = i - j + 1;
        result.push_back(occur);
      }
    }
    else if (j > 0)
    {
      j = next[j];
      i--; // since `i` will be incremented in the next iteration
    }
  }

  return result;
}

// g++ -std=c++0x -pthread -o out knuth-morris-pratt-2.cpp; ./out
int main()
{
  string text = "ABCABAABCABAC";
  string pattern = "CAB";

  auto found_at = KMP(text, pattern);
  for (int i : found_at) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
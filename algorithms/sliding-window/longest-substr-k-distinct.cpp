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
 * Find the longest substring of a string containing `k` distinct characters
 *
 * Given a string and a positive number k, find the longest substring of the string
 * containing k distinct characters. If k is more than the total number of distinct
 * characters in the string, return the whole string.
 *
 * For example, consider string abcbdbdbbdcdabd.
 * For k = 2, o/p is ‘bdbdbbd’
 * For k = 3, o/p is ‘bcbdbdbbdcd’
 * For k = 5, o/p is ‘abcbdbdbbdcdabd’
 */

// Define the character range
#define CHAR_RANGE 128

// Function to find the longest substring of a given string containing
// `k` distinct characters using a sliding window
string findLongestSubstring(string str, int k, int n)
{
  // stores the longest substring boundaries
  int end = 0, begin = 0;

  // set to store distinct characters in a window
  unordered_set<char> window;

  // Count array `freq` stores the frequency of characters present in the
  // current window. We can also use a map instead of a count array.
  int freq[CHAR_RANGE] = {0};

  // `[low…high]` maintains the sliding window boundaries
  for (int low = 0, high = 0; high < n; high++)
  {
    window.insert(str[high]);
    freq[str[high]]++;

    // if the window size is more than `k`, remove characters from the left
    while (window.size() > k)
    {
      // If the leftmost character's frequency becomes 0 after
      // removing it in the window, remove it from the set as well
      if (--freq[str[low]] == 0)
      {
        window.erase(str[low]);
      }

      low++; // reduce window size
    }

    // update the maximum window size if necessary
    if (end - begin < high - low)
    {
      end = high;
      begin = low;
    }
  }

  // return the longest substring found at `str[begin…end]`
  return str.substr(begin, end - begin + 1);
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  string str = "abcbdbdbbdcdabd";
  int k = 2;

  int n = str.length();
  cout << findLongestSubstring(str, k, n);

  return 0;
}
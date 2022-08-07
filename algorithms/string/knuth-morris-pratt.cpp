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

void findPrefix(string pattern, int m, int prefArray[])
{
  int length = 0;
  prefArray[0] = 0; // first place is always 0 as no prefix

  for (int i = 1; i < m; i++)
  {
    if (pattern[i] == pattern[length])
    {
      length++;
      prefArray[i] = length;
    }
    else
    {
      if (length != 0)
      {
        length = prefArray[length - 1];
        i--; // decrease i to avoid effect of increasing after iteration
      }
      else
      {
        prefArray[i] = 0;
      }
    }
  }
}

void kmpPattSearch(string mainString, string pattern, int *locArray, int &loc)
{
  int n, m, i = 0, j = 0;
  n = mainString.size();
  m = pattern.size();
  int prefixArray[m]; // prefix array as same size of pattern
  findPrefix(pattern, m, prefixArray);
  loc = 0;

  while (i < n)
  {
    if (mainString[i] == pattern[j])
    {
      i++;
      j++;
    }

    if (j == m)
    {
      locArray[loc] = i - j; // item found at i-j position.
      loc++;
      j = prefixArray[j - 1]; // get the prefix length from array
    }
    else if (i < n && pattern[j] != mainString[i])
    {
      if (j != 0)
      {
        j = prefixArray[j - 1];
      }
      else
      {
        i++;
      }
    }
  }
}

// g++ -std=c++0x -pthread -o out knuth-morris-pratt.cpp; ./out
int main()
{

  string str = "AAAABAAAAABBBAAAAB";
  string patt = "AAAB";
  int locationArray[str.size()];
  int index;
  kmpPattSearch(str, patt, locationArray, index);

  for (int i = 0; i < index; i++)
  {
    cout << "Pattern found at location: " << locationArray[i] << endl;
  }

  return 0;
}

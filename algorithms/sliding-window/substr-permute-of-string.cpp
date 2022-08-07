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
 * Find all substrings of a string that contains all characters of another string.
 * In other words, find all substrings of the first string that are anagrams of the
 * second string.
 *
 * The first string is 'XYYZXZYZXXYZ'
 * The second string is 'XYZ'
 *
 * Anagram 'YZX' present at index 2
 * Anagram 'XZY' present at index 4
 * Anagram 'YZX' present at index 6
 * Anagram 'XYZ' present at index 9
 */

// Function to find all substrings of string 'X' that are
// permutations of string 'Y'
void findAllAnagrams(string X, string Y)
{
  // `m` and `n` store the length of the string 'Y' and 'X', respectively
  int m, n;

  // invalid input
  if ((m = Y.length()) > (n = X.length()))
  {
    return;
  }

  // maintains the count of characters in the current window
  unordered_multiset<char> window;

  // maintains the count of characters in the second string
  unordered_multiset<char> set;

  // insert all characters of string 'Y' into a set
  for (int i = 0; i < m; i++)
  {
    set.insert(Y[i]);
  }

  // Note that `std::unordered_multiset` or `std::multiset` can maintain
  // duplicate elements unlike `std::unordered_set` or `std::set`

  // maintain a sliding window of size `m` with adjacent characters
  // of string 'X'
  for (int i = 0; i < n; i++)
  {
    // add first `m` characters of string 'X' to the current window
    if (i < m)
    {
      window.insert(X[i]);
    }
    else
    {
      // If all characters in the current window match that of the
      // string 'Y', we found an anagram
      if (window == set)
      {
        cout << "Anagram " << X.substr(i - m, m) << " present at index " << i - m << endl;
      }

      // consider the next substring of 'X' by removing the leftmost element of
      // the sliding window and add the next character of string 'X' to it

      // delete only "one" occurrence of the leftmost element of
      // the current window
      auto itr = window.find(X[i - m]);
      if (itr != window.end())
      {
        window.erase(itr);
      }

      // insert the next character of the string 'X' into the current window
      window.insert(X[i]);
    }
  }

  // if the last `m` characters of string 'X' matches that of string 'Y',
  // we found an anagram
  if (window == set)
  {
    cout << "Anagram " << X.substr(n - m, m) << " present at index " << n - m << endl;
  }
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  string X = "XYYZXZYZXXYZ";
  string Y = "XYZ";

  findAllAnagrams(X, Y);

  return 0;
}
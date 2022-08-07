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
 * Given a string, find all palindromic permutations of it.
 * Input: str = xyxzwxxyz
 *
 * Output:
 *
 * [
 *  xxyzwzyxx, xxzywyzxx, xyxzwzxyx, xyzxwxzyx, xzxywyxzx,
 *  xzyxwxyzx, yxxzwzxxy, yxzxwxzxy, yzxxwxxzy, zxxywyxxz,
 *  zxyxwxyxz, zyxxwxxyz
 * ]
 */

// Function to find all palindromic permutations of a given string
void printPalindromicPermutations(string str)
{
  // base case
  if (str.size() == 0)
  {
    return;
  }

  // store frequency of each character of a string in a map
  unordered_map<char, int> freq;
  for (char ch : str)
  {
    freq[ch]++;
  }

  int odd = 0;        // stores odd character's count
  string mid;         // stores odd character
  string left, right; // stores left and right-half

  // iterate through the map
  for (auto itr : freq)
  {
    char ch = itr.first; // current character
    int c = itr.second;  // character count

    if ((c & 1)) // if the count of the current character is odd
    {
      // if more than one odd character is present in the string,
      // palindromic permutations are not possible
      if (++odd > 1)
      {
        return;
      }

      c = c - 1;       // make count even or zero
      mid = itr.first; // update mid
    }

    // append `c/2` characters to the left-half
    // (other `c/2` characters will go in the right-half)
    c = c / 2;
    while (c--)
    {
      left = left + ch; // update left
    }
  }

  // sort left-half to generate permutations in lexicographical order
  // no need to sort if we use `std::map` as keys are already sorted
  sort(left.begin(), left.end());

  while (1)
  {
    // the right-half will be the reverse of the left-half
    right = left;
    reverse(right.begin(), right.end());

    // print left-half, middle character (if any), and right-half
    cout << (left + mid + right) << endl;

    // find the next lexicographically greater permutation
    if (!next_permutation(left.begin(), left.end()))
    {
      break;
    }
  }

  // Note that we can also sort in reverse order and use `std::prev_permutation`
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{
  string str = "xyxzwxxyz";

  printPalindromicPermutations(str);

  return 0;
}
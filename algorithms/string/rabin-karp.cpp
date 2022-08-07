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
 * Rabin-Karp algorithm for pattern searching
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

// d is the number of characters in the input alphabet
#define d 256

/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
  int M = strlen(pat);
  int N = strlen(txt);
  int i, j;
  int p = 0; // hash value for pattern
  int t = 0; // hash value for txt
  int h = 1;

  // The value of h would be "pow(d, M-1)%q"
  for (i = 0; i < M - 1; i++)
    h = (h * d) % q;

  // Calculate the hash value of pattern and first
  // window of text
  for (i = 0; i < M; i++)
  {
    p = (d * p + pat[i]) % q;
    t = (d * t + txt[i]) % q;
  }

  // Slide the pattern over text one by one
  for (i = 0; i <= N - M; i++)
  {

    // Check the hash values of current window of text
    // and pattern. If the hash values match then only
    // check for characters one by one
    if (p == t)
    {
      /* Check for characters one by one */
      for (j = 0; j < M; j++)
      {
        if (txt[i + j] != pat[j])
        {
          break;
        }
      }

      // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]

      if (j == M)
        cout << "Pattern found at index: " << i << endl;
    }

    // Calculate hash value for next window of text: Remove
    // leading digit, add trailing digit
    if (i < N - M)
    {
      t = (d * (t - txt[i] * h) + txt[i + M]) % q;

      // We might get negative value of t, converting it
      // to positive
      if (t < 0)
        t = (t + q);
    }
  }
}

// g++ -std=c++0x -pthread -o out rabin-karp.cpp; ./out
int main()
{

  char txt[] = "GEEKS FOR GEEKS";
  char pat[] = "GEEK";

  // we mod to avoid overflowing of value but we should take as big q as possible to avoid the collison
  int q = INT_MAX;

  // Function Call
  search(pat, txt, q);
  return 0;
}

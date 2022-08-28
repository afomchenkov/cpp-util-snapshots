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
 * KMP algorithm for pattern searching
 *
 * Given a text[0...n-1] and a pattern pat[0...m-1], find all occurrences of pat
 * in text Assumption: n > m
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

// Function to implement the KMP algorithm
void KMP(string text, string pattern) {
  int m = text.length();
  int n = pattern.length();

  // if pattern is an empty string
  if (n == 0) {
    cout << "The pattern occurs with shift 0";
    return;
  }

  // if text's length is less than that of pattern's
  if (m < n) {
    cout << "Pattern not found";
    return;
  }

  // next[i] stores the index of the next best partial match
  int next[n + 1];

  for (int i = 0; i < n + 1; i++) {
    next[i] = 0;
  }

  for (int i = 1; i < n; i++) {
    int j = next[i + 1];

    while (j > 0 && pattern[j] != pattern[i]) {
      j = next[j];
    }

    if (j > 0 || pattern[j] == pattern[i]) {
      next[i + 1] = j + 1;
    }
  }

  for (int i = 0, j = 0; i < m; i++) {
    if (text[i] == pattern[j]) {
      if (++j == n) {
        cout << "The pattern occurs with shift " << i - j + 1 << endl;
      }
    } else if (j > 0) {
      j = next[j];
      i--; // since `i` will be incremented in the next iteration
    }
  }
}

// g++ -std=c++0x -pthread -o out kmp.cpp; ./out
int main() {

  string text = "ABCABAABCABAC";
  string pattern = "CAB";

  KMP(text, pattern);

  return 0;
}

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

// the worst time complexity O(n*m)
int brute_force_pattern_match(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();

  for (int i = 0; i < n - m; ++i) {
    int k = 0;
    while (k < m && text[i + k] == pattern[k]) {
      k++;
    }
    if (k == m) {
      return i;
    }
  }

  return -1;
}

/**
 * @brief Boyer-Moore algorithm
 * 
 * The main idea of the Boyer-Moore algorithm is to improve the running time of the brute-force
 * algorithm by adding two potentially time-saving heuristics. Roughly stated,
 * these heuristics are as follows:
 * 
 * - Looking-GlassHeuristic: Whentestingapossibleplacementofthepatternagainst the text, perform the 
 *   comparisons against the pattern from right-to-left.
 * 
 * - Character-Jump Heuristic: During the testing of a possible placement of the pattern within
 *   the text, a mismatch of character text[i]=c with the corresponding character pattern[k] is 
 *   handled as follows. If c is not contained anywhere in the pattern, then shift the pattern
 *   completely past text[i] = c. Otherwise, shift the pattern until an occurrence of character c
 *   gets aligned with text[i].
 */




// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  string text = "abacaabaccabacabaabb";
  string pattern = "abacab";


  return 0;
}

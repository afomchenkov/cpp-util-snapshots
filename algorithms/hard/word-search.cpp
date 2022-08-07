#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cstddef>
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
 * Given words = ["oath", "pea", "eat", "rain"]
 * board = [
 *    ['o', 'a', 'a', 'n'],
 *    ['e', 't', 'a', 'e'],
 *    ['i', 'h', 'k', 'r'],
 *    ['i', 'f', 'l', 'v']
 * ]
 *
 * return ["eat", "oath"]
 *
 * backtracking + trie
 */

class TrieNode {
public:
  vector<TrieNode*> next; // 26 letters
  string word;
};

TrieNode* build_trie(vector<string>& words) {
  TrieNode* root = new TrieNode();

  for (string word : words) {
    TrieNode* p = root;
    for (char c : word) {
      int index = c - 'a';
      if (!p->next[index]) {
        p->next[index] = new TrieNode();
      }
      p = p->next[index];
    }
    p->word = word;
  }

  return root;
}

void dfs(vector< vector<char> >&board, int i, int j, TrieNode* p, vector<string>& result) {
  char c = board[i][j];
  int index = c - 'a';

  if (c == '#' || !p->next[index] || i < 0 || j < 0 || i > board.size() - 1 || j > board[0].size() - 1) {
    return;
  }
  p = p->next[index];
  if (p->word != "") {
    result.push_back(p->word);
    p->word = nullptr;
  }

  board[i][j] = '#';

  dfs(board, i - 1, j, p, result);
  dfs(board, i + 1, j, p, result);
  dfs(board, j - 1, j, p, result);
  dfs(board, j + 1, j, p, result);

  board[i][j] = c;
}

vector<string> find_words(vector< vector<char> >& board, vector<string>& words) {
  vector<string> result;
  TrieNode* root = build_trie(words);

  for (int i = 0; i < board.size(); ++i) {
    for (int j = 0; j < board[0].size(); ++j) {
      dfs(board, i, j, root, result);
    }
  }

  return result;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {

  return 0;
}

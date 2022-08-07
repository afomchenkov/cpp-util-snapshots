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

class TrieNode {
public:
  char val;
  bool is_word = false;
  vector<TrieNode*> children; // size == 26

  TrieNode() {}
  TrieNode(char c): val(c) {
    TrieNode* node = new TrieNode();
    node->val = c;
  }
};

class Trie {
public:
  TrieNode* root;

  Trie() {
    root = new TrieNode();
    root->val = ' ';
  }

  void insert(const string word) {
    TrieNode* ws = root;
    for (int i = 0; i < word.length(); ++i) {
      char c = word.at(i);
      int index = c - 'a';
      if (!ws->children[index]) {
        ws->children[index] = new TrieNode(c);
      }
      ws = ws->children[index];
    }
    ws->is_word = true;
  }

  bool search(const string word) {
    TrieNode* ws = root;
    for (int i = 0; i < word.length(); ++i) {
      char c = word.at(i);
      int index = c - 'a';

      if (!ws->children[index]) {
        return false;
      }
      ws = ws->children[index];
    }
    return ws->is_word;
  }

  bool starts_with(const string prefix) {
    TrieNode* ws = root;
    for (int i = 0; i < prefix.length(); ++i) {
      char c = prefix.at(i);
      int index = c = 'a';
      if (!ws->children[index]) {
        return false;
      }
      ws = ws->children[index];
    }
    return false;
  }
};

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  
  return 0;
}
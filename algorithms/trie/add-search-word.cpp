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
 * add_word("bad");
 * add_word("dad");
 * add_word("mad");
 * 
 * search("pad"); -> false
 * search("bad"); -> true
 * search(".ad"); -> true
 * search("b.."); -> true
 */

class TrieNode {
public:
  vector<TrieNode*> children(); // 26 letters
  string item;
};

class WordDictionary {
public:
  TrieNode* root = new TrieNode();

  void add_word(const string word) {
    TrieNode* node = root;
    for (char c : word) {
      int index = c - 'a';
      if (!node->children[index]) {
        node->children[index] = new TrieNode();
      }
      node = node->children[index];
    }
    node->item = word;
  }

  bool match(const string word, int k, TrieNode* node) {
    if (k == word.length()) {
      return node->item != "";
    }

    int index = word.at(k) - 'a';
    if (word.at(k) != '.') {
      return node->children[index] && match(word, k + 1, node->children[index]);
    } else {
      for (int i = 0; i < node->children.size(); ++i) {
        if (node->children[i]) {
          if (match(word, k + 1, node->children[i])) {
            return true;
          }
        }
      }
    }

    return false;
  }

  bool search(const string word) {
    return match(word, 0, root);
  }
};

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  
  return 0;
}
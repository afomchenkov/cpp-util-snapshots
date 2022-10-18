#include <cstdio>
#include <stdexcept>

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

class TreeNode {
public:
  int val;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;

  TreeNode() {}
  TreeNode(int _val): val(_val) {}
};

class Solution {
public:
  vector<string> res;

  void dfs(TreeNode *root, string &visited) {
    if (!root) return;
    if (!root->left && !root->right) {
      res.push_back(visited + to_string(root->val));
      return;
    }

    string tmp = visited;
    visited += to_string(root->val) + "->";
    dfs(root->left, visited);
    dfs(root->right, visited);
    visited = tmp;
  }

  vector<string> btPaths(TreeNode* root) {
    string visited;
    dfs(root, visited);
    return res;
  }
};

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main() {
  return 0;
}

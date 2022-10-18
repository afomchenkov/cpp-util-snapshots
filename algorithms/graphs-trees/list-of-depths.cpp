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
 * Given a BT, build a linked list of all the nodes at each depth.
 * (e.g. if you have a tree with depth d, you'll have d linked lists)
 */
struct TreeNode {
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
  int val;

  TreeNode() {}
  TreeNode(int _val): val(_val) {}
};

// modify pre-order traversal where we pass in level + to the next recursive call
void create_level_linked_list(TreeNode* root, vector<list<TreeNode*>>& lists, int level) {
  if (!root) {
    return;
  }

  list<TreeNode*> list_here;
  if (lists.size() == level) {
    list_here = {};
    // Levels are always traversed in order, if this is the first time visit level i
    // we must have seen levels 0 to i - 1, therefore add safely level at the end
    lists.push_back(list_here);
  } else{
    list_here = lists[level];
  }

  list_here.push_back(root);
  create_level_linked_list(root->left, lists, level + 1);
  create_level_linked_list(root->right, lists, level + 1);
}

vector<list<TreeNode*>> create_level_ll(TreeNode* root) {
  vector<list<TreeNode*>> lists;
  create_level_linked_list(root, lists, 0);
  return lists;
}

// modification of BFS, iterate level by level
vector<list<TreeNode*>> create_level_ll_bfs(TreeNode* root) {
  vector<list<TreeNode*>> result;
  list<TreeNode*> current;

  // visit root
  if (root) {
    current.push_back(root);
  }

  while (!current.empty()) {
    result.push_back(current);
    list<TreeNode*> parents = current;

    current = {};
    for (TreeNode* parent : parents) {
      if (parent->left) {
        current.push_back(parent->left);
      }
      if (parent->right) {
        current.push_back(parent->right);
      }
    }
  }

  return result;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  return 0;
}
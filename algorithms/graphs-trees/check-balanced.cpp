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
 * Check if BT is balanced, heights of the two subtrees of any node never differ by more than one
 */
struct TreeNode
{
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  int val;

  TreeNode() {}
  TreeNode(int _val) : val(_val) {}
};

int get_height(TreeNode* root) {
  if (!root) {
    return -1;
  }

  return max(get_height(root->left), get_height(root->right)) + 1;
}

// not very efficient
bool is_balanced(TreeNode* root) {
  if (!root) {
    return true;
  }

  int heightDiff = get_height(root->left) - get_height(root->right);
  if (abs(heightDiff) > 1) {
    return false;
  } else {
    return is_balanced(root->left) && is_balanced(root->right);
  }
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  return 0;
}
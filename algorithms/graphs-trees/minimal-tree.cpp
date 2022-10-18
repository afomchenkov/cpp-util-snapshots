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
 * Given a sorted increasingly array with unique integers, create a BST with minimal height
 * 
 * Match the number of nodes in left and right subtree as much as possible. Take the mid of
 * array as a root so half will be less then the root and half greater.
 */

struct TreeNode {
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
  int val;

  TreeNode() {}
  TreeNode(int _val): val(_val) {}
};

/**
 * @brief Create a min bst object
 * 
 * 1. insert middle element of the array
 * 2. insert left subarray elements
 * 3. insert right subarray elements
 * 4. recurse
 * 
 * @param arr 
 * @param start 
 * @param end 
 * @return TreeNode* 
 */
TreeNode* create_min_bst(vector<int>& arr, int start, int end) {
  if (start == end) {
    return nullptr;
  }

  int mid = (start + end) / 2;
  TreeNode* n = new TreeNode(arr[mid]);
  n->left = create_min_bst(arr, start, mid - 1);
  n->right = create_min_bst(arr, mid + 1, end);
  
  return n;
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  return 0;
}
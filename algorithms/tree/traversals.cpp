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

class TreeNode {
public:
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() {}
  TreeNode(int _val): val(_val) {}
  TreeNode(int _val, TreeNode* _left, TreeNode* _right): val(_val), left(_left), right(_right) {}
};

// https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

vector<int> preorder_traversal(TreeNode* root) {
  vector<int> preorder;

  if (!root) {
    return preorder;
  }

  stack<TreeNode*> st;
  st.push(root);

  // traverse: root, left, right
  while (!st.empty()) {
    auto node = st.top();
    st.pop();

    preorder.push_back(node->val);
    
    if (node->right) {
      st.push(node->right);
    }

    if (node->left) {
      st.push(node->left);
    }
  }

  return preorder;
}

vector<int> inorder_traversal(TreeNode* root) {
  vector<int> inorder;

  if (!root) {
    return inorder;
  }

  stack<TreeNode*> st;
  auto node = root;

  // traverse: left, root, right
  while (!stack.empty() || node) {
    if (node) {
      st.push(node);
      node = node->left;
    } else {
      node = st.top();
      st.pop();

      inorder.push_back(node->val);
      node = node->right;
    }
  }

  return inorder;
}

vector<int> postorder_traversal(TreeNode* root) {
  vector<int> postorder;

  if (!root) {
    return postorder;
  }

  stack<TreeNode*> st;
  stack<TreeNode*> st_out;
  st.insert(root);

  while (!st.empty()) {
    auto current = st.top();
    st.pop();

    st_out.insert(current->val);

    if (current->left) {
      st.insert(current->left);
    }
    if (current->right) {
      st.insert(current->right);
    }
  }

  return st_out;
}

int main()
{

  return 0;
}
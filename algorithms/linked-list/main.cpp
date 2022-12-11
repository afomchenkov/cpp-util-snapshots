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

class Node
{
public:
  int val;
  Node *next = nullptr;

  Node() {}
  Node(int _val) : val(_val) {}
  Node(int _val, Node *_next) : val(_val), next(_next) {}
};

bool has_cycle(Node *root)
{
  if (!root)
  {
    return false;
  }

  Node *fast = root;
  Node *slow = root;

  while (fast && fast->next)
  {
    slow = slow->next;

    if (!fast->next || !fast->next->next)
    {
      return false;
    }

    fast = fast->next->next;

    if (fast == slow)
    {
      return true;
    }
  }

  return false;
}

Node *merge_two_lists(Node *l1, Node *l2)
{
  if (!l1 && !l2)
  {
    return nullptr;
  }
  else if (!l1 && l2)
  {
    return l2;
  }
  else if (l1 && !l2)
  {
    return l1;
  }

  Node *head = new Node();
  auto pointer = head;

  while (l1 && l2)
  {
    if (l1->val < l2->val)
    {
      pointer.next = l1;
      l1 = l1->next;
    }
    else
    {
      pointer->next = l2;
      l2 = l2->next;
    }

    pointer = pointer->next;
  }

  if (l1)
  {
    pointer->next = l1;
  }

  if (l2)
  {
    pointer->next = l2;
  }

  return head->next;
}

bool is_palindr(Node *head)
{
  if (!head)
  {
    return true;
  }

  if (head && !head->next)
  {
    return true;
  }

  Node *fast = head;
  Node *slow = head;

  stack<int> st;
  while (fast && fast->next)
  {
    st.push(slow->val);
    slow = slow->next;
    fast = fast->next->next;
  }

  if (fast)
  {
    slow = slow->next;
  }

  while (slow)
  {
    if (slow->val != st.top())
    {
      return false;
    }
    else
    {
      slow = slow->next;
    }

    st.pop();
  }

  return true;
}

Node *remove_elements(Node *head, int val)
{
  if (!head)
  {
    return nullptr;
  }

  if (head && !head->next)
  {
    if (head->val == val)
    {
      return nullptr;
    }
    else
    {
      return head;
    }
  }

  Node *dummy = new Node(0, head);
  auto prev = dummy;

  while (head)
  {
    if (head->val == val)
    {
      // skip current
      prev->next = head->next;
      head = prev;
    }

    prev = head;
    head = head->next;
  }

  return dummy->next;
}

Node* remove_duplicates(Node* head) {
  if (!head) {
    return nullptr;
  }
  if (head && !head->next) {
    return head;
  }

  set<int> lookup;
  auto current = head;
  auto prev = head;

  while (current) {
    if (lookup.count(current->val)) {
      prev->next = prev->next->next;
    } else {
      lookup.insert(current->val);
      prev = current;
    }

    current = current->next;
  }

  return head;
}

int main()
{

  return 0;
}
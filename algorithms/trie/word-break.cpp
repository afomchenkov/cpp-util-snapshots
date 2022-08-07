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
 * Input:
 * words[] = { this, th, is, famous, Word, break, b, r, e, a, k, br, bre, brea, ak, problem }
 *
 * string = Wordbreakproblem
 *
 * Output: The string can be segmented
 *
 *
 * The segmented strings are:
 *
 * Word break problem
 * Word brea k problem
 * Word bre ak problem
 * Word bre a k problem
 * Word br e ak problem
 * Word br e a k problem
 * Word b r e ak problem
 * Word b r e a k problem
 */

// Currently, Trie supports lowercase English characters `a – z`.
// So, the character size is 26.
#define CHAR_SIZE 26

// Data structure to store a Trie node
struct Node
{
  bool exist; // true when the node is a leaf node
  Node *next[CHAR_SIZE];

  // Function that returns a new Trie node
  Node()
  {
    exist = false;

    for (int i = 0; i < CHAR_SIZE; i++)
    {
      next[i] = nullptr;
    }
  }
};

// Recursive function to delete a Trie in a postorder manner
void freeTrie(Node *node)
{
  if (!node)
  {
    return;
  }

  for (int i = 0; i < CHAR_SIZE; i++)
  {
    freeTrie(node->next[i]);
  }

  delete node;
}

// Iterative function to insert a string into a Trie
void insertTrie(Node *const head, string const &s)
{
  // start from the root node
  Node *node = head;

  // do for each character in the string
  for (char ch : s)
  {
    // create a new node if the path doesn't exist
    if (node->next[ch - 'a'] == nullptr)
    {
      node->next[ch - 'a'] = new Node();
    }

    // go to the next node
    node = node->next[ch - 'a'];
  }

  // mark the last node as a leaf
  node->exist = true;
}

// Function to determine if the string can be segmented into a
// space-separated sequence of one or more dictionary words
bool wordBreak(Node *const head, string const &s)
{
  // get the length of the string
  int n = s.length();

  // `good[i]` is true if the first `i` characters of `s` can be segmented
  vector<bool> good(n + 1);
  good[0] = true; // base case

  for (int i = 0; i < n; i++)
  {
    if (good[i])
    {
      Node *node = head;
      for (int j = i; j < n; j++)
      {
        if (!node)
        {
          break;
        }

        node = node->next[s[j] - 'a'];

        // we can make [0, i] using our known decomposition
        // and [i+1, j] using this string in a Trie
        if (node && node->exist)
        {
          good[j + 1] = true;
        }
      }
    }
  }

  // `good[n]` would be true if all characters of `s` can be segmented
  return good[n];
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  // vector of strings to represent a dictionary
  vector<string> words =
      {
          "this", "th", "is", "famous", "word", "break", "b", "r",
          "e", "a", "k", "br", "bre", "brea", "ak", "prob", "lem"};

  // given string
  string s = "wordbreakproblem";

  // create a Trie to store the dictionary
  Node *trie = new Node();
  for (string const &s : words)
  {
    insertTrie(trie, s);
  }

  // check if the string can be segmented or not
  if (wordBreak(trie, s))
  {
    cout << "The string can be segmented";
  }
  else
  {
    cout << "The string can't be segmented";
  }

  // deallocate memory used by the Trie
  freeTrie(trie);

  return 0;
}
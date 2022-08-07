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
 * Input:  A[] = { 5, 2, 3, 5, 4, 3 }
 * Output: The largest subarrays with all distinct elements are:
 *
 * { 5, 2, 3 }
 * { 2, 3, 5, 4 }
 * { 5, 4, 3 }
 */

// Utility function to print the subarray formed by `A[i, j]`
void printSubarray(int A[], int i, int j, int n)
{
  if (i < 0 || i > j || j >= n)
  { // invalid input
    return;
  }

  for (int index = i; index < j; index++)
  {
    cout << A[index] << ", ";
  }

  cout << A[j] << endl;
}

// Function to print all subarrays having distinct elements
void calculate(int A[], int n)
{
  // create a map to mark elements as visited in the current window
  unordered_map<int, bool> visited;

  // points to the left and right boundary of the current window;
  // i.e., the current window is formed by `A[left, right]`
  int right = 0, left = 0;

  // loop until the right index of the current window is less
  // than the maximum index
  while (right < n)
  {
    // keep increasing the window size if all elements in the
    // current window are distinct
    while (right < n && !visited[A[right]])
    {
      visited[A[right]] = true;
      right++;
    }

    printSubarray(A, left, right - 1, n);

    // As soon as a duplicate is found (`A[right]`),
    // terminate the above loop, and reduce the window's size
    // from its left to remove the duplicate
    while (right < n && visited[A[right]])
    {
      visited[A[left]] = false;
      left++;
    }
  }
}

// g++ -std=c++0x -pthread -o out file.cpp; ./out
int main()
{

  int A[] = {5, 2, 3, 5, 4, 3};
  int n = sizeof A / sizeof A[0];

  calculate(A, n);

  return 0;
}
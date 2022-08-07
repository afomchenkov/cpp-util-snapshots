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
 * const - a compile time constraint that an object cannot be modified
 *
 * Why use const:
 * - guards against inadvertent write to the variable
 * - self documenting
 * - enables compiler to do more optimization, making code tighter
 * - const means the variable can be put in ROM (read-only memory)
 */

int main()
{
  const int i = 9;
  // i = 6; // <- error: assignment of read-only variable 'i'
  const_cast<int &>(i) = 6; // reassigns the const

  int j;
  // const_cast<const int&>(j); = 7; // <- error: assignment of read-only location '* (const int*)(& j)'

  const int *p1 = &i; // data is const, pointer is not
  // *p1 = 5; // <- error: assignment of read-only location '*p1'
  p1++;

  int *const p2 = 0; // pointer is const, data is not

  const int *const p3 = 0; // data and pointer are const

  int const *p4 = &i;
  const int *p5 = &i;
  // if const is on the left of *, data is const
  // if const is on the right of *, pointer is const

  return 0;
}

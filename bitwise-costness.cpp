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

class BigArray
{
  vector<int> v; // huge vector
  int accessCounter;
  mutable int accessCounterMut;

  int *v2; // another int array

public:
  int getItem(int index) const
  {
    // accessCounter++; // <- fails as function marked as const
    accessCounterMut++;                            // <- does not fail
    const_cast<BigArray *>(this)->accessCounter++; // hacky way to update

    return v[index];
  }

  void setV2Item(int index, int x)
  {
    *(v2 + index) = x;
  }

  /**
   * 1. the return value of fun is a constant pointer pointing to a constant integer value
   *
   * 2. the parameter of fun is a reference of a constant pointer pointing to a constant
   * integer the reference cannot refer to a different pointer (nature of references)
   * the referred pointer cannot point to a different value the pointed value of the
   * referred pointer cannot be changed
   *
   * 3. fun is also a const function, meaning that it cannot directly modify members unless
   * they are marked mutable, also it can only call other const functions
   *
   */
  const int *const fun(const int *const &p) const;
};

int main()
{
  BigArray b1;

  return 0;
}

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
 * handle self-assignment in operator=
 *
 * operator overload: exploite people's intuition and reduce learning curve
 */

// solution 1: implement assignment operator
class collar
{
};
class dog
{
  collar *pCollar;

  dog &operator=(const dog &rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }

    collar *pOrigCollar = pCollar;
    pCollar = new collar(*rhs.pCollar);

    delete pOrigCollar;
    return *this;
  }
};

// solution 2: delegation
class cat
{
  collar *pCollar;
  cat &operator=(const cat &rhs)
  {
    *pCollar = *rhs.pCollar;
    // member by member copying of collars or call collar's operator=

    return *this;
  }
};

int main()
{
  return 0;
}

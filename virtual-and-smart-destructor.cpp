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

// using virtual destructors in polymorphic base classes
// Note: all classes in STL have no virtual destructor, inherit from them carefully

class Dog
{
public:
  virtual ~Dog()
  {
    cout << "Dog destroyed" << endl;
  }
  virtual void bark() {}
};

class YellowDog : public Dog
{
public:
  ~YellowDog()
  {
    cout << "YellowDog destroyed" << endl;
  }
};

class DogFactory
{
public:
  static shared_ptr<Dog> createYellowDog()
  {
    // ...
    return shared_ptr<YellowDog>(new YellowDog());
  }
};

int main()
{
  // Dog *pd = DogFactory::createYellowDog();
  // delete pd;

  // with shared pointer no need to delete
  // virtual destructor can also be removed
  shared_ptr<Dog> pd = DogFactory::createYellowDog();

  // destructors called:
  // - YellowDog destroyed
  // - Dog destroyed

  return 0;
}

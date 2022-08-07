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
 * calling virtual function in constructor or destructor
 */

class Dog
{
public:
  Dog()
  {
    cout << "Dog is born" << endl;
  }

  virtual void bark()
  {
    cout << "I am a Dog" << endl;
  }

  void seeCat()
  {
    bark();
  }
};

class YellowDog : public Dog
{
public:
  YellowDog()
  {
    cout << "YellowDog is born" << endl;
  }

  // dynamic binding of 'bark'
  void bark()
  {
    cout << "I am a YellowDog" << endl;
  }
}

int
main()
{

  YellowDog d;
  d.seeCat();

  // > output if 'bark' is not virtual
  // Dog is born
  // YellowDog is born
  // I am a Dog

  // > output if 'bark' is virtual
  // Dog is born
  // YellowDog is born
  // I am a YellowDog

  return 0;
}

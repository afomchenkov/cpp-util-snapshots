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
 * const used with functions
 */

class Dog
{
  int age;
  string name;

public:
  Dog()
  {
    age = 3;
    name = "dummy";
  }

  // const parameters
  void setAge1(const int a)
  {
    age = a;
  }
  // <- fails: 'void Dog::setAge1(int)' cannot be overloaded
  // void setAge1(int a) {
  //   age = a;
  // }

  void setAge2(int &a)
  {
    age = a;
    a++; // modifies variable outside
  }

  void setAgeConstRef3(const int &a)
  {
    age = a;
    // a++; // <- fails
  }

  // const return value: caller cannot change the value
  const string &getName()
  {
    return name;
  }

  // const is useless here
  // const string getName() {
  //   return name;
  // }

  // const function - does not change member variables
  void printDogName() const
  {
    cout << name << " const " << endl;
  }
  // overload - separate function
  void printDogName()
  {
    cout << name << " non-const " << endl;
  }
};

int main()
{
  int i = 9;

  Dog d;
  d.setAge2(i);
  d.setAgeConstRef3(i);
  d.printDogName(); // calls second function

  const Dog d2;
  d2.printDogName(); // call first function

  return 0;
}

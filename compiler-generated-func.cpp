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
 * Compiler silently writes 4 functions:
 *
 * 1. copy constructor
 * 2. copy assignment operator
 * 3. destructor
 * 4. default constructor (only if there is no constructor declared)
 */

class Dog
{
};

// equivalent to
// class Dog {
// public:
//   Dog(const Dog& rhs) {
//     // ...
//     // member by member initialization
//   }

//   auto operator= (const Dog& rhs) {
//     // ...
//     // member by member copying
//   }

//   Dog() {
//     // ...
//     // default constructor
//     // 1. call base class's default constructor
//     // 2. call data member's default constructor
//   }

//   ~Dog() {
//     // ...
//     // default destructor
//     // 1. call bases class's destructor
//     // 2. call data member's destructor
//   }
// };

class Person
{
public:
  string m_name;
  // string& m_name;

  Person(string name = "Bob")
  {
    m_name = name;
    cout << name << " is born." << endl;
  }
  ~Person()
  {
    cout << m_name << " is destroyed." << endl;
  }
};

class Collar
{
public:
  // without default param the default constructor is missing
  Collar(string color = "default")
  {
    cout << "Collar is born." << endl;
  }
};

class Wrapper
{
  Collar m_collar;
  // string& m_name; // <- ref date member prevents
  //    the compiler from generating copy assignment
  //    operator for the cast <> it must either be initialized
  //    or define copy operator/constructor

public:
  Wrapper() = default; // define default constructor
};

int main()
{
  Person p1("Henry");
  Person p2;
  p2 = p1; // copy assignment operator generated by compiler
  // string& m_name; <- will not compile with default copy constructor

  // Henry is born.
  // Bob is born.
  // Henry is destroyed.
  // Henry is destroyed.

  Wrapper wr1;

  return 0;
}
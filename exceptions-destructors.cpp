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
 * prevent exceptions from leaving destructors
 */

class Dog
{
public:
  string m_name;
  Dog(string name)
  {
    m_name = name;
    cout << name << " is born" << endl;
  }
  ~Dog()
  {
    cout << m_name << "is destroyed" << endl;
    // throw 20; // <- should not be like that

    // solutions 1: destructor swallow exception
    // try {
    //   // enclose all the exception prone code here
    // } catch (MY_EXCEPTION e) {
    //   // handle exception
    // }
  }
  void prepareToDestroy()
  {
    // solution 2: move the exception prone code to a different function
    // ...
    throw 20;
  }

  void bark() {}
};

int main()
{

  try
  {
    Dog dog1("Henry");
    Dog dog2("Bob");

    // throw 20;

    dog1.bark();
    dog2.bark();

    dog1.prepareToDestroy();
    dog2.prepareToDestroy();
  }
  catch (int e)
  {
    cout << e << " is caught" << endl;
  }

  // > output:
  // Henry is born
  // Bob is born
  // Bob is destroyed
  // Henry is destroyed
  // 20 is caught

  return 0;
}

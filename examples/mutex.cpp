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

// https://stackoverflow.com/questions/4989451/mutex-example-tutorial

/**
 * Threads : | | | | | | | | | |
 * Mutex   :       m
 * Lock    :       l
 * Resource:       r
 */

std::mutex m; // you can use std::lock_guard if you want to be exception safe
int i = 0;

void makeACallFromPhoneBooth()
{
  m.lock(); // man gets a hold of the phone booth door and locks it. The other men wait outside
  // man happily talks to his wife from now....
  std::cout << i << " Hello Wife" << std::endl;
  i++; // no other thread can access variable i until m.unlock() is called
  //...until now, with no interruption from other men
  m.unlock(); // man lets go of the door handle and unlocks the door
}

// g++ -std=c++0x -pthread -o mutex mutex.cpp; ./mutex

int main()
{

  // This is the main crowd of people uninterested in making a phone call

  // man1 leaves the crowd to go to the phone booth
  std::thread man1(makeACallFromPhoneBooth);
  // Although man2 appears to start second, there's a good chance he might
  // reach the phone booth before man1
  std::thread man2(makeACallFromPhoneBooth);
  // And hey, man3 also joined the race to the booth
  std::thread man3(makeACallFromPhoneBooth);

  man1.join(); // man1 finished his phone call and joins the crowd
  man2.join(); // man2 finished his phone call and joins the crowd
  man3.join(); // man3 finished his phone call and joins the crowd
  return 0;
}
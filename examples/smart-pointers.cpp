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

#include <system_error>
#include <cstdio>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


// > Scoped pointers
// A scoped pointer expresses non-transferable, exclusive ownership over a single dynamic object.
// - Non-transferable means that the scoped pointers cannot be moved from one scope to another.
// - Exclusive ownership means that they can’t be copied, so no other smart pointers can have
// ownership of a scoped pointer’s dynamic object. 
//
// There is no stdlib scoped pointer.
// boost::scoped_ptr is defined in the <boost/smart_ptr/scoped_ptr.hpp>

// > Unique pointers
// A unique pointer has transferable, exclusive ownership over a single dynamic object. You can
// move unique pointers, which makes them transferable. They also have exclusive ownership, so
// they cannot be copied. The stdlib has a unique_ptr available in the <memory> header.

// As with a scoped pointer, the unique pointer has a default constructor that initializes
// the unique pointer to empty. It also provides a constructor taking a raw pointer that takes
// ownership of the pointed-to dynamic object. One construction method is to create a dynamic
// object with new and pass the result to the constructor
//
// std::unique_ptr<int> my_ptr{ new int{ 808 } };
//
// Another method is to use the std::make_unique function. The make_unique function is a 
// template that takes all the arguments and forwards them to the appropriate constructor of
// the template parameter.
// auto my_ptr = make_unique<int>(808);


// > Weak pointers
// A weak pointer is a special kind of smart pointer that has no ownership over the object to
// which it refers. Weak pointers allow you to track an object and to convert the weak pointer
// into a shared pointer only if the tracked object still exists. This allows you to generate 
// temporary ownership over an object. Like shared pointers, weak pointers are movable and 
// copyable.
//
// A common usage for weak pointers is caches. In software engineering, a cache is a data 
// structure that stores data temporarily so it can be retrieved faster. A cache could keep 
// weak pointers to objects so they destruct once all other owners release them. Periodically, 
// the cache can scan its stored weak pointers and trim those with no other owners.
//
// auto sp = std::make_shared<int>(808);
// std::weak_ptr<int> wp{ sp };
// Now the weak pointer wp will track the object owned by the shared pointer sp.


// Allocators
static size_t n_allocated, n_deallocated;

template <typename T>
struct MyAllocator {
  using value_type = T;

  MyAllocator() noexcept{ }
  
  template <typename U>
  MyAllocator(const MyAllocator<U>&) noexcept { }
  
  T* allocate(size_t n) {
    auto p = operator new(sizeof(T) * n);
    ++n_allocated;
    return static_cast<T*>(p);
  }

  void deallocate(T* p, size_t n) {
    operator delete(p);
    ++n_deallocated;
  }
};

template <typename T1, typename T2>
bool operator==(const MyAllocator<T1>&, const MyAllocator<T2>&) {
  return true;
}
template <typename T1, typename T2>
bool operator!=(const MyAllocator<T1>&, const MyAllocator<T2>&) {
  return false;
}

// Smart pointers manage dynamic objects via RAII, and you can provide allocators to 
// customize dynamic memory allocation. Depending on which smart pointer you choose, 
// you can encode different ownership patterns onto the dynamic object.

/**
 * g++ -std=c++0x -pthread -o out file.cpp; ./out
 */
int main()
{

  return 0;
}

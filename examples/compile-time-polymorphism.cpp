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
#include <cstddef>

using namespace std;

// template class wtih three template parameters
template<typename X, typename Y, typename Z>
struct TemplateClass {
  X foo(Y&);
private:
  Z* member;
};

// template function
template<typename X, typename Y, typename Z>
X template_function(Y& arg1, const Z* arg2) {}

// Named conversion - named-conversion<desired-type>(object-to-cast)

// - const_cast
// The const_cast function shucks away the const modifier, allowing 
// the modification of const values.
void carbon_thaw(const int& encased_solo) {
  // encased_solo++; // Compiler error; modifying const
  auto& hibernation_sick_solo = const_cast<int&>(encased_solo);
  hibernation_sick_solo++;
}
// - static_cast
// The static_cast reverses a well-defined implicit conversion, such as an
// integer type to another integer type.

// - reinterpret_cast
// In system programming and especially in embedded environments, you often need complete 
// control over how to interpret memory. The reinterpret_cast gives you such control, 
// but ensuring the correctness of these conversions is entirely your responsibility.

// - narrow_cast
// Narrowing is a loss in information. Think about converting from an int to a short. As 
// long as the value of int fits into a short, the conver- sion is reversible and no narrowing occurs.
// If the value of int is too big for the short, the conversion isn’t reversible and results in narrowing.


// What you need to solve this copy-and-paste problem is generic programming, a programming
// style where you program with yet-to-be-specified types. You achieve generic programming
// using the support C++ has for templates. Templates allow the compiler to instantiate a custom
// class or function based on the types in use.
template<typename T>
T mean(T* values, size_t length) {
  T result{};

  for (size_t i{}; i < length; i++) {
    result += values[i];
  }

  return result / length;
}
// Fortunately, you can generally omit the template parameters when invoking a template function.
// The process that the compiler uses to determine the correct template parameters is called
// template type deduction.

// SimpleUniquePointer: A Template Class Example
// A unique pointer is an RAII wrapper around a free-store-allocated object. 
template<typename T>
struct SimpleUniquePointer {
  SimpleUniquePointer() = default;
  SimpleUniquePointer(T* pointer): pointer {pointer} {}
  ~SimpleUniquePointer() {
    if (pointer) {
      delete pointer;
    }
  }
  SimpleUniquePointer(const SimpleUniquePointer&) = delete;
  SimpleUniquePointer& operator=(const SimpleUniquePointer&) = delete;
  SimpleUniquePointer(SimpleUniquePointer&& other) noexcept: pointer{other.pointer} {
    other.pointer = nullptr;
  }
  SimpleUniquePointer& operator=(SimpleUniquePointer&& other) noexcept {
    if (pointer) {
      delete pointer;
    }

    pointer = other.pointer;
    other.pointer = nullptr;
    return *this;
  }

  T* get() {
    return pointer;
  }

private:
  T* pointer;
};

// - Concepts
// Concepts constrain template parameters, allowing for parameter checking at the point 
// of instantiation rather than the point of first use. By catching usage issues at the 
// point of instantiation, the compiler can give you a friendly, informative error code—for 
// example, “You tried to instantiate this template with a char*, but this template requires
// a type that supports multiplication.”
// Concepts allow you to express requirements on template parameters directly in the language.

// A concept is a template. It’s a constant expression involving template arguments, 
// evaluated at compile time. Think of a concept as one big predicate: a function that 
// evaluates to true or false.
// If a set of template parameters meets the criteria for a given concept, that concept
// evaluates to true when instantiated with those parameters; otherwise, it will evaluate
// to false. When a concept evaluates to false, template instantiation fails.
//
// template<typename T1, typenameT2, ...>
// concept bool ConceptName() {}


// Variadic templates
// template<typename T, typename... Arguments>
// SimpleUniquePointer<T> make_simple_unique(Arguments... arguments) {
//   return SimpleUniquePointer<T>{ new T{ arguments...} };
// }


/**
 * g++ -std=c++0x -pthread -o out file.cpp; ./out
 */
int main()
{

  return 0;
}

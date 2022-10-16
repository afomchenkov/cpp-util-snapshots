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

// Transfer ownership of resources from one object to another. Move semantics is move’s corollary to copy
// semantics, and it requires that after an object y is moved into an object x, x is equivalent to the
// former value of y. After the move, y is in a special state called the moved-from state.


// void own_a_string() {
//   --- code ---
//   SimpleString a{ 50 };
//   a.append_line("We apologize for the");
//   a.append_line("inconvenience.");
//   SimpleStringOwner b{ a };
//   --- code ---
// }
// After copy constructor called for SimpleStringOwner the 'a' instance not needed
// anymore so we should move the guts of SimpleString 'a' into 'h_string' field.
// After moving a, the SimpleString of b is equivalent to the former state of a,
// and a is destructible.
//
// The class invariants of SimpleString aren’t satisfied when a is moved from. The compiler
// has built-in safeguards: lvalues and rvalues though.
//
// Every expression has two important characteristics: its type and its value category.
// A value category describes what kinds of operations are valid for the expression.
//
// An lvalue is any value that has a name, and an rvalue is anything that isn’t an lvalue.
// Move constructors look like copy constructors except they take rvalue references instead of lvalue references.

void ref_type(int &x)
{
  printf("lvalue reference %d\n", x);
}

void ref_type(int &&x)
{
  printf("rvalue reference %d\n", x);
}


// A fully specified SimpleString class supporting copy and move semantics
struct SimpleString
{
  SimpleString(size_t max_size)
      : max_size{max_size},
        length{}
  {
    if (max_size == 0)
    {
      throw std::runtime_error{"Max size must be at least 1."};
    }
    buffer = new char[max_size];
    buffer[0] = 0;
  }

  ~SimpleString()
  {
    delete[] buffer;
  }

  SimpleString(const SimpleString &other)
      : max_size{other.max_size},
        buffer{new char[other.max_size]},
        length{other.length}
  {
    std::strncpy(buffer, other.buffer, max_size);
  }

  SimpleString(SimpleString &&other) noexcept
      : max_size(other.max_size),
        buffer(other.buffer),
        length(other.length)
  {
    other.length = 0;
    other.buffer = nullptr;
    other.max_size = 0;
  }

  SimpleString &operator=(const SimpleString &other)
  {
    if (this == &other)
      return *this;
    const auto new_buffer = new char[other.max_size];
    delete[] buffer;
    buffer = new_buffer;
    length = other.length;
    max_size = other.max_size;
    std::strncpy(buffer, other.buffer, max_size);
    return *this;
  }

  SimpleString &operator=(SimpleString &&other) noexcept
  {
    if (this == &other)
      return *this;
    delete[] buffer;
    buffer = other.buffer;
    length = other.length;
    max_size = other.max_size;
    other.buffer = nullptr;
    other.length = 0;
    other.max_size = 0;
    return *this;
  }

  void print(const char *tag) const
  {
    printf("%s: %s", tag, buffer);
  }

  bool append_line(const char *x)
  {
    const auto x_len = strlen(x);
    if (x_len + length + 2 > max_size)
      return false;
    std::strncpy(buffer + length, x, max_size - length);
    length += x_len;
    buffer[length++] = '\n';
    buffer[length] = 0;
    return true;
  }

private:
  size_t max_size;
  char *buffer;
  size_t length;
};

struct SimpleStringOwner
{
  SimpleStringOwner(const SimpleString &my_string) : h_string{my_string} {}

private:
  SimpleString h_string;
};

// Compiler-Generated Methods
// Five methods govern move and copy behavior:
//  • The destructor
//  • The copy constructor
//  • The move constructor
//  • The copy assignment operator
//  • The move assignment operator

/**
 * g++ -std=c++0x -pthread -o out copy-semantics.cpp; ./out
 */
int main()
{
  auto x = 1;
  ref_type(x);            // lvalue reference 1 - x is lvalue and it has a name
  ref_type(2);            // rvalue reference 2 - 2 is an integer literal without a name
  ref_type(x + 2);        // rvalue reference 3 - the result of adding 2 to x is not bound to a name
  ref_type(std::move(x)); // rvalue reference 1

  return 0;
}

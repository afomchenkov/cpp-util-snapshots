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

struct Point
{
  int x, y;
};

// pass-by-value
Point make_transpose(Point p)
{
  // p - is a copy of passed POD type Point
  int tmp = p.x;
  p.x = p.y;
  p.y = tmp;
  return p;
}

// Copy constructors
struct SimpleString
{
  SimpleString()
  {
    int default_max_size = 256;
    buffer = new char[default_max_size];
    buffer[0] = 0;
  }

  SimpleString(size_t max_size) : max_size{max_size}, length{}
  {
    if (max_size == 0)
    {
      throw std::runtime_error{"Max size must be at least 1"};
    }

    buffer = new char[max_size];
    buffer[0] = 0;
  }

  SimpleString(const SimpleString &other) : max_size{other.max_size},
                                            buffer{new char[other.max_size]},
                                            length{other.length}
  {
    std::strncpy(buffer, other.buffer, max_size);
  }

  ~SimpleString()
  {
    // This pattern is called resource acquisition is initialization (RAII) or
    // constructor acquires, destructor releases (CADRe).
    delete[] buffer;
  }

  SimpleString &operator=(const SimpleString &other)
  {
    if (this == &other) {
      return *this;
    }
    
    const auto new_buffer = new char[other.max_size];
    delete[] buffer;
    buffer = new_buffer;
    length = other.length;
    max_size = other.max_size;
    // strcpy_s(buffer, max_size, other.buffer);
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
    {
      return false;
    }
    // har* std::strncpy(char* destination, const char* source, std::size_t num);
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

// The copy constructor is invoked when passing SimpleString into a function by value
void foo(SimpleString x)
{
  // NB: You shouldn’t pass by value to avoid modification. Use a const reference.
  x.append_line("This change is lost.");
}

// Default copy
struct Replicant {
  // Best practice dictates to explicitly declare default copy assignment and
  // copy construction using the default keyword.
  Replicant(const Replicant&) = default;
  Replicant& operator=(const Replicant&) = default;
};

struct Highlander {
  // Suppress the compiler from generating a copy constructor and
  // a copy assignment operator using the delete keyword.
  Highlander(const Highlander&) = delete;
  Highlander& operator=(const Highlander&) = delete;
};

/**
 * g++ -std=c++0x -pthread -o out copy-semantics.cpp; ./out
 */
int main()
{

  SimpleString c{50};
  c.append_line("We apologize for the");
  SimpleString c_copy{c}; // invokes a copy constructor of SimpleString
  c.append_line(" inconvenience.");
  c_copy.append_line(" another inconvenience.");
  c.print("c");
  c_copy.print("c_copy");

  // Copy assignment
  SimpleString a{50};
  a.append_line("We apologize for the");
  SimpleString b{50};
  b.append_line("Last message");
  b = a;

  return 0;
}

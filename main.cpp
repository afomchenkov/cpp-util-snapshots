#include <cstdlib>
#include <csignal>
#include <csetjmp>
#include <cstdarg>
#include <typeindex>
#include <type_traits>
#include <ctime>
#include <chrono>
#include <cstddef>
#include <initializer_list>
#include <scoped_allocator>
#include <climits>
#include <cfloat>
#include <cinttypes>
#include <limits>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <system_error>
#include <cerrno>
#include <cfenv>
#include <iosfwd>
#include <ios>
#include <istream>
#include <ostream>
#include <iomanip>
#include <streambuf>
#include <cstdio>
#include <locale>
#include <clocale>
#include <codecvt>
#include <condition_variable>
#include <ciso646>
#include <ccomplex>
#include <ctgmath>
#include <cstdbool>
#include <typeinfo>
#include <strstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cwctype>
#include <cstring>
#include <cwchar>
#include <cmath>
#include <complex>
#include <valarray>
#include <random>
#include <numeric>
#include <ratio>
#include <cstdint>

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

using namespace std;
// g++ -Wall main.cpp -o main
// clang++ -g -std=c++1y main.cpp -o main

// bool   - Boolean value, either true or false
// char   - character
// short  - short integer
// int    - integer
// long   - long integer
// float  - single-precision floating-point number double double-precision floating-point number

// Together, enums and the types bool, char, and int are called integral types.

#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i = j; i < k; i += in)
#define RFOR(i, j, k, in) for (int i = j; i >= k; i -= in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert(B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define read(type) readInt<type>()
#define fast                        \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL)
#define ONLINE_JUDGE
const double pi = acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int, int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef long long ll;
typedef unsigned long long int uint64;

template <typename T>
inline void write(T x)
{
  int i = 20;
  char buf[21];
  // buf[10] = 0;
  buf[20] = '\n';

  do
  {
    buf[--i] = x % 10 + '0';
    x /= 10;
  } while (x);
  do
  {
    putchar(buf[i]);
  } while (buf[i++] != '\n');
}

template <typename T>
inline T readInt()
{
  T n = 0, s = 1;
  char p = getchar();
  if (p == '-')
    s = -1;
  while ((p < '0' || p > '9') && p != EOF && p != '-')
    p = getchar();
  if (p == '-')
    s = -1, p = getchar();
  while (p >= '0' && p <= '9')
  {
    n = (n << 3) + (n << 1) + (p - '0');
    p = getchar();
  }

  return n * s;
}

template <typename T>
void print_vector(const vector<T> &v)
{
  for (auto i : v)
  {
    cout << i << ", ";
  }
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////

class MyClass
{
private:
  static int s_Counter;
  int *m_Member{&s_Counter};

public:
  MyClass()
  {
    ++(*m_Member);
    cout << "Constructing: " << GetValue() << endl;
  }
  MyClass(const MyClass &rhs) : m_Member{rhs.m_Member}
  {
    ++(*m_Member);
    cout << "Copying: " << GetValue() << endl;
  }
  ~MyClass()
  {
    --(*m_Member);
    m_Member = nullptr;
    cout << "Destructing: " << s_Counter << endl;
  }

  int GetValue() const
  {
    return *m_Member;
  }
};

MyClass CopyMyClass(MyClass parameter)
{
  return parameter;
}

int MyClass::s_Counter{0};

// #include <bits/stdc++.h>
// include entire std lib
// g++ compiler
// g++ -std=c++11 -O2 -Wall test.cpp -o test
// - standard (-std=c++11)
// - optimizes the code (-O2)
// - shows warnings about possible errors (-Wall)

int main()
{
  cout << endl
       << "--------- START ---------" << endl;

  cout << endl
       << "---------  END  ---------" << endl;
  return 0;
}
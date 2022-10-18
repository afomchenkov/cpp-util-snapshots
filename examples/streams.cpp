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
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <limits>

using namespace std;

// The output string streams support all the same features as an ostream. Whenever you send input 
// to the string stream, the stream stores this input into an internal buffer. You can think of 
// this as functionally equivalent to the append operation of string (except that string streams 
// are potentially more efficient).
using ostringstream = basic_ostringstream<char>;
using wostringstream = basic_ostringstream<wchar_t>;

using istringstream = basic_istringstream<char>;
using wistringstream = basic_istringstream<wchar_t>;

using stringstream = basic_stringstream<char>;
using wstringstream = basic_stringstream<wchar_t>;

using ifstream = basic_ifstream<char>;
using wifstream = basic_ifstream<wchar_t>;

// All string streams are moveable.

// g++ -std=c++0x -pthread -o out ./examples/streams.cpp; ./out
int main()
{

  ostringstream oss;
  oss << "By Grabthar's hammer, ";
  oss << "by the suns Worvan.";
  oss << "You shall be avenged.";
  const auto lazarus = oss.str();

  oss.str("I am Groot.");
  const auto groot = oss.str();

  cout << lazarus << "\n";  // "By Grabthar's hammer, by the suns of Worvan. You shall be avenged."
  cout << groot << "\n";    // "I am Groot."


  string numbers("1 2.23606 2");
  istringstream iss{ numbers };
  int a;
  float b, c, d;
  iss >> a;
  iss >> b;
  iss >> c;


  // File stream
  ofstream file{ "text.txt", ios::out|ios::app };
  file << "Time is an illusion." << endl;
  file << "Lunch time, " << 2 << "x so." << endl;

  ifstream file{ "numbers.txt" };
  auto maximum = numeric_limits<int>::min();
  int value;

  while (file >> value) {
    maximum = maximum < value ? value : maximum;
  }
  cout << "Maximum found was " << maximum << endl;


  return 0;
}
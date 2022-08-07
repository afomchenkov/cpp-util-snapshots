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
 * Summary of disallowing functions:
 *
 * 1. C++ 11: f() = delete;
 * 2. C++ 03: declare the function to be private and not define it
 * 3. private destructor: stay out of stack
 */

class OpenFile
{
public:
  OpenFile(const string &filename)
  {
    cout << "Open a file " << filename << endl;
  }

  void destroy()
  {
    delete this;
  }

private:
  // OpenFile(OpenFile& rhs);
  // OpenFile& operator=(const OpenFile& rhs);
  // OpenFile(OpenFile& rhs) = delete;
  ~OpenFile()
  {
    cout << "OpenFile destructor" << endl;
  }
};

int main()
{
  // OpenFile f1(string("m_file"));
  // OpenFile f2(f1);

  OpenFile *f = new OpenFile(string("m_file"));
  f->destroy();

  return 0;
}

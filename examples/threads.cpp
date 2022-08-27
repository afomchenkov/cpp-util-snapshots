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
#include <condition_variable>
#include <chrono>

#include <system_error>
#include <cstdio>
#include <cstdio>
#include <cstring>

using namespace std;

// Each program has one or more threads that can perform independent operations.
// The sequence of instructions that a thread executes is called its [thread of execution].

// We can attach a callback with the std::thread object, that will be executed when
// this new thread starts. These callbacks can be:
// 1.) Function Pointer
// 2.) Function Objects
// 3.) Lambda functions
//
// Thread objects can be created like this: std::thread threadObject(<CALLBACK>);
//
// New Thread will start just after the creation of new object and will execute the
// passed callback in parallel to thread that has started it. Any thread can wait
// for another to exit by calling join() function on that thread’s object.

void thread_function()
{
  for (int i = 0; i < 10000; i++) {
    std::cout << "thread function Executing" << std::endl;
  }
}

class DisplayThread
{
public:
  void operator()()
  {
    for (int i = 0; i < 10000; i++) {
      std::cout << "Display Thread Executing" << std::endl;
    }
  }
};

class WorkerThread
{
public:
  void operator()()     
  {
    std::cout << "Worker Thread " << std::this_thread::get_id() << " is Executing" << std::endl;
  }
};

void threadCallback(int x, std::string str) {
  std::cout << "Passed Number = " << x << std::endl;
  std::cout << "Passed String = " << str << std::endl;
}

void thread_function_1()
{
  std::cout << "Inside Thread :: ID  = " << std::this_thread::get_id() << std::endl;    
}

class ThreadRAII
{
std::thread & m_thread;
public:
  ThreadRAII(std::thread  & threadObj) : m_thread(threadObj) { }
  // We should not forget call either join() or detach() in case of exceptions.
  // To prevent this we should use RESOURCE ACQUISITION IS INITIALIZATION (RAII)
  ~ThreadRAII() {
    // Check if thread is joinable then detach the thread
    if(m_thread.joinable()) {
      m_thread.detach();
    }
  }
};

void newThreadCallback(int * p) {
  std::cout << "Inside Thread :  "" : p = " << p << std::endl;
  std::chrono::milliseconds dure(1000);
  std::this_thread::sleep_for(dure);
  *p = 19;
}
void startNewThread()
{
  int i = 10;
  std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
  std::thread t(newThreadCallback, &i);
  t.detach();
  std::cout << "Inside Main Thread :  "" : i = " << i << std::endl;
}

void newThreadCallbackRef(int * p) {
  std::cout << "Inside Thread :  "" : p = " << p << std::endl;
  std::chrono::milliseconds dure(1000);
  std::this_thread::sleep_for(dure);
  *p = 19;
}

void threadCallbackWithRef(int const& x) {
  // Even if threadCallback accepts arguments as reference but still changes done to it
  // are not visible outside the thread, because x in the thread function 'threadCallbackWithRef'
  // is reference to the temporary value copied at the new thread’s stack.
  int& y = const_cast<int &>(x);
  y++;
  std::cout << "Inside Thread x = " << x << std::endl;
}

class DummyClass {
public:
  DummyClass() {}
  DummyClass(const DummyClass & obj) {}
  void sampleMemberFunction(int x) {
    std::cout << "Inside sampleMemberFunction " << x <<std::endl;
  }
};

// > Race conditions
// When two or more threads perform a set of operations in parallel, that access the same memory location.
// Also, one or more thread out of them modifies the data in that memory location, then this can lead to an
// unexpected results some times.
class Wallet {
  int mMoney;
public:
  Wallet(): mMoney(0) {}
  int getMoney() {
    return mMoney;
  }
  void addMoney(int money) {
    for (int i = 0; i < money; ++i) {
      mMoney++;
    }
  }
};

int testMultithreadedWallet() {
  Wallet walletObject;
  std::vector<std::thread> threads;

  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread(&Wallet::addMoney, &walletObject, 1000));
  }
  // As all threads are modifying the shared data at same time, it might be possible that in
  // some scenarios money in wallet at the end will be much lesser than 5000.
  for (int i = 0; i < threads.size(); i++) {
    threads.at(i).join();
  }
  // To fix this problem we need to use Lock mechanism i.e. each thread need to acquire a lock before modifying
  // or reading the shared data and after modifying the data each thread should unlock the Lock.

  return walletObject.getMoney();
}

// To fix race conditions in multi-threaded environment we need mutex i.e. each thread needs to lock a mutex before
// modifying or reading the shared data and after modifying the data each thread should unlock the mutex.
// There are two important methods of mutex:
// 1. lock()
// 2. unlock()
class WalletMutex {
  int mMoney;
  std::mutex mutex;
public:
  WalletMutex(): mMoney(0) {}
  int getMoney() {
    return mMoney;
  }
  void addMoney(int money) {
    // mutex lock guarantees that Money in the WalletMutex will be 5000 in the end
    mutex.lock();
    for(int i = 0; i < money; ++i) {
      mMoney++;
    }
    mutex.unlock();
    // if we forgot to unlock the mutex at the end of function, one thread will exit without releasing the
    // lock and other threads will remain in waiting. This kind of scenario can happen in case some exception
    // came after locking the mutex. To avoid such scenarios we should use std::lock_guard
    // - std::lock_guard is a class template, which implements the RAII for mutex
  }
};

int testMultithreadedWalletMutex() {
  WalletMutex walletObject;
  std::vector<std::thread> threads;

  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread(&WalletMutex::addMoney, &walletObject, 1000));
  }

  for (int i = 0; i < threads.size(); i++) {
    // because mutex lock in addMoney makes sure that once one thread finishes the
    // modification of money then only any other thread modifies the money in Wallet
    threads.at(i).join();
  }

  return walletObject.getMoney();
}

class WalletLockGuard {
  int mMoney;
  std::mutex mutex;
public:
  WalletLockGuard(): mMoney(0) {}
  int getMoney() {
    return mMoney;
  }
  void addMoney(int money) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    // in constructor it locks the mutex
    for (int i = 0; i < money; ++i) {
      // if some exception occurs at this point then destructor of lockGuard will be called due to stack unwinding
      mMoney++;
    }
    // once function exits, then destructor of lockGuard Object will be called, in destructor it unlocks the mutex
  }
};

// Sometimes a thread needs to wait for an event to happen like a condition to become true or a task to be completed
// by another thread.
// An example of a network based application. This application does following tasks:
//   - Perform some handshaking with server
//   - Load Data from XML files
//   - Do processing on data loaded from XML
//
// Task 1 is not dependent on any other Tasks but Task 3 is dependent on Task 2, it means that Task 1 and Task 2
// can be run in parallel by different Threads to improve the performance of application.
//
// > Responsibilities of Thread 1:
//   - Perform some handshaking with server
//   - Wait for data to be loaded from XML by Thread 2
//   - Do processing on data loaded from XML
//
// > Responsibilities of Thread 2:
//   - Load data from XML
//   - Notify another Thread i.e. waiting for the message
//
// When Thread 1 is busy in some handshaking mechanism then Thread 2 will load the
// data parallel from XML, it will increase the performance of application.
class NetworkApplication {
  std::mutex m_mutex;
  bool m_bDataLoaded;
public:
  NetworkApplication() {
    m_bDataLoaded = false;
  }

  void loadData() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Loading Data from XML" << std::endl;
    // Lock The Data structure
    std::lock_guard<std::mutex> guard(m_mutex);
    // Set the flag to true, means data is loaded
    m_bDataLoaded = true;
  }

  void mainTask() {
    std::cout << "Do Some Handshaking" << std::endl;
    // Acquire the Lock
    m_mutex.lock();
    // Check if flag is set to true or not
    while (m_bDataLoaded != true) {
      // Release the lock
      m_mutex.unlock();
      // sleep for 100 milli seconds
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      // Acquire the lock
      m_mutex.lock();
    }
    // Release the lock
    m_mutex.unlock();
    // Doc processing on loaded Data
    std::cout << "Do Processing On loaded Data" << std::endl;
  }
};

// Condition Variable is a kind of Event used for signaling between two or more threads. One or more thread
// can wait on it to get signaled, while an another thread can signal this.
using namespace std::placeholders;

class ApplicationCondition {
  std::mutex m_mutex;
  std::condition_variable m_condVar;
  bool m_bDataLoaded;
public:
  ApplicationCondition() {
    m_bDataLoaded = false;
  }

  bool isDataLoaded() {
    return m_bDataLoaded;
  }

  // > Responsibilities of Thread 1:
  //   - Perform some handshaking with server
  //   - Wait for data to be loaded from XML by Thread 2
  //   - Do processing on data loaded from XML
  void mainTask() {
    std::cout << "Do Some Handshaking" << std::endl;
    // Acquire the lock
    std::unique_lock<std::mutex> mlock(m_mutex);
    // Start waiting for the Condition Variable to get signaled Wait() will internally release the lock and
    // make the thread to block. As soon as condition variable get signaled, resume the thread and
    // again acquire the lock. Then check if condition is met or not, if condition is met then continue
    // else again go in wait.
    m_condVar.wait(mlock, std::bind(&ApplicationCondition::isDataLoaded, this));
    std::cout << "Do Processing On loaded Data" << std::endl;
  }

  // > Responsibilities of Thread 2:
  //   - Load data from XML
  //   - Notify another Thread i.e. waiting for the message
  void loadData() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Loading Data from XML" << std::endl;
    std::lock_guard<std::mutex> guard(m_mutex);
    m_bDataLoaded = true;
    
    m_condVar.notify_one();
  }
};

// std::future std::promise and returning values from Thread
// Example: we created a thread that will compress a given folder and we want this thread to return
// the new zip file name and its size in result.
// 1. Old Way: Share data among threads using pointer
// 2. C++11 Way: Using std::future and std::promise
//
// std::future is a class template and its object stores the future value.
// std::future object internally stores a value that will be assigned in future and it also provides a mechanism to access
// that value i.e. using get() member function, but if somebody tries to access this associated value of future through
// get() function before it is available, then get() function will block till value is not available.
//
// std::promise is also a class template and its object promises to set the value in future. Each std::promise object
// has an associated std::future object that will give the value once set by the std::promise object.
// A std::promise object shares data with its associated std::future object.
void promise_initiazer(std::promise<int> * promObj) {
  std::cout << "Inside Thread" << std::endl;
  promObj->set_value(35);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

  // Creating a thread using Function Pointer
  std::thread threadObj1(thread_function);
  for (int i = 0; i < 10000; i++) {
    std::cout << "Display From MainThread" << std::endl;
  }
  threadObj1.join();
  std::cout << "Exit of Main function" << std::endl;

  // Creating a thread using Function Objects
  std::thread threadObj2((DisplayThread()));
  for (int i = 0; i < 10000; i++) {
    std::cout << "Display From Main Thread " << std::endl;
  }
  std::cout << "Waiting For Thread to complete" << std::endl;
  threadObj2.join();
  std::cout << "Exiting from Main Thread" << std::endl;

  // Creating a thread using Lambda functions
  int x = 9;
  std::thread threadObj3([] {
    for (int i = 0; i < 10000; i++) {
      std::cout << "Display Thread Executing" << std::endl;
    }
  });

  for (int i = 0; i < 10000; i++)
  {
    std::cout << "Display From Main Thread" << std::endl;
  }

  threadObj3.join();
  std::cout << "Exiting from Main Thread" << std::endl;

  // Each of the std::thread object has an associated ID and we can fetch using, member function,
  // gives id of associated thread object i.e. std::thread::get_id()
  // 
  // To get the identifier for the current thread use: std::this_thread::get_id()
  // If std::thread object does not have an associated thread then get_id() will return a default
  // constructed std::thread::id object i.e. not any thread.

  std::thread threadObj11(thread_function_1);
  std::thread threadObj21(thread_function_1);

  if (threadObj11.get_id() != threadObj21.get_id()) {
    std::cout << "Both Threads have different IDs" << std::endl;
  }

  std::cout << "From Main Thread :: ID of Thread 11 = " << threadObj1.get_id() << std::endl;
  std::cout << "From Main Thread :: ID of Thread 21 = " << threadObj2.get_id() << std::endl;

  threadObj11.join();
  threadObj21.join();

  // > Joining and detaching threads
  // Once a thread is started then another thread can wait for this new thread to finish.
  // For this another need need to call join() function on the std::thread object i.e.
  //
  // std::thread th(funcPtr);
  // -- Some Code
  // th.join();

  std::vector<std::thread> threadList;
  for (int i = 0; i < 10; i++) {
    threadList.push_back(std::thread(WorkerThread()));
  }
  // Now wait for all the worker thread to finish i.e. call join() function on each of the std::thread object
  std::cout << "wait for all the worker thread to finish" << std::endl;
  std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
  std::cout << "Exiting from Main Thread" << std::endl;

  // > Detaching Threads using std::thread::detach()
  // Detached threads are also called daemon/background threads. To detach a thread we need to call
  // std::detach() function on std::thread object i.e.
  //
  // std::thread th(funcPtr);
  // th.detach();
  // After calling detach(), std::thread object is no longer associated with the actual thread of execution.

  // When a join() function is called on an thread object, and in case again join() function is called on
  // such object then it will cause the program to terminate. Similarly calling detach() makes the std::thread
  // object not linked with any thread function. In that case calling 'detach' twice on an std::thread
  // object will cause the program to terminate. Therefore, before calling join() or detach() we should
  // check if thread is join-able every time i.e.
  if (threadObj11.joinable()) {
    std::cout << "Joining Thread " << std::endl;
    threadObj11.join();
  }
  if (threadObj21.joinable()) {
    std::cout << "Joining Thread " << std::endl;
    threadObj21.join();
  }

  // passing simple arguments to a thread
  std::thread threadObjWithCallback(threadCallback, 10, "Sample String");
  if (threadObjWithCallback.joinable()) {
    threadObjWithCallback.join();
  }

  // Don’t pass addresses of variables from local stack to thread’s callback function, because it
  // might be possible that local variable in Thread 1 goes out of scope but Thread 2 is still trying
  // to access it through it’s address. In such scenario accessing invalid address can cause
  // unexpected behaviour.
  // Similarly be careful while passing pointer to memory located on heap to thread. Because it might
  // be possible that some thread deletes that memory before new thread tries to access it. In such
  // scenario accessing invalid address can cause unexpected behaviour.
  startNewThread();
  std::chrono::milliseconds dure(2000);
  std::this_thread::sleep_for(dure);

  int * p = new int();
  *p = 10;
  std::cout << "Inside Main Thread :  "" : *p = " << *p << std::endl;
  std::thread tRef(newThreadCallbackRef, p);
  tRef.detach();
  delete p;

  int x1 = 9;
  std::cout << "In Main Thread : Before Thread Start x = " << x1 <<std::endl;
  std::thread threadObjWithRef(threadCallbackWithRef, x1);
  // To fix ref, use std::ref() i.e. -> std::ref(x1))
  threadObjWithRef.join();
  std::cout << "In Main Thread : After Thread Joins x = " << x1 << std::endl;
  
  // Assigning pointer to member function of a class as thread function
  DummyClass dummyObj;
  int x2 = 10;
  std::thread threadObj(&DummyClass::sampleMemberFunction, &dummyObj, x2);
  threadObj.join();

  NetworkApplication app1;
  std::thread thread_1(&NetworkApplication::mainTask, &app1);
  std::thread thread_2(&NetworkApplication::loadData, &app1);
  thread_2.join();
  thread_1.join();

  ApplicationCondition app;
  std::thread thread_1(&ApplicationCondition::mainTask, &app);
  std::thread thread_2(&ApplicationCondition::loadData, &app);
  thread_2.join();
  thread_1.join();

  // init promise/future
  std::promise<int> promiseObj1;
  std::future<int> futureObj = promiseObj1.get_future();
  std::thread th(promise_initiazer, &promiseObj1);
  std::cout << futureObj.get() << std::endl;
  th.join();

  return 0;
}

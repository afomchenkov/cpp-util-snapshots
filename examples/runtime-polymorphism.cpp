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

enum class LoggerType
{
  Console,
  File
};

struct Logger {
  virtual ~Logger() = default;
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct FileLogger : Logger
{
  void log_transfer(long from, long to, double amount) override
  {
    printf("[file] %ld -> %ld: %f\n", from, to, amount);
  }
};

struct ConsoleLogger : Logger
{
  void log_transfer(long from, long to, double amount) override
  {
    printf("[console] %ld -> %ld: %f\n", from, to, amount);
  }
};

/**
 * Adding a new kind of logging requires making several updates throughout the code:
 * 1. You need to write a new logger type.
 * 2. You need to add a new enum value to the enum class LoggerType.
 * 3. You must add a new case in the switch statementy.
 * 4. You must add the new logging class as a member to Bank.
 */
struct Bank
{
  Bank() : type{LoggerType::Console} {}

  void set_logger(LoggerType new_type)
  {
    type = new_type;
  }

  void make_transfer(long from, long to, double amount)
  {
    switch (type)
    {
      case LoggerType::Console:
      {
        consoleLogger.log_transfer(from, to, amount);
        break;
      }
      case LoggerType::File:
      {
        fileLogger.log_transfer(from, to, amount);
        break;
      }
      default:
      {
        throw std::logic_error("Unknown Logger type encountered.");
      }
    }
  }

private:
  LoggerType type;
  ConsoleLogger consoleLogger;
  FileLogger fileLogger;
};

// Defining interfaces
// To declare an interface, declare a pure virtual class.
// To implement an inter­ face, derive from it.
// Because the interface is pure virtual, an implementa­ tion must implement all of the interface’s methods.
struct LoggerInterface {
  virtual ~Logger() = default;
  // If you want to require a derived class to implement the method,
  // you can append the =0 suffix to a method definition. You call
  // methods with both the virtual keyword and =0 suffix pure virtual
  // methods. You can’t instanti­ate a class containing any pure virtual methods.
  virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLoggerImplements : LoggerInterface {
  virtual void log_transfer(long from, long to, double amount) override {
    printf("%ld -> %ld: %f\n", from, to, amount);
  }
}

struct BaseClass {
  virtual const char* final_message() const {
    return "We apologize for the incontinence.";
  }

  virtual ~BaseClass() = default;
};

struct DerivedClass : BaseClass {
  const char* final_message() const override {
    return "We apologize for the inconvenience.";
  }

  DerivedClass() {  
    printf("DerivedClass() invoked.\n");
  }
  // Adding the virtual destructor causes the DerivedClass destructor to get
  // invoked when you delete the BaseClass pointer.
  ~DerivedClass() {
    printf("~DerivedClass() invoked.\n");
  }
};
// Declaring a protected non-virtual destructor is a good alternative to declaring a public
// virtual destructor because it will cause a compilation error when writing code that deletes
// a base class pointer. Some don’t like this approach because you eventually have to make a
// class with a public destructor, and if you derive from that class, you run into the same issues.


// Constructor injection
struct BankConstructorInjection {
  BankConstructorInjection(Logger& logger) : logger{ logger } { }
  
  void make_transfer(long from, long to, double amount) {
    logger.log_transfer(from, to, amount);
  }

  private:
    Logger& logger;
};

// Property injection
struct BankPropertyInjection {
  void set_logger(Logger* new_logger) {
    logger = new_logger;
  }

  void make_transfer(long from, long to, double amount) {
    if (logger) {
      logger->log_transfer(from, to, amount);
    }
  }

private:
  Logger* logger{};
};

/**
 * g++ -std=c++0x -pthread -o out file.cpp; ./out
 */
int main()
{

  Bank bank;
  bank.make_transfer(1000, 2000, 49.95);
  bank.make_transfer(2000, 4000, 20.00);
  bank.set_logger(LoggerType::File);
  bank.make_transfer(3000, 2000, 75.00);

  BaseClass base;
  DerivedClass derived;
  BaseClass& ref = derived;
  printf("BaseClass: %s\n", base.final_message());        // BaseClass: We apologize for the incontinence.
  printf("DerivedClass: %s\n", derived.final_message());  // DerivedClass: We apologize for the inconvenience.
  printf("BaseClass&: %s\n", ref.final_message());        // BaseClass&: We apologize for the inconvenience.

  return 0;
}

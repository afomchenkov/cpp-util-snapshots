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

using namespace std;

struct HolmesIV
{
  bool is_sentient;
  int sense_of_humor_rating;
};
void mannie_service(HolmesIV *); // Takes a pointer to a HolmesIV
void mannie_service(HolmesIV &); // Takes a reference to a HolmesIV

void make_sentient(HolmesIV *mike)
{
  if (mike == nullptr)
    return;
  mike->is_sentient = true;
}
void make_sentient(HolmesIV &mike)
{
  mike.is_sentient = true;
}

// C decalration way
typedef struct Jabberwocks_s
{
  void *tugley_wood;
  int is_galumping;
} Jabberwock;
// C++ declaration way
struct Jabberwocks
{
  void *tugley_wood;
  int is_galumping;
};

namespace Creature
{
  struct Jabberwocks
  {
    void *tugley_wood;
    int is_galumping;
  };
}
namespace Func
{
  void Jabberwock()
  {
    printf("Burble!");
  }
}

// lambdas
// [capture] (arguments) { body }
// auto n_evens = std::count_if(x.begin(), x.end(), [] (auto number) { return number % 2 == 0; });

// templates
template <typename T>
T add(T x, T y, T z)
{
  return x + y + z;
}

struct Hal
{
  // sets up the Hal object and establishes its class invariants
  // Invariants are features of a class that don’t change once
  // they’ve been constructed.
  Hal() : version{9000}
  { // sets the version, which is an invariant, to 9000
    printf("operational");
  }
  ~Hal()
  {
    printf("destruct");
  }
  const int version;
};

// the resource allocation is initialization (RAII) concept
// (sometimes also called constructor acquires, destructor releases)

struct File
{
  File(const char *path, bool write)
  {
    auto file_mode = write ? "w" : "r";
    file_pointer = fopen(path, file_mode);
    if (!file_pointer)
    {
      throw system_error(errno, system_category());
    }
  }
  ~File()
  {
    fclose(file_pointer);
  }
  FILE *file_pointer;
};

// move semantics
// Sometimes, you want to transfer ownership of an object; this comes up often, for example, with unique_ptr.
// You can’t copy a unique_ptr, because once one of the copies of the unique_ptr is destructed, the remaining
// unique_ptr would hold a reference to the deleted object. Rather than copying the object, you use the move
// semantics of C++ to transfer ownership from one unique pointer to another.
struct Foundation
{
  const char *founder;
};

struct Mutant
{
  Mutant(unique_ptr<Foundation> foundation) : foundation(move(foundation)) {}
  unique_ptr<Foundation> foundation;
};

// scoped enum
enum class Race
{
  Dinan,
  Teklan,
  Ivyn,
  Moiran,
  Camite,
  Julian,
  Aidan
};
Race langobard_race = Race::Aidan;

// POD
struct Book
{
  char name[256];
  int year;
  int pages;
  bool hardcover;
};

struct ClockOfTheLongNow
{
  void add_year()
  {
    year++;
  }
  int get_year()
  {
    return year;
  }

private:
  int year;
};

// The union Variant can be interpreted as a char[10], an int, or a double.
// It takes up only as much memory as its largest member (probably string in
// this case).
// all members of a union are in the same place
union Variant
{
  char str[10];
  int integer;
  double floating_point;
};

struct PodStruct
{
  uint64_t a;
  char b[256];
  bool c;
};

// Fully featured classes are always initialized. In other words, one of a fully featured
// class’s constructors always gets called during initialization. Which constructor is called
// depends on the arguments given during initialization.
struct Taxonomist
{
  Taxonomist()
  {
    printf("(no argument)\n");
  }
  Taxonomist(char x)
  {
    printf("char: %c\n", x);
  }
  Taxonomist(int x)
  {
    printf("int: %d\n", x);
  }
  Taxonomist(float x)
  {
    printf("float: %f\n", x);
  }
  ~Taxonomist()
  {
    printf("destruct");
  }
};

struct Element
{
  Element *next{};
  void insert(Element *new_element)
  {
    new_element->next = next;
    next = new_element;
  }
  char prefix[2];
  short operating_number;
};

// An x86 architecture has 32-bit (4-byte) general-purpose registers, whereas
// an x64 architecture has 64-bit (8-byte) general-purpose registers.
struct College
{
  char name[256];
};
void print_name(College *college_ptr)
{
  printf("%s College\n", college_ptr->name);
}

// const arguments - precludes its modification within a function’s scope
void petruchio(const char *shrew)
{
  // shrew[0] = "K"; // compiler error
}
// const methods - promise not to modify the current object’s state within the const method, read-only methods
struct ClockOfTheLongNowConst
{
  int get_year() const
  {
    return year;
  }

private:
  int year;
};
// const member variables - cannot be modified after their initialization.
struct Avout
{
  const char *name = "Erasmas";
};

// static - declared via static or extern at global (or namespace) scope
// global - allocated when program starts and deallocated when the program stops
//          and can be accessed from any function in the translation unit
//          (a translation unit is what a preprocessor produces after acting on a single source file)
static int rat_things_power = 200;
// When you use the static keyword, you specify internal linkage. Internal
// linkage means that a variable is inaccessible to other translation units. You can
// alternately specify external linkage, which makes a variable accessible to other
// translation units. For external linkage, you use the extern keyword instead of static.
extern int rat_things_power_extern = 200;

// A local static variable is a special kind of static variable that is a local—rather
// than global—variable. Local static variables are declared at function scope, just
// like automatic variables. But their lifetimes begin upon the first invocation of
// the enclosing function and end when the program exits.
void power_up_rat_thing(int nuclear_isotopes)
{
  static int rat_things_power = 200;
  rat_things_power = rat_things_power + nuclear_isotopes;
  const auto waste_heat = rat_things_power * 20;
  if (waste_heat > 10000)
  {
    printf("Warning! Hot doggie!\n");
  }
  printf("Rat-thing power: %d\n", rat_things_power);
}

// Static members are members of a class that aren’t associated with a particular instance of the class.
// Normal class members have lifetimes nested within the class’s lifetime, but static members have
// static storage duration. You must ini- tialize static members at global scope. You cannot initialize
// a static member within a containing class definition.
struct RatThing
{
  static int rat_things_power;
  static void power_up_rat_thing(int nuclear_isotopes)
  {
    rat_things_power = rat_things_power + nuclear_isotopes;
    const auto waste_heat = rat_things_power * 20;
    if (waste_heat > 10000)
    {
      printf("Warnings! Hot doggie!\n");
    }
    printf("Rat-thing power: %d\n", rat_things_power);
  }
};
int RatThing::rat_things_power = 200;
// You can modify any variable with static storage duration to have thread-local storage duration
// by adding the thread_local keyword to the static or extern keyword. If only thread_local is
// specified, static is assumed. The vari- able’s linkage is unchanged.
void power_up_rat_thing_thread(int nuclear_isotopes)
{
  // Now each thread would represent its own Rat Thing, if one thread modifies its rat_things_power,
  // the modification will not affect the other threads
  static thread_local int rat_things_power = 200;
}

// DYNAMIC STORAGE DURATION
// Objects with dynamic storage duration are allocated and deallocated on request.
void dynamic_allocation()
{
  int *my_int_ptr = new int;
  int *my_int_ptr_1 = new int{42};
  // deallocate dynamic objects using the delete expression
  // delete expressions always return void
  delete my_int_ptr;
}

// dynamic arrays - new MyType[n_elements] { init-list }
void dynamic_arrays()
{
  int *my_int_array_ptr = new int[100];

  delete[] my_int_array_ptr;
}

// EXCEPTIONS
struct Groucho
{
  void forget(int x)
  {
    if (x == 0)
    {
      throw std::runtime_error{"Make an exception"};
    }
    printf("Forgot");

    // handling exceptions
    // When an exception is thrown, a catch block handles the exception if the thrown exception’s
    // type matches the catch handler’s exception type or if the thrown exception’s type inherits
    // from the catch handler’s exception type.
    try
    {
      throw std::logic_error{"It's not about who wrong "
                             "it's not about who right"};
    }
    catch (std::exception &ex)
    {
      // Handles std::logic_error as it inherits from std::exception
    }

    // this handler catches any exception regardless of its type
    try
    {
      throw 'z'; // Don't do this.
    }
    catch (...)
    {
      // Handles any exception, even a 'z'
    }

    // exceptions chaining
    //
    // try
    // {
    //   // Code that might throw an exception --snip--
    // }
    // catch (const std::logic_error &ex)
    // {
    //   // Log exception and terminate the program; there is a programming error! --snip--
    // }
    // catch (const std::runtime_error &ex)
    // { // Do our best to recover gracefully --snip--
    // }
    // catch (const std::exception &ex)
    // {
    //   // This will handle any exception that derives from std:exception // that is not a logic_error or a runtime_error.
    //   --snip--
    // }
    // catch (...)
    // {
    //   // Panic; an unforeseen exception type was thrown --snip--
    // }
  }
};

// You can, and should, mark any function that cannot possibly throw an exception noexcept
// Functions marked noexcept make a rigid contract. When you’re using a function marked
// noexcept, you can rest assured that the function cannot throw an exception.
bool is_odd(int x) noexcept
{
  return 1 == (x % 2);
}

struct SimpleString
{
  SimpleString(size_t max_size) : max_size{max_size}, length{}
  {
    if (max_size == 0)
    {
      throw std::runtime_error{"Max size must be at least 1"};
    }

    buffer = new char[max_size];
    buffer[0] = 0;
  }
  ~SimpleString()
  {
    // This pattern is called resource acquisition is initialization (RAII) or
    // constructor acquires, destructor releases (CADRe).
    delete[] buffer;
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

struct SimpleStringOwner
{
  SimpleStringOwner(const char *x) : str{10}
  {
    if (!str.append_line(x))
    {
      throw std::runtime_error{"Not enough memory"};
    }
    str.print("Constructed");
  }
  ~SimpleStringOwner()
  {
    str.print("About to destroy");
  }
private:
  SimpleString str;
};

// copy constructor
struct SimpleStringCopy : SimpleString {
  SimpleStringCopy(const SimpleStringCopy& other):
    max_size{ other.max_size },
    buffer{ new char[other.max_size] },
    length{ other.length } {
      std::strncpy(buffer, other.buffer, max_size);
  }

  // - assignment operator
  // The major difference between copy assignment and copy construction is that in copy assignment,
  // b might already have a value. You must clean up b’s resources before copying a.
  SimpleStringCopy& operator =(const SimpleStringCopy& other) {
    if (this == &other) return *this;

    const auto new_buffer = new char[other.max_size];
    delete[] buffer;
    buffer = new_buffer;
    length = other.length;
    max_size = other.max_size;
    strcpy_s(buffer, max_size, other.buffer);
    return *this;
  }
};

/**
 * @brief
 * g++ -std=c++0x -pthread -o out general.cpp; ./out
 */
int main()
{
  int a = 0;  // Initialized to 0
  int b{};    // Initialized to 0
  int c = {}; // Initialized to 0
  int d;      // Initialized to 0 (maybe)

  int e = 42;   // Initialized to 42
  int f{42};    // Initialized to 42
  int g = {42}; // Initialized to 42
  int h(42);    // Initialized to 42

  auto the_answer{42};           // int
  auto foot{12L};                // long
  auto rootbeer{5.0F};           // float
  auto cheeseburger{10.0};       // double
  auto politifact_claims{false}; // bool
  auto cheese{"string"};         // char[7]

  auto year{2019};               // int
  auto &year_ref = year;         // int&
  const auto &year_cref = year;  // const int&
  auto *year_ptr = &year;        // int*
  const auto *year_cptr = &year; // const int*

  PodStruct initialized_pod1{};            // all fields zeroed
  PodStruct initialized_pod2 = {};         // all fields zeroed
  PodStruct initialized_pod3{42, "Hello"}; // fields a & b set; c = 0
  // The order of arguments from left to right matches the order of members
  // from top to bottom. Any omitted members are zeroed.
  PodStruct initialized_pod4{42, "Hello", true}; // all fields set
  // PodStruct initialized_pod(42, "Hello", true); // will not compile

  int array_1[]{1, 2, 3};  // Array of length 3; 1, 2, 3
  int array_2[5]{};        // Array of length 5; 0, 0, 0, 0, 0
  int array_3[5]{1, 2, 3}; // Array of length 5; 1, 2, 3, 0, 0
  int array_4[5];          // Array of length 5; uninitialized values

  Taxonomist t1;
  Taxonomist t2{'c'};
  Taxonomist t3{65537};
  Taxonomist t4{6.02e23f};
  Taxonomist t5('g');
  Taxonomist t6 = {'l'};
  Taxonomist t7{};
  Taxonomist t8();

  int key_to_the_universe[]{3, 6, 9};
  int *key_ptr = key_to_the_universe; // Points to 3

  // best_colleges array decays into a pointer when you call print_name. Because arrays decay into
  // pointers to their first element, college_ptr points to the first College in best_colleges.
  College best_colleges[] = {"Magdalen", "Nuffield", "Kellogg"};
  // Pointer arithmetic, the set of rules for addition and subtraction on pointers, provides an alternate
  // approach. When you add or subtract integers to pointers, the compiler figures out the correct byte
  // offset using the size of the pointedto type. For example, adding 4 to a uint64_t pointer adds 32 bytes
  // a uint64_t takes up 8 bytes, so 4 of them take up 32 bytes.
  College oxford[] = {"Magdalen", "Nuffield", "Kellogg"};
  College *third_college_ptr1 = &oxford[2];
  College *third_college_ptr2 = oxford + 2;
  print_name(best_colleges);

  // Sometimes the pointedto type is irrelevant. In such situations, you use the void pointer void*. The void
  // pointers have important restrictions, the principal of which is that you cannot dereference a void*.

  try
  {
    // > Some code that might throw a std::exception
    // When an exception is thrown, the stack unwinds until an
    // exception handler is found, at which point the program recovers.

    auto h1 = new Hal{};
    delete h1;

    File file("text.txt", true);
    const auto message = "Exception has occurred";
    fwrite(message, strlen(message), 1, file.file_pointer);

    {
      // The bracesuwdefine a scope. Because the first file resides
      // within this scope, the scope defines the lifetime of file.
      File file("text.txt", false);
      char read_message[37]{};
      fread(read_message, sizeof(read_message), 1, file.file_pointer);
      printf("Read last message: %s\n", read_message);
    }

    // Smart pointers manage the life cycle of dynamic objects through an ownership model.
    // Once no smart pointer owns a dynamic object, the object destructs.
    std::unique_ptr<Foundation> second_foundation{new Foundation{}};
    // Access founder member variable just like a pointer:
    second_foundation->founder = "Wanda";

    // Smart pointers differ from regular, raw pointers because a raw pointer is simply
    // a memory address. You must orchestrate all the memory managment that’s involved
    // with the address manually.

    // move semantics
    {
      std::unique_ptr<Foundation> second_foundation{new Foundation{}};
      Mutant the_mule{std::move(second_foundation)};
      // second_foundation is in a 'moved-from' state, the_mule owns the Foundation
    }
  }
  catch (const std::exception &e)
  {
    // recover the program here
  }

  Element trooper1, trooper2, trooper3;
  trooper1.prefix[0] = 'T';
  trooper1.prefix[1] = 'K';
  trooper1.operating_number = 421;
  trooper1.insert(&trooper2);
  trooper2.prefix[0] = 'F';
  trooper2.prefix[1] = 'N';
  trooper2.operating_number = 2187;
  trooper2.insert(&trooper3);
  trooper3.prefix[0] = 'L';
  trooper3.prefix[1] = 'S';
  trooper3.operating_number = 005;

  for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
    printf("stormtrooper %c%c-%d\n",
           cursor->prefix[0],
           cursor->prefix[1],
           cursor->operating_number);
  }

  SimpleStringCopy a1;
  SimpleStringCopy a_copy{ a1 }; // invokes copy constructor

  return 0;
}

## The compiler tool chain

> The preprocessor performs basic source code manipulation. For example, #include <cstdio>
a directive that instructs the preprocessor to include information about the cstdio library
directly into your program’s source code. When the preprocessor finishes processing a source
file, it produces a single translation unit. Each translation unit is then passed to the compiler
for further processing.

> The compiler reads a translation unit and generates an object file. Object files contain an
intermediate format called object code. These files contain data and instructions in an intermediate
format that most humans wouldn’t understand. Compilers work on one translation unit at a time, so each
translation unit corresponds to a single object file.

> The linker generates programs from object files. Linkers are also responsible for finding the libraries
you’ve included within your source code. When you compile, for example, the linker will find the cstdio
library and include everything your program needs to use the printf function. Note that the cstdio header
is distinct from the cstdio library. The header contains information about how to use the library. You’ll
learn more about libraries and source code organization in Chapter 21.

- floating-point types take up a finite amount of mem- ory, which is called the type’s precision.
The more precision a floating-point type has, the more accurate it will be at approximating a
real number. As with integer types, each floating-point representation depends on implementation.

float - single precision
double - double precision
long double - extended precision

On major desktop operating systems, the float level usually has 4 bytes of precision. The double and
long double levels usually have 8 bytes of preci- sion (double precision).

## Object lifetime, allocation, deallocation
Each object passes through the following stages:
1. The object’s storage duration begins, and storage is allocated.
2. The object’s constructor is called.
3. The object’s lifetime begins.
4. You can use the object in your program.
5. The object’s lifetime ends.
6. The object’s destructor is called.
7. The object’s storage duration ends, and storage is deallocated.

## stdlib Exception Classes
The stdlib provides you with the standard exception classes in the <stdexcept> header.
The superclass for all the standard exception classes is the class std::exception. All the
subclasses in std::exception can be partitioned into three groups:
```
- logic errors
- runtime errors
- language support errors

            exception
                |
         ----------------
        |                |
  runtime_error      logic_error
  system_error       domain_error
  underflow_error    invalid_argument
  overflow_error     length_error
                     out_of_range

  bad_cast
  bad_alloc
```

You can define your own exceptions whenever you’d like; usually, these user-defined exceptions inherit
from std::exception. All the classes from stdlib use exceptions that derive from std::exception.
This makes it easy to catch all exceptions, whether from your code or from the stdlib, with a single 
catch block.

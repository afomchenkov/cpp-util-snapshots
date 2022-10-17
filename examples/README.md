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

> When you implement copy behavior, think about the following criteria:
> - Correctness: You must ensure that class invariants are maintained.
> - Independence: After copy assignment or copy construction, the original object and the copy shouldn’t change
>   each other’s state during modification.
> - Equivalence: The original and the copy should be the same. The semantics of sameness depend on context.
>   But generally, an operation applied to the original should yield the same result when applied to the copy.

In C++ value categories are complicated:
- an expression can be a “generalized lvalue” (glvalue)
- a “pure rvalue” (prvalue)
- an “expiring value” (xvalue)
- an lvalue (a glvalue that isn’t an xvalue)
- an rvalue (a prvalue or an xvalue)

An lvalue is any value that has a name, and an rvalue is anything that isn’t an lvalue.

Compiler-Generated Methods
Five methods govern move and copy behavior:
• The destructor
• The copy constructor
• The move constructor
• The copy assignment operator
• The move assignment operator


## Runtime/Compile-time polymorphism

Virtual functions can incur runtime overhead, although the cost is typically low (within 25 
percent of a regular function call). The compiler generates virtual function tables (vtables) 
that contain function pointers. At runtime, a consumer of an interface doesn’t generally know 
its underlying type, but it knows how to invoke the interface’s methods (thanks to the vtable). 
In some circumstances, the linker can detect all uses of an interface and devirtualize a 
function call. This removes the function call from the vtable and thus eliminates associated 
runtime cost.

The compiler cannot know ahead of time how much memory to allocate for the underlying type:
if the compiler could know the underlying type, you would be better off using templates.
> There are two options for how to set the member:
> - Constructor injection: With constructor injection, you typically use an interface reference.
>   Because references cannot be reseated, they won’t change for the lifetime of the object.
> - Property injection: With property injection, you use a method to set a pointer member. This 
>   allows you to change the object to which the member points.

You can combine these approaches by accepting an interface pointer in a constructor while also 
providing a method to set the pointer to some­ thing else.

When you want polymorphism, you should use templates. But sometimes you can’t use templates 
because you won’t know the types used with your code until runtime. Remember that template
instantiation only occurs when you pair a template’s parameters with types. At this point,
the compiler can instantiate a custom class for you. In some situations, you might not be able
to perform such pairings until your program is executing (or, at least, performing such pairing
at compile time would be tedious). In such cases, you can use runtime polymorphism. Whereas
the template is the mechanism for achieving compile-time polymorphism, the runtime mechanism
is the interface.

Every smart pointer has an ownership model that specifies its relationship with a dynamically
allocated object. When a smart pointer owns an object, the smart pointer’s lifetime is
guaranteed to be at least as long as the object’s. Put another way, when you use a smart
pointer, you can rest assured that the pointed-to object is alive and that the pointed-to
object won’t leak. The smart pointer manages the object it owns, so you can’t forget to destroy
it thanks to RAII.

## Allocators
Allocators are low-level objects that service requests for memory. The stdlib and Boost 
libraries enable you to provide allocators to customize how a library allocates dynamic memory.
In the majority of cases, the default allocator std::allocate is totally sufficient. It allocates 
memory using operator new(size_t), which allocates raw memory from the free store, also known 
as the heap. It deallocates memory using operator delete(void*), which deallocates the raw 
memory from the free store.
The idea behind a custom allocator is that you know a lot more about your specific program 
than the designers of the default allocator model, so you can make improvements that will 
increase allocation performance.

At a minimum, you need to provide a template class with the following characteristics for 
it to work as an allocator:
• An appropriate default constructor
• A value_type member corresponding to the template parameter
• A template constructor that can copy an allocator’s internal state while dealing with a change in value_type
• An allocate method
• A deallocate method
• An operator== and an operator!=

## Iterators
The interface between containers and algorithms is the iterator. An iterator is a type that 
knows the internal structure of a container and exposes simple, pointer-­like operations to a 
container’s elements.
Iterators come in various flavors, but they all support at least the follow­ing operations:
1. Get the current element (operator*)
2. Go to the next element (operator++)
3. Assign an iterator equal to another iterator (operator=)

# unique_ref
unique reference implementation in C++ (similar to unique_ptr)

## How to use it

Just `#include "unique_ptr.hpp"`, it's a single header library!

You can import "unique_ptr" namespace `using unique_ptr::uref` to get `uref` class,
or just use it like `unique_ptr::uref<MyClass> obj` to create `MyClass& obj` equivalent.

What is the advantage over regular reference?

This should be used when you cannot really stack alloc your object, but still don't want
to use a pointer... if you use `uref` we will manage the memory for you (using `std::unique_ptr`
  in the background).

## C++ Requirements

C++14 standard is required (for `make_unique`).

## License

This project is MIT licensed, so feel free to use and share it!

2020 

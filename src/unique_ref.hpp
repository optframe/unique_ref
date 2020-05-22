#pragma once

#include <memory>

// Author: Igor M. Coelho
// May 2020
// unique_ref: an implementation of unique references (similar to std::unique_ptr)
// The namespace is called 'unique_ref', but decided to name class 'uref' to keep name shorter
// Please inform if there's any name conflict with "bigger" projects
//   (if it's necessary to change it for some reason, file an Issue on 'https://github.com/optframe/unique_ref')
//
// MIT License

//
// declaring namespace 'unique_ref'
//
namespace unique_ref {
//
// ====================== uref class ========================
// the only requirement here is a copy constructor for 'T'
//
// method 'ref()' returns the internal reference
// operator-> gives pointer navigation to T fields
// operator* gives a reference of T object
// operator T() gives implicit copy construction of object
//
template<class T>
class uref final // 'uref' is shorter than 'unique_ref'
{
private:
   std::unique_ptr<T> _t;

public:
   // 'make_unique' requires concrete type T
   explicit uref(const uref<T>&& other) noexcept
     : _t{ std::make_unique<T>(std::move(*other._t)) }
   {
   }

   // 'make_unique' requires concrete type T
   explicit uref(const uref<T>& other) noexcept
     : _t{ std::make_unique<T>(*other._t) }
   {
   }

   // 'make_unique' requires concrete type T
   explicit uref(const T& t) noexcept
     : _t{ std::make_unique<T>(t) }
   {
   }

   // constructor useful for abstract reference types
   // beware that this may inject null inside this reference
   explicit uref(std::unique_ptr<T>&& uptr) noexcept
     : _t{ std::move(uptr) }
   {
   }

   T& ref() { return *_t; }
   const T& ref() const { return *_t; }

   // returns pointer (beware to not break element!)
   T* operator->() { return _t.get(); }
   const T* operator->() const { return _t.get(); }

   // returns reference (beware to not break element!)
   T& operator*() { return *_t; }
   const T& operator*() const { return *_t; }

   // issue: 'is_abstract' requires type 'T' to be complete at this point... not always the case!
   /*
   // conversion copy (requires concrete type T) - SFINAE protection against abstract classes
   template<typename NonAbstractT =
              std::enable_if<!std::is_abstract<T>::value>>
   operator NonAbstractT() const
   {
      return std::move(NonAbstractT{ *_t });
   } // returns copy/move

   // SFINAE protection for the function below
   //operator T() const { return std::move(T{ *_t }); } // returns copy/move
*/
};

//
} // namespace unique_ref
//

//
// ============== SIMPLE USAGE ==============
// Just create an object 'uref<YourType>' and this is
//  "equivalent" to 'YourType&', with automatic memory management.
//
//
// #include "unique_ref.hpp" // single header lib
// using unique_ref::uref;   // gets class 'uref'
//
// class XYZ {
//  ...
//  uref<X> x;               // declares "reference" to 'X' (it's actually a pointer...)
//
//  XYZ(const X& _x) :       // constructor of XYZ must give an initialization for x object
//    x{_x}
//  {
//   ...
//  }
//
// That's it! Good luck.
//

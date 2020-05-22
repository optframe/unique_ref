#include <iostream>

#include "src/unique_ref.hpp"
//
using unique_ref::uref; // unique reference
using unique_ref::ucref; // unique reference only for concrete types

class XAbstract
{
public:
   virtual void print() = 0;
};

class XConcrete : public XAbstract
{
public:
   int x{0};
   void print() override {}
};

class Incomplete; // forward decl.

class UseIncomplete
{
public:
   static uref<Incomplete> r;
};

class Incomplete
{
public:
   void iprint(){};
};

uref<Incomplete> UseIncomplete::r{Incomplete{}};

int main()
{
   ucref<XConcrete> refX{XConcrete{}};
   int y = refX->x;

   XConcrete c1 = *refX; // copy
   XConcrete c2 = refX;  // copy without operator*... nice! only possible on 'ucref' type

   // cannot use 'ucref' for abstract types! use general 'uref'
   uref<XAbstract> refXA{std::unique_ptr<XAbstract>{new XConcrete{}}};

   XAbstract &c3 = *refXA; // ok, reference passing
   //XConcrete c4 = refXA; // cannot do this! abstract type!

   UseIncomplete use;
   use.r->iprint();

   return 0;
}

#include <iostream>

#include "src/unique_ref.hpp"
//
using unique_ref::uref;

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

int main()
{
   uref<XConcrete> refX{XConcrete{}};
   int y = refX->x;

   XConcrete c1 = *refX; // copy
   XConcrete c2 = refX;  // copy (without operator*... easy!)

   uref<XAbstract> refXA{std::unique_ptr<XAbstract>{new XConcrete{}}};

   XAbstract& c3 = *refXA; // ok, reference passing
   //XConcrete c4 = refXA; // cannot do this! abstract type!

   return 0;
}

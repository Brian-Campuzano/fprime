#ifndef TestLibrary_TestComponent_HPP
#define TestLibrary_TestComponent_HPP

#include <TestLibrary2/TestComponent/TestComponentComponentAc.hpp>

namespace TestLibrary2 {

class TestComponent : public TestComponentComponentBase
{
  public:
    TestComponent(const char* name);
    ~TestComponent();
  private:
    void schedIn_handler(FwIndexType portNum, U32 context);
};

};
#endif

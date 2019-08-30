//
// ... Testing header files
//
#include <gtest/gtest.h>

//
// ... Type Utility header files
//
#include <type_utility/type.hpp>

namespace // anonymous
{
  using TypeUtility::Core::Type;
  
}// end of anonymous namespace

namespace TypeUtility::Testing
{

  TEST( Type, Contruction )
  {
    constexpr Type<int> tint{};
  }

} // end of namespace TypeUtility::Testing

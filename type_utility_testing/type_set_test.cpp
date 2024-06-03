//
// ... Type Utility header files
//
#include <type_utility/type_set.hpp>

//
// ... Testing header files
//
#include <gtest/gtest.h>

namespace TypeUtility::Core::Testing {

  TEST(type_utility, type_set)
  {
    ASSERT_TRUE(!type_set<>.ismember(type<int>));
    ASSERT_TRUE(type_set<int>.ismember(type<int>));
    ASSERT_TRUE(ismember(type_set<short, int>, type<int>));
    ASSERT_TRUE(ismember(type_set<int, short>, type<int>));
  }

} // end of namespace TypeUtility::Core::Testing

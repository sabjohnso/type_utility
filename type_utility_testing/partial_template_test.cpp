//
// ...  TypeUtility header files
//
#include <type_utility/type_utility.hpp>

//
// ... Testing header files
//
#include <gtest/gtest.h>

namespace TypeUtility::Testing {

  template<typename... Ts>
  struct K
  {};

  struct T1
  {};

  struct T2
  {};

  TEST(Partial_template, Empty)
  {
    constexpr auto ptmplt = partial_template<K>;
    static_assert(ptmplt.size() == 0);
    ASSERT_EQ(ptmplt.size(), 0);
  }

  TEST(Partial_template, One_parameter)
  {
    constexpr auto ptmplt = partial_template<K, T1>;
    ASSERT_EQ(ptmplt.size(), 1);
    ASSERT_EQ(ptmplt[nat<0>], type<T1>);
  }

  TEST(Partial_template, Tw_parameters)
  {
    constexpr auto ptmplt = partial_template<K, T1, T2>;
    ASSERT_EQ(ptmplt.size(), 2);
    ASSERT_EQ(ptmplt[nat<0>], type<T1>);
    ASSERT_EQ(ptmplt[nat<1>], type<T2>);
  }

} // end of namespace TypeUtility::Testing

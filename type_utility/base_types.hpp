#pragma once

//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/import.hpp>
#include <type_utility/type_sequence.hpp>

namespace TypeUtility::Core {

  template<size_t size, typename T>
  struct has_sizeof : conditional_t<sizeof(T) == size, true_type, false_type>
  {};

  template<size_t size>
  struct make_size_predicate
  {
    template<typename T>
    using pred = has_sizeof<size, T>;
  };

  using Signed_integer_types = Type_sequence<char, short, int, long, long long>;

  template<size_t size>
  using Int =
    typename decltype(Signed_integer_types::first_sat<
                      make_size_predicate<size / 8>::template pred>())::type;

  using Unsigned_integer_types = Type_sequence<
    unsigned char,
    unsigned short,
    unsigned,
    unsigned long,
    unsigned long long>;

  template<size_t size>
  using UInt =
    typename decltype(Unsigned_integer_types::first_sat<
                      make_size_predicate<size / 8>::template pred>())::type;

  using Floating_point_types = Type_sequence<float, double, long double>;

  template<size_t size>
  using Float =
    typename decltype(Floating_point_types::first_sat<
                      make_size_predicate<size / 8>::template pred>())::type;

} // end of namespace TYPE_UTILITY_NAMESPACE::Core

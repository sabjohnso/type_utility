#pragma once
//
// ... Type Utility header files
//
#include <type_utility/integer.hpp>
#include <type_utility/type_sequence.hpp>

namespace TypeUtility::Core {

  constexpr auto drop(Type_sequence<>, Nat<0>) { return types<>; }

  template<typename T, typename... Ts>
  constexpr auto drop(Type_sequence<T, Ts...>, Nat<0>)
  {
    return types<T, Ts...>;
  }

  template<typename T, typename... Ts, size_t N>
  constexpr auto drop(Type_sequence<T, Ts...>, Nat<N>)
  {
    return drop(types<Ts...>, nat<N - 1>);
  }

  template<typename I, I x, I... xs>
  constexpr auto drop(Integer_sequence<I, x, xs...>, Nat<0>)
  {
    return integers<I, x, xs...>;
  }

  template<typename I>
  constexpr auto drop(Integer_sequence<I>, Nat<0>)
  {
    return integers<I>;
  }

  template<typename I, I x, I... xs, size_t N>
  constexpr auto drop(Integer_sequence<I, x, xs...>, Nat<N>)
  {
    return drop(integers<I, xs...>, nat<N - 1>);
  }

  constexpr auto drop(index_sequence<>, Nat<0>) { return index_sequence<>(); }

  template<size_t x, size_t... xs>
  constexpr auto drop(index_sequence<x, xs...>, Nat<0>)
  {
    return index_sequence<x, xs...>();
  }

  template<size_t x, size_t... xs, size_t N>
  constexpr auto drop(index_sequence<x, xs...>, Nat<N>)
  {
    static_assert(
      length(index_sequence<x, xs...>()) - N ==
      length(drop(index_sequence<xs...>(), nat<N - 1>)));

    return drop(index_sequence<xs...>(), nat<N - 1>);
  }

} // end of namespace TypeUtility::Core

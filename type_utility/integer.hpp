#pragma once

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>
#include <type_utility/type.hpp>
#include <type_utility/type_sequence_utility.hpp>

namespace TypeUtility::Core {

  template<size_t N>
  struct Nat
  {

    static constexpr size_t value = N;

    template<size_t M>
    friend constexpr bool
    operator<(const Nat&, const Nat<M>&)
    {
      return N < M;
    }

    template<size_t M>
    friend constexpr bool
    operator<=(const Nat&, const Nat<M>&)
    {
      return N <= M;
    }

    template<size_t M>
    friend constexpr bool
    operator>(const Nat&, const Nat<M>&)
    {
      return N > M;
    }

    template<size_t M>
    friend constexpr bool
    operator>=(const Nat&, const Nat<M>&)
    {
      return N >= M;
    }

    template<size_t M>
    friend constexpr bool
    operator==(const Nat&, const Nat<M>&)
    {
      return N == M;
    }

    template<size_t M>
    friend constexpr bool
    operator!=(const Nat&, const Nat<M>&)
    {
      return N != M;
    }

    template<size_t M>
    friend constexpr auto
    operator+(const Nat&, const Nat<M>&)
    {
      return Nat<N + M>();
    }

    template<size_t M>
    friend constexpr auto
    operator-(const Nat&, const Nat<M>&)
    {
      static_assert(N > M, "Underflow");
      return Nat<N - M>();
    }

    template<size_t M>
    friend constexpr auto
    operator*(const Nat&, const Nat<M>&)
    {
      return Nat<N - M>();
    }

    template<size_t M>
    friend constexpr auto
    operator/(const Nat&, const Nat<M>&)
    {
      return Nat<N / M>();
    }

    template<size_t M>
    friend constexpr auto
    operator%(const Nat&, const Nat<M>&)
    {
      return Nat<N % M>();
    }

    template<typename Stream>
    friend Stream&
    operator<<(Stream& os, Nat)
    {
      os << "nat<" << N << ">";
      return os;
    }

  }; // end of class

  template<size_t N>
  constexpr auto nat = Nat<N>{};

  template<typename T, T... xs>
  struct Integer_sequence
  {
    using value_type = T;
    static constexpr size_t extent = count_types<decltype(xs)...>();
    static constexpr T values[] = { xs... };

    constexpr Integer_sequence() {}

    constexpr Integer_sequence(integer_sequence<T, xs...>) {}

    friend constexpr bool
    operator==(const Integer_sequence&, const Integer_sequence&)
    {
      return true;
    }

    template<T... ys>
    friend constexpr bool
    operator==(const Integer_sequence&, const Integer_sequence<T, ys...>&)
    {
      return false;
    }

    template<typename U>
    friend constexpr bool
    operator!=(const Integer_sequence&, const U&)
    {
      return !(Integer_sequence() == U());
    }

  }; // end of struct Integer_sequence

  template<typename T, T x>
  using Integer = integral_constant<T, x>;

  template<typename T, T x>
  constexpr auto integer = integral_constant<T, x>{};

  template<typename Stream, typename T, T x>
  Stream&
  operator<<(Stream& os, Integer<T, x>)
  {
    os << '[' << x << ':' << type<T> << ']';
    return os;
  }

  template<typename T, T x, T y>
  constexpr auto operator+(Integer<T, x>, Integer<T, y>)
  {
    return integer<T, x + y>;
  }

  template<typename T, T x, T y>
  constexpr auto operator-(Integer<T, x>, Integer<T, y>)
  {
    return integer<T, x - y>;
  }

  template<typename T, T x, T y>
  constexpr auto operator*(Integer<T, x>, Integer<T, y>)
  {
    return integer<T, x * y>;
  }

  template<typename T, T x, T y>
  constexpr auto operator/(Integer<T, x>, Integer<T, y>)
  {
    return integer<T, x / y>;
  }

  template<typename T, T x, T y>
  constexpr auto operator%(Integer<T, x>, Integer<T, y>)
  {
    return integer<T, x % y>;
  }

  template<typename T, T x>
  constexpr auto succ(Integer<T, x>)
  {
    return integer<T, x + 1>;
  }

  template<typename T, T x>
  constexpr auto pred(Integer<T, x>)
  {
    return integer<T, x - 1>;
  }

  template<typename T, T... xs>
  constexpr auto integers = Integer_sequence<T, xs...>{};

  template<typename T, T x, T... xs, T... ys>
  constexpr bool
  operator==(
    const integer_sequence<T, x, xs...>&,
    const integer_sequence<T, x, ys...>&)
  {
    return integers<T, xs...> == integers<T, ys...>;
  }

  template<typename T, T x, T... xs, T... ys>
  constexpr bool
  operator==(
    const integer_sequence<T, x, xs...>&,
    const integer_sequence<T, ys...>&)
  {
    return false;
  }

  template<typename T, T... xs, T y, T... ys>
  constexpr bool
  operator==(
    const integer_sequence<T, xs...>&,
    const integer_sequence<T, y, ys...>&)
  {
    return false;
  }

  template<typename T>
  constexpr bool
  operator==(const integer_sequence<T>&, const integer_sequence<T>&)
  {
    return true;
  }

  template<typename T, T... xs, T... ys>
  constexpr bool
  operator!=(
    const integer_sequence<T, xs...>&,
    const integer_sequence<T, ys...>&)
  {
    return !(integer_sequence<T, xs...>() == integer_sequence<T, ys...>());
  }

  template<typename T, T y>
  constexpr bool ismember(Integer_sequence<T>, integral_constant<T, y>)
  {
    return false;
  }

  template<typename T, T x, T... xs>
  constexpr bool ismember(
    Integer_sequence<T, x, xs...>,
    integral_constant<T, x>)
  {
    return true;
  }

  template<typename T, T x, T... xs, T y>
  constexpr bool ismember(
    Integer_sequence<T, x, xs...>,
    integral_constant<T, y>)
  {
    return ismember(integers<T, xs...>, integer<T, y>);
  }

  template<typename T, T... xs>
  struct Are_unique_integers : Are_unique<Type<integral_constant<T, xs>...>>
  {};

  template<typename T>
  struct Are_unique_integers<T> : true_type
  {};

  template<typename F, typename T, T... xs>
  constexpr auto
  integer_sequence_transform(F f, Integer_sequence<T, xs...>)
  {
    return Integer_sequence<decay_t<result_of_t<F(T)>>, f(xs)...>{};
  }

  template<size_t N, size_t... Indices>
  struct Generate_indices;

  template<size_t N, size_t... Indices>
  struct Generate_indices : Generate_indices<N - 1, N - 1, Indices...>
  {};

  template<size_t... Indices>
  struct Generate_indices<0, Indices...> : Type<index_sequence<Indices...>>
  {};

  template<size_t N>
  constexpr auto
  generate_indices()
  {
    return typename Generate_indices<N>::type{};
  }

  template<typename... Ts>
  constexpr auto
  generate_indices()
  {
    return generate_indices<count_types<Ts...>()>();
  }

  template<size_t index, size_t... indices>
  constexpr auto rotate(index_sequence<index, indices...>)
  {
    return index_sequence<indices..., index>();
  }

  template<typename I, I... xs>
  constexpr size_t length(Integer_sequence<I, xs...>)
  {
    return count_types<decltype(xs)...>();
  }

  template<size_t... xs>
  constexpr size_t length(index_sequence<xs...>)
  {
    return count_types<decltype(xs)...>();
  }

} // end of namespace TypeUtility::Core

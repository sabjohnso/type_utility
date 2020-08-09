#pragma once

//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/integer.hpp>
#include <type_utility/type.hpp>
#include <type_utility/type1.hpp>
#include <type_utility/type_sequence_utility.hpp>

namespace TypeUtility::Core {

  /**
   * @brief a type representing the abscense of types
   */
  struct No_type
  {
    using type = No_type;
  };

  /**
   * @brief Return the Nth type from the type parameters
   */
  template<size_t n, typename... Ts>
  struct Nth_type;

  /**
   * @brief Return the Nth type from the type parameters
   *
   * @details This is the iterate specialization of
   * the recursive algorithm for selecting a type
   * from a sequence of types by its position in the sequence.
   */
  template<size_t n, typename T, typename... Ts>
  struct Nth_type<n, T, Ts...> : Nth_type<n - 1, Ts...>
  {};

  /**
   * @brief Return the Nth type from the type parameters
   *
   * @details This is the terminal specialization of
   * the recursive algorithm for selecting a type
   * from a sequence of types.
   */
  template<typename T, typename... Ts>
  struct Nth_type<0, T, Ts...> : Type<T>
  {};

  /**
   * @brief Return the Nth type from the type parameters
   */
  template<size_t n, typename... Ts>
  constexpr auto
  nth_type()
  {
    return type<typename Nth_type<n, Ts...>::type>;
  }

  /**
   * @brief Determine the index of the first type in
   * the sequence of types
   */
  template<typename T, typename... Ts>
  struct Find_type
  {

    static_assert(
      Has_type<T, Ts...>::value,
      "Expected the subject type to be present");

    template<size_t, typename...>
    struct Aux;

    template<size_t i, typename U, typename... Us>
    struct Aux<i, U, Us...> : Aux<i + 1, Us...>
    {};

    template<size_t i, typename... Us>
    struct Aux<i, T, Us...> : integral_constant<size_t, i>
    {};

    static constexpr size_t value = Aux<0, Ts...>::value;

  }; // end of struct Find_type

  template<typename Pred, typename... Ts>
  struct Sat;

  template<template<typename...> class Pred>
  struct Sat<Type1<Pred>> : false_type
  {};

  template<template<typename...> class Pred, typename T, typename... Ts>
  struct Sat<Type1<Pred>, T, Ts...>
    : conditional_t<Pred<T>::value, true_type, Sat<Type1<Pred>, Ts...>>
  {};

  template<typename...>
  struct First_sat;

  template<template<typename...> class Pred, typename T, typename... Ts>
  struct First_sat<Type1<Pred>, T, Ts...>
    : conditional_t<Pred<T>::value, Type<T>, First_sat<Type1<Pred>, Ts...>>
  {};

  template<template<typename...> class Pred>
  struct First_sat<Type1<Pred>> : No_type
  {};

  template<typename... Ts>
  struct Type_sequence
  {

    static constexpr size_t
    size()
    {
      return count_types<Ts...>();
    }

    template<size_t index>
    static constexpr auto
    at()
    {
      static_assert(index < size(), "Expected a valid index");
      return nth_type<index, Ts...>();
    }

    template<size_t index>
    static constexpr auto at(integral_constant<size_t, index>)
    {
      return at<index>();
    }

    template<size_t index>
    static constexpr auto at(Nat<index>)
    {
      return at<index>();
    }
    template<size_t index>
    constexpr auto
    operator ()(Nat<index>) const { return at(nat<index>); }

    template<size_t index>
    constexpr auto
    operator [](Nat<index>) const { return at(nat<index>); }

    template<typename T>
    static constexpr bool
    ismember()
    {
      return Has_type<T, Ts...>::value;
    }

    template<typename T>
    static constexpr bool ismember(Type<T>)
    {
      return ismember<T>();
    }

    template<typename T>
    static constexpr size_t
    find()
    {
      static_assert(
        Has_type<T, Ts...>::value, "Expected type subject type to be present");
      return Find_type<T, Ts...>::value;
    }

    template<typename T>
    static constexpr size_t find(Type<T>)
    {
      static_assert(
        Has_type<T, Ts...>::value, "Expected type subject type to be present");
      return Find_type<T, Ts...>::value;
    }

    /** Return true if any of the types satisfy the predicate, otherwise false
     */
    template<template<typename...> class Pred>
    static constexpr bool
    sat()
    {
      return Sat<Type1<Pred>, Ts...>::value;
    }

    /** Return true if any of the types satisfy the predicate, otherwise false
     */
    template<template<typename...> class Pred>
    static constexpr bool sat(Type1<Pred>)
    {
      return Sat<Type1<Pred>, Ts...>::value;
    }

    template<template<typename...> class Pred>
    static constexpr auto
    first_sat()
    {
      static_assert(sat<Pred>(), "Expected at least one type to satisfy Pred");
      return type<typename First_sat<Type1<Pred>, Ts...>::type>;
    }

    template<template<typename...> class Pred>
    static constexpr auto first_sat(Type1<Pred>)
    {
      static_assert(sat<Pred>(), "Expected at least one type to satisfy Pred");
      return type<typename First_sat<Type1<Pred>, Ts...>::type>;
    }



  }; // end of struct  Type_sequence

  template<typename... Ts>
  constexpr Type_sequence<Ts...> types{};

  /**
   * @brief Evaluate the equality of type sequences
   *
   * @details The terminal specialization for the affirmative case
   */
  constexpr bool operator==(Type_sequence<>, Type_sequence<>) { return true; }

  /**
   * @brief Evaluate the equality of type sequences
   *
   * @details The iterate specialization leading to either
   * the affirmative or the negative terminating
   * specializations
   */
  template<typename T, typename... Ts, typename... Us>
  constexpr bool operator==(Type_sequence<T, Ts...>, Type_sequence<T, Us...>)
  {
    return types<Ts...> == types<Us...>;
  }

  /**
   * @brief Evaluate the equality of type sequences
   *
   * @details The specialization for the negative case
   */
  template<typename T, typename... Ts, typename... Us>
  constexpr bool operator==(Type_sequence<T, Ts...>, Type_sequence<Us...>)
  {
    return false;
  }

  /**
   * @brief Evaluate the equality of type sequences
   */
  template<typename... Ts, typename U, typename... Us>
  constexpr bool operator==(Type_sequence<Ts...>, Type_sequence<Us...>)
  {
    return false;
  }

  /**
   * @brief Return true if the input type sequence has the input type
   * as a member.
   */
  template<typename T, typename... Ts>
  constexpr bool ismember(Type_sequence<Ts...>, Type<T>)
  {
    return Type_sequence<Ts...>::ismember(type<T>);
  }

  /**
   * @brief Prepend a type to a type sequence.
   */
  template<typename T, typename... Ts>
  constexpr auto cons(Type<T>, Type_sequence<Ts...>)
  {
    return types<T, Ts...>;
  }

  /**
   * @brief Return the length of a type sequence.
   */
  template<typename... Ts>
  constexpr size_t length(Type_sequence<Ts...>)
  {
    return types<Ts...>.size();
  }

  /**
   * @brief Append the reverse of the fist type sequence and the second type
   * sequence
   */
  template<typename T, typename... Ts, typename... Us>
  constexpr auto rappend(Type_sequence<T, Ts...>, Type_sequence<Us...>)
  {
    return rappend(types<Ts...>, types<T, Us...>);
  }

  /**
   * @brief Append the reverse of the fist type sequence and the second type
   * sequence
   */
  template<typename... Us>
  constexpr auto rappend(Type_sequence<>, Type_sequence<Us...>)
  {
    return types<Us...>;
  }

  /**
   * @brief Reverse the input type sequence.
   */
  template<typename... Ts>
  constexpr auto reverse(Type_sequence<Ts...>)
  {
    return rappend(types<Ts...>, types<>);
  }

  /**
   * @brief Append two type sequences
   */
  template<typename... Ts, typename... Us>
  constexpr auto append(Type_sequence<Ts...>, Type_sequence<Us...>)
  {
    return rappend(reverse(types<Ts...>), types<Us...>);
  }

  /**
   * @brief Return the head of a type sequence
   */
  template<typename T, typename... Ts>
  constexpr auto head(Type_sequence<T, Ts...>)
  {
    return type<T>;
  }

  /**
   * @brief Return the tails of a type sequence.
   */
  template<typename T, typename... Ts>
  constexpr auto tail(Type_sequence<T, Ts...>)
  {
    return types<Ts...>;
  }

  /**
   * @brief Return the tail of a type sequence.
   */
  constexpr auto tail(Type_sequence<>) { return types<>; }

  /**
   * @brief Map a function of plain values  over values
   * in the type sequnece monad
   */
  template<typename F, typename T, typename... Ts>
  constexpr auto type_sequence_transform(F, Type_sequence<T, Ts...>)
  {
    return cons(
      type_transform<decay_t<F>>(type<T>),
      type_sequence_transform<F>(types<Ts...>));
  }

  /**
   * @brief Map a function of plain values  over values
   * in the type sequnece monad
   */
  template<typename F, typename T, typename... Ts>
  constexpr auto type_sequence_transform(Type_sequence<T, Ts...>)
  {
    return cons(
      type_transform<F>(type<T>), type_sequence_transform<F>(types<Ts...>));
  }

  /**
   * @brief Map a function of plain values  over values
   * in the type sequnece monad
   */
  template<typename F>
  constexpr auto type_sequence_transform(F, Type_sequence<>)
  {
    return types<>;
  }

  /**
   * @brief Map a function of plain values  over values
   * in the type sequnece monad
   */
  template<typename F>
  constexpr auto type_sequence_transform(Type_sequence<>)
  {
    return types<>;
  }

  /**
   * @brief Inject a value into the type sequence monad
   */
  template<typename T>
  constexpr auto
  type_sequence_pure(T&&)
  {
    return types<decay_t<T>>;
  }

  /**
   * @brief Apply a function to types
   */
  template<typename F, typename... Fs, typename... Ts>
  constexpr auto type_sequence_apply(
    Type_sequence<F, Fs...>,
    Type_sequence<Ts...>)
  {
    return append(
      type_sequence_transform<F>(types<Ts...>),
      type_sequence_apply(types<Fs...>, types<Ts...>));
  }

  /**
   *
   */
  template<typename... Ts>
  constexpr auto type_sequence_apply(Type_sequence<>, Type_sequence<Ts...>)
  {
    return types<>;
  }

  template<typename Ts, typename... Tss>
  constexpr auto type_sequence_join(Type_sequence<Ts, Tss...>)
  {
    return append(Ts{}, type_sequence_join(types<Tss...>));
  }

  template<typename... Ts, typename F>
  constexpr auto type_sequence_bind(Type_sequence<Ts...>, F)
  {
    return type_sequence_bind<F>(types<Ts...>);
  }

  template<typename F, typename T, typename... Ts>
  constexpr auto type_sequence_bind(Type_sequence<T, Ts...>)
  {
    return append(result_of_t<F(T)>{}, type_sequence_bind<F>(types<Ts...>));
  }

  template<typename F>
  constexpr auto type_sequence_bind(F, Type_sequence<>)
  {
    return types<>;
  }

  template<typename F>
  constexpr auto type_sequence_bind(Type_sequence<>)
  {
    return types<>;
  }

  constexpr auto
  type_list()
  {
    return types<>;
  }

  template<typename T, typename... Ts>
  constexpr auto
  type_list(Type<T>, Type<Ts>...)
  {
    return cons(type<T>, type_list(type<Ts>...));
  }

  template<typename Stream, typename T>
  Stream&
  operator<<(Stream& os, Type_sequence<T>)
  {
    os << type<T>;
    return os;
  }

  template<typename Stream, typename T, typename U, typename... Vs>
  Stream&
  operator<<(Stream& os, Type_sequence<T, U, Vs...>)
  {
    os << type<T> << ',' << types<U, Vs...>;
    return os;
  }

  template<typename Stream, template<typename...> class K, typename... Ts>
  Stream&
  operator<<(Stream& os, Type<K<Ts...>>)
  {
    os << type<Type1<K>> << '<' << types<Ts...> << '>';
    return os;
  }

  template<typename... Ts>
  constexpr auto select(Type_sequence<Ts...>, index_sequence<>)
  {
    return types<>;
  }

  template<typename... Ts, size_t index, size_t... indices>
  constexpr auto select(Type_sequence<Ts...>, index_sequence<index, indices...>)
  {
    return cons(
      nth_type<index, Ts...>(),
      select(types<Ts...>, index_sequence<indices...>()));
  }

} // end of namespace TypeUtility::Core

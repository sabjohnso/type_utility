#pragma once

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>
#include <type_utility/type.hpp>

namespace TypeUtility::Core {

  /** Proxy for templates */
  template<template<typename...> class K>
  class Type1 {
  public:
    template<typename... Ts>
    using type1 = K<Ts...>;

    /** Construct a type proxy for the template specialized over the input types
     */
    template<typename... Ts>
    static constexpr Type<K<Ts...>>
    make_type(Type<Ts>...)
    {
      return type<K<Ts...>>;
    }

    /** Construct a type proxy as a function call */
    template<typename... Ts>
    constexpr Type<K<Ts...>>
    operator()(Type<Ts>...) const&
    {
      return make_type(type<Ts> ...);
    }

  }; // end of class Type1

  template<template<typename...> class K>
  constexpr Type1<K> type1{};

  template<typename Stream, template<typename...> class K>
  Stream&
  operator<<(Stream& os, Type1<K>)
  {
    os << type<Type1<K>>;
    return os;
  }

  template<template<typename...> class K, typename... Ts>
  Type1<K> type1_pure(Type<K<Ts...>>)
  {
    return type1<K>;
  }

} // end of namespace TypeUtility::Core

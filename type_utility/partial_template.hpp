#ifndef PARTIAL_TEMPLATE_HPP_INCLUDED_1309192774600417686
#define PARTIAL_TEMPLATE_HPP_INCLUDED_1309192774600417686 1

//
// ... TypeUtility header files
//
#include <type_utility/type.hpp>
#include <type_utility/type_sequence.hpp>

namespace TypeUtility::Core
{
  template<template<typename ...> class K, typename ... Ts>
  struct Partial_template {
    template<typename ... Us>
    using tmplt = K<Ts..., Us...>;

    template<typename ... Us>
    static constexpr auto
    call(Type<Us> ...){
      return type<K<Ts...,Us...>>;
    }

    template<typename ... Us>
    constexpr auto
    operator ()(Type<Us> ...) const { return call(type<Us> ...); }

    template<size_t Index>
    static constexpr auto
    at(Nat<Index>){
      return types<Ts...>.at(nat<Index>);
    }

    template<size_t Index>
    constexpr auto
    operator [](Nat<Index>) const { return at(nat<Index>); }

    static constexpr auto
    size(){ return types<Ts...>.size(); }
  }; // end of class Partial_template

  template<template<typename ...> class K, typename ... Ts>
  constexpr Partial_template<K,Ts...> partial_template{};


} // end of namespace TypeUtility::Core

#endif // ! defined PARTIAL_TEMPLATE_HPP_INCLUDED_1309192774600417686

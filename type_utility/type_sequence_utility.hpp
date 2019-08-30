#pragma once

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>


namespace TypeUtility::Core
{
  
  template< typename ... Ts >
  struct Count_types;

  template<>
  struct Count_types<> : integral_constant<size_t,0>
  {};

  template<typename T, typename ... Ts >
  struct Count_types<T,Ts...> : integral_constant<size_t,1+Count_types<Ts...>::value >
  {};

  template<typename ... Ts>
  constexpr auto
  count_types(){
    return Count_types<Ts...>::value;
  }

  template<typename ... Ts>
  constexpr auto
  count_args( Ts && ... ){
    return count_types<Ts...>();
  }


  template< typename T, typename ... Ts >
  struct Has_type;

  template< typename T, typename ... Ts >
  struct Has_type<T,T,Ts...> : true_type {};
    

  template< typename T >
  struct Has_type<T> : false_type {};

  template< typename T, typename U, typename ... Ts >
  struct Has_type<T,U,Ts...> : Has_type<T,Ts...> {};







  template< typename ... Ts >
  struct Are_unique;

  template<>
  struct Are_unique<> : false_type {};

  template< typename T, typename ... Ts >
  struct Are_unique<T,Ts...>
    : conditional_t< Has_type<T,Ts...>::value,
		     false_type,
		     Are_unique<Ts...>>{};
      
} // end of namespace TypeUtility::Core


#pragma once

//
// ... Type Utility header files
//
#include <type_utility/type.hpp>
#include <type_utility/type_sequence.hpp>

namespace TypeUtility::Core
{
    
  template< typename ... Ts >
  struct Type_set : Type_sequence<Ts ... >{};

  template< typename T, typename ... Ts >
  constexpr bool
  ismember( Type_set<Ts...>, Type<T> ){
    return Type_set<Ts...>::ismember( type<T> );
  }

  template< typename ... Ts >
  constexpr auto
  validate_type_set(){
    static_assert( Are_unique<Ts ... >::value, "Expected unique members" );
    return Type_set<Ts ... >{};
  }

  template< typename ... Ts >
  constexpr auto type_set = Type_set<Ts...>{};

  template< bool test, typename Pass, typename Fail >
  constexpr auto
  cond( Pass p, Fail f){
    return  conditional_t<test, Pass, Fail >{};
  }

  template< typename ... Ts, typename T >
  constexpr auto
  type_set_add( Type_set<Ts...>, Type<T> ){
    return cond<type_set<Ts...>.ismember( type<T> )>(
      type_set<Ts...>, Type_set<T,Ts...>{});
  }

  template< typename ... Ts >
  constexpr auto
  type_set_intersection( Type_set<Ts ...>, Type_set<> ){
    return type_set<Ts...>;
  }
    
  template< typename ... Ts, typename U, typename  ... Us>
  constexpr auto
  type_set_intersection( Type_set<Ts ...>, Type_set< U, Us ...> ){
    return type_set_intersection(
      type_set_add( type_set<Ts...>, type<U> ),
      Type_set<Us...>{} );
  }

} // end of namespace TypeUtility::Core

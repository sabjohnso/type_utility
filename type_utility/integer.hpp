#ifndef INTEGER_HPP_INCLUDED_2236071534764956228
#define INTEGER_HPP_INCLUDED_2236071534764956228 1

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>
#include <type_utility/type.hpp>

namespace TypeUtility
{
  namespace Core
  {

    template< typename T, T x >
    using Integer = Type<integral_constant<T,x>>;

    template< typename T, T x >
    constexpr auto integer = type<integral_constant<T,x>>;

    template< typename Stream, typename T, T x >
    Stream&
    operator <<( Stream& os, Integer<T,x> ){
      os << '[' << x << ':' << type<T> << ']';
      return os;
    }

    template< typename T, T x, T y >
    constexpr auto
    operator +( Integer<T,x>, Integer<T,y> ){
      return integer<T,x+y>;
    }

    
    template< typename T, T x, T y >
    constexpr auto
    operator -( Integer<T,x>, Integer<T,y> ){
      return integer<T,x-y>;
    }

    
    template< typename T, T x, T y >
    constexpr auto
    operator *( Integer<T,x>, Integer<T,y> ){
      return integer<T,x*y>;
    }

    
    template< typename T, T x, T y >
    constexpr auto
    operator /( Integer<T,x>, Integer<T,y> ){
      return integer<T,x/y>;
    }
    
    template< typename T, T x, T y >
    constexpr auto
    operator %( Integer<T,x>, Integer<T,y> ){
      return integer<T,x%y>;
    }

    template< typename T, T x >
    constexpr auto
    succ( Integer<T,x> ){ return integer<T,x+1>; }

    template< typename T, T x >
    constexpr auto
    pred( Integer<T,x> ){ return integer<T,x-1>; }
      


    // template< typename T, T ... xs >
    // struct Are_unique_integers : Are_unique<Type<integral_constant<T,xs> ... >>
    // {};

    // template< typename T >
    // struct Are_unique_integers<T> : true_type {};

    // template< typename T, T ... xs >
    // struct integer_set : integer_sequence<T, T ... xs >
    // {
    // };
    
  } // end of namespace Cre
} // end of namespace TypeUtility

#endif // !defined INTEGER_HPP_INCLUDED_2236071534764956228

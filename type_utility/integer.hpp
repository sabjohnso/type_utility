#ifndef INTEGER_HPP_INCLUDED_2236071534764956228
#define INTEGER_HPP_INCLUDED_2236071534764956228 1

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>


namespace TypeUtility
{
  namespace Cre
  {

    template< typename T, T x >
    using Integer = Type<integral_constant<T,x>>;


    template< typename T, T x >
    constexpr auto integer = type<integral_contant<T,x>>;


    template< typename T, xs ... >
    struct Are_unique_integers : Are_unique_types<Type<integral_constant<T,xs> ... >>
    {};

    template< typename T >
    struct Are_unique_integers<T> : true_type {};

    template< typename T, T x, 
    

    template< typename T, T ... xs >
    struct integer_set : integer_sequence<T, T ... xs >
    {
    };
    
  } // end of namespace Cre
} // end of namespace TypeUtility

#endif // !defined INTEGER_HPP_INCLUDED_2236071534764956228

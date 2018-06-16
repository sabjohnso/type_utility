#ifndef DROP_HPP_INCLUDED_1900745432998936524
#define DROP_HPP_INCLUDED_1900745432998936524 1

//
// ... Type Utility header files
//
#include <type_utility/type_sequence.hpp>
#include <type_utility/integer.hpp>



namespace TypeUtility
{
  namespace Core
  {

    constexpr auto
    drop( Type_sequence<>, Nat<0>){
      return types<>;
    }

    template< typename T, typename ... Ts >
    constexpr auto
    drop( Type_sequence<T,Ts...>, Nat<0> ){
      return types<T,Ts...>;
    }
    
    
    template< typename T, typename ... Ts, size_t N >
    constexpr auto
    drop( Type_sequence<T,Ts...>, Nat<N> ){
      return drop( types<Ts...>, nat<N-1> );
    }





    

    template< typename I, I x, I ... xs >
    constexpr auto
    drop( Integer_sequence<I, x, xs ... >, Nat<0> ){
      return integers<I, x, xs...>;
    }

    template< typename I >
    constexpr auto
    drop( Integer_sequence<I>, Nat<0> ){
      return integers<I>;
    }

    template< typename I, I x, I ... xs, size_t N >
    constexpr auto
    drop( Integer_sequence<I, x, xs ... >, Nat<N> ){
      return drop( integers<I,xs...>, nat<N-1> );
    }
	

    
    
  } // end of namespace Core
} // end of namespace TypeUtility
#endif // !defined DROP_HPP_INCLUDED_1900745432998936524

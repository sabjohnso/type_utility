#ifndef TAKE_HPP_INCLUDED_1796238555755909691
#define TAKE_HPP_INCLUDED_1796238555755909691 1

//
// ... Type Utility header files
//
#include <type_utility/type_sequence.hpp>
#include <type_utility/integer.hpp>


namespace TypeUtility
{
  namespace Core
  {

    
    class  Take_types {
    public:

      template< typename ... Ts, size_t N >
      static constexpr auto
      call( Type_sequence<Ts...>, Nat<N> ){
	static_assert( count_types<Ts...>() >= N, "Expected a sufficient number of types");
	return aux(types<Ts...>, types<>, nat<N>  );
      }
    private:
      
      template< typename T, typename ... Ts, typename ... Us >
      static constexpr auto
      aux( Type_sequence<T,Ts...>, Type_sequence<Us...>, Nat<0> ){
	return types<Us...>;
      }
      
      template< typename ... Us >
      static constexpr auto
      aux( Type_sequence<>, Type_sequence<Us...>, Nat<0> ){
	return types<Us...>;
      }

      template< typename T, typename ... Ts, typename ... Us,  size_t N>
      static constexpr auto
      aux( Type_sequence<T,Ts...>, Type_sequence<Us...>, Nat<N> ){
	return aux( types<Ts...>, types<Us...,T>, nat<N-1> );
      }

      
    }; // end of class Take_types;

    template< typename ... Ts, size_t N >
    constexpr auto
    take( Type_sequence<Ts...>, Nat<N> ){
      return Take_types::call( types<Ts...>, nat<N> );
    }







    class Take_integers {
    public:
      template< typename I, I ... xs, size_t N >
      static constexpr auto
      call( Integer_sequence<I,xs...>, Nat<N> ){
	return aux( integers<I,xs...>, integers<I>, nat<N> );
      }
    private:

      
      template< typename I, I x, I ... xs, I ... ys >
      static constexpr auto
      aux( Integer_sequence<I,x,xs...>, Integer_sequence<I,ys...>, Nat<0> ){
	return integers<I,ys...>;
      }

      
      template< typename I, I ... ys >
      static constexpr auto
      aux( Integer_sequence<I>, Integer_sequence<I,ys...>, Nat<0> ){
	return integers<I,ys...>;
      }

      template< typename I, I x, I ... xs, I ... ys, size_t N >
      static constexpr auto
      aux( Integer_sequence<I,x,xs...>, Integer_sequence<I,ys...>, Nat<N> ){
	return aux( integers<I,xs...>, integers<I,ys...,x>, nat<N-1> );
      }

    }; // end of class Take_integers


    
    template< typename I, I ... xs, size_t N >
    constexpr auto
    take( Integer_sequence<I,xs...>, Nat<N> ){
      return Take_integers::call( integers<I,xs...>, nat<N> );
    }


    template< size_t ... xs >
    constexpr auto
    index_to_integer_sequence( index_sequence<xs ...> ){
      return integers<size_t,xs...>;
    }

    template< size_t ... xs >
    constexpr auto
    integer_to_index_sequence( Integer_sequence<size_t,xs...> ){
      return index_sequence<xs...>();
    }

    template< size_t ... xs, size_t N >
    constexpr auto
    take( index_sequence<xs...>, Nat<N> ){
      return integer_to_index_sequence( take( integers<size_t,xs...>, nat<N>));
    }
    








    
    
  } // end of namespace Core
} // end of namespace TypeUtility


#endif // !defined TAKE_HPP_INCLUDED_1796238555755909691

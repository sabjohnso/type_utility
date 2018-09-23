#ifndef INTEGER_SET_HPP_INCLUDED_2287266480445231110
#define INTEGER_SET_HPP_INCLUDED_2287266480445231110 1

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>
#include <type_utility/integer.hpp>
#include <type_utility/type_set.hpp>


namespace TypeUtility::Core
{

  
  template< typename T, T ... xs >
  struct Integer_set {
    static constexpr T values[] = {xs ...};
  };

  template< typename T, T ... xs >
  constexpr Integer_set<T,xs ...> integer_set{};


  template< typename T, T ... xs, T x >
  constexpr bool
  ismember( Integer_set<T,xs...>, Integer<T,x> ){
    return ismember( integers<T,xs...>, integer<T,x> );
  }
    
    
  template< typename T, T ... xs >
  constexpr auto
  integer_set_validate( Integer_set<T, xs ... > ){
    static_assert( Are_unique_integers<T,xs...>::value, "Expected unique integers" );
    return integer_set<T,xs...>;
  }

  template< typename T, T ... xs, T x >
  constexpr auto
  integer_set_add( Integer_set<T,xs...>, Integer<T,x> ){
    return cond<ismember(integers<T,xs...>, integer<T,x> )>(
      integer_set<T,xs...>,
      integer_set<T,x,xs...> );
  }

  template< typename T, T ... xs, T y, T ... ys >
  constexpr auto
  integer_set_union( Integer_set<T, xs ...>, Integer_set<T, y, ys ...> ){
    return integer_set_union(
      integer_set_add( integer_set<T,xs...>, integer<T,y>),
      integer_set<T,ys...> );
  }

    
  template< typename T, T ... xs >
  constexpr auto
  integer_set_union( Integer_set<T, xs ...>, Integer_set<T> ){
    return integer_set<T,xs...>;
  }

  template< typename T, T ... xs, T ... ys >
  constexpr auto
  integer_set_intersection( Integer_set<T, xs ...>, Integer_set<T, ys ... > ){
    return  integer_set_intersection_aux(
      integer_set<T,xs ...>, integer_set<T,ys...>, integer_set<T> );
  }

  template< typename T, T x, T ... xs, T ... ys, T ... zs >
  constexpr auto
  integer_set_intersection_aux(
    Integer_set<T, x, xs ...>,
    Integer_set<T, ys ... >,
    Integer_set<T, zs ... > ){
    return integer_set_intersection_aux(
      integer_set<T,xs...>,
      integer_set<T,ys...>,
      cond<ismember( integers<T,ys...>, integer<T,x> )>(
	integer_set<T,x,zs...>,
	integer_set<T,zs...>));
  }



  template< typename T, T ... ys, T ... zs >
  constexpr auto
  integer_set_intersection_aux( Integer_set<T>, Integer_set<T, ys ... >, Integer_set<T, zs ... >){
    return integer_set<T,zs ...>;
  }

  template< typename T, T ... xs, T y, T ... ys >
  constexpr bool
  issubset( Integer_set<T,xs...> xset, Integer_set<T,y,ys ...> ){
    return ismember(integer_set<T,xs...>, integer<T,y>)
      ? issubset( integer_set<T,xs...>, integer_set<T,ys...> )
      : false;
  }

  template< typename T, T ... xs >
  constexpr bool
  issubset( Integer_set<T,xs...> xset, Integer_set<T> ){
    return true;
  }
      
  template< typename T, T ... xs, T ... ys >
  constexpr bool
  operator ==( Integer_set<T,xs...> xset, Integer_set<T,ys...> yset ){
    return issubset( xset, yset ) && issubset( yset, xset );
  }

  template< typename T, T ... xs, T ... ys >
  constexpr bool
  operator !=( Integer_set<T,xs...> xset, Integer_set<T,ys...> yset ){
    return !( xset == yset );
  }

  template< typename T, T ... ys, T ... zs >
  constexpr auto
  integer_set_difference_aux( Integer_set<T>, Integer_set<T,ys ...> yset, Integer_set<T,zs ...> accum ){
    return accum;
  }

  template< typename T, T x, T ... xs, T ... ys, T ... zs >
  constexpr auto
  integer_set_difference_aux( Integer_set<T,x,xs...>, Integer_set<T,ys ...> yset, Integer_set<T,zs ...> accum ){
    return cond<ismember(yset,integer<T,x>)>(
      integer_set_difference_aux( integer_set<T,xs...>, yset, accum ),
      integer_set_difference_aux( integer_set<T,xs...>, yset, integer_set_add( accum, integer<T,x> )));
  }

  template< typename T, T ... xs, T ... ys >
  constexpr auto
  integer_set_difference( Integer_set<T,xs...> xset, Integer_set<T,ys...> yset ){
    return integer_set_difference_aux( xset, yset, integer_set<T> );
  }

  template< typename T, T ... xs, T y >
  constexpr auto
  integer_set_remove( Integer_set<T,xs...> xset, Integer<T,y> ){
    return integer_set_difference( xset, integer_set<T,y> );
  }



  template< typename T, T ... xs, T ... ys >
  constexpr auto
  integer_set_symmetric_difference( Integer_set<T,xs...> xset, Integer_set<T,ys...> yset ){
    return integer_set_intersection(
      integer_set_difference( xset, yset ),
      integer_set_difference( yset, xset ));
  }
  
  
} // end of namespace TypeUtility::Core
#endif // !defined INTEGER_SET_HPP_INCLUDED_2287266480445231110

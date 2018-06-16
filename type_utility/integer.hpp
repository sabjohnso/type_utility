#ifndef INTEGER_HPP_INCLUDED_2236071534764956228
#define INTEGER_HPP_INCLUDED_2236071534764956228 1

//
// ... Type Utility header files
//
#include <type_utility/import.hpp>
#include <type_utility/type.hpp>
#include <type_utility/type_sequence.hpp>
#include <type_utility/type_set.hpp>

namespace TypeUtility
{
  namespace Core
  {
    
    
    template< size_t N>
    struct Nat{

      static constexpr size_t value = N;

      template< size_t M >
      friend constexpr bool
      operator <( const Nat&, const Nat<M>& ){ return N < M; }

      template< size_t M >
      friend constexpr bool
      operator <=( const Nat&, const Nat<M>& ){ return N <= M; }

      template< size_t M> 
      friend constexpr bool
      operator >( const Nat&, const Nat<M>& ){ return N > M; }

      template< size_t M> 
      friend constexpr bool
      operator >=( const Nat&, const Nat<M>& ){ return N >= M; }

      template< size_t M >
      friend constexpr bool
      operator ==( const Nat&, const Nat<M>& ){ return N == M; }

      template< size_t M >
      friend constexpr bool
      operator !=( const Nat&, const Nat<M>& ){ return N != M; }


      template< size_t M >
      friend constexpr auto
      operator +( const Nat&, const Nat<M>& ){ return Nat<N+M>(); }

      
      template< size_t M >
      friend constexpr auto
      operator -( const Nat&, const Nat<M>& ){
	static_assert( N > M, "Underflow" );
	return Nat<N-M>();
      }

      template< size_t M >
      friend constexpr auto
      operator *(const Nat&, const Nat<M>& ){ return Nat<N-M>(); }

      template< size_t M >
      friend constexpr auto
      operator /( const Nat&, const Nat<M>& ){ return Nat<N/M>(); }

      template< size_t M >
      friend constexpr auto
      operator %( const Nat&, const Nat<M>& ){ return Nat<N%M>(); }
      

      

    }; // end of class
    
      
    template<size_t N>
    constexpr auto nat = Nat<N>{};



    template< typename T, T ... xs >
    struct Integer_sequence
    {
      using value_type = T;
      static constexpr size_t extent = count_types<decltype(xs) ... >();
      static constexpr T values [] = {xs ... };

      constexpr
      Integer_sequence(){}
      
      constexpr
      Integer_sequence( integer_sequence<T,xs...> ){}

      friend constexpr bool
      operator ==( const Integer_sequence&, const Integer_sequence& ){ return true; }

      template< T ... ys >
      friend constexpr bool
      operator ==( const Integer_sequence&, const Integer_sequence<T,ys...>& ){ return false; }

      template< typename U >
      friend constexpr bool
      operator != ( const Integer_sequence&, const U& ){ return !( Integer_sequence() == U() ); }

      

    }; // end of struct Integer_sequence


    
    
    template< typename T, T x >
    using Integer = integral_constant<T,x>;

    template< typename T, T x >
    constexpr auto integer = integral_constant<T,x>{};

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

    
    template< typename T, T ... xs >
    constexpr auto integers = Integer_sequence<T,xs ...>{};


    template< typename T, T x, T ... xs, T ... ys >
    constexpr bool
    operator ==( const  integer_sequence<T,x,xs...>&, const integer_sequence<T,x,ys ... >& ){
      return integers<T,xs...> == integers<T,ys...>;
    }

    template< typename T, T x, T ... xs, T ... ys >
    constexpr bool
    operator ==( const integer_sequence<T,x,xs...>&, const integer_sequence<T,ys ... >& ){
      return false;
    }

    template< typename T, T ... xs, T y, T ... ys >
    constexpr bool
    operator ==( const integer_sequence<T,xs...>&, const integer_sequence<T,y,ys ... >& ){
      return false;
    }


    template< typename T >
    constexpr bool
    operator ==( const integer_sequence<T>&, const integer_sequence<T>& ){
      return true;
    }

    template< typename T, T ... xs, T ... ys >
    constexpr bool
    operator !=( const integer_sequence<T, xs ...>&, const integer_sequence<T,ys...>& ){
      return !( integer_sequence<T, xs ...>() ==  integer_sequence<T,ys...>());
    }
    

    
    template< typename T, T y >
    constexpr bool
    ismember( Integer_sequence<T>, integral_constant<T,y> ){
      return false;
    }
    
    

    template< typename T, T x, T ... xs >
    constexpr bool
    ismember( Integer_sequence<T,x, xs...>, integral_constant<T,x> ){
      return true;
    }

    template< typename T, T x, T ... xs, T y >
    constexpr bool
    ismember( Integer_sequence<T,x, xs...>, integral_constant<T,y> ){
      return ismember( integers<T,xs...>, integer<T,y> );
    }

      
      


    template< typename T, T ... xs >
    struct Are_unique_integers : Are_unique<Type<integral_constant<T,xs> ... >>
    {};

    template< typename T >
    struct Are_unique_integers<T> : true_type {};


    template< typename F, typename T, T ... xs >
    constexpr auto
    integer_sequence_transform( F f, Integer_sequence<T,xs...> ){
      return Integer_sequence<decay_t<result_of_t<F(T)>>, f(xs) ... >{};
    }




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
    



    template< size_t N, size_t ... Indices >
    struct Generate_indices;

    template< size_t N, size_t ... Indices >
    struct Generate_indices : Generate_indices<N-1,N-1,Indices ...> {};
    
    template< size_t ... Indices >
    struct Generate_indices<0,Indices...> : Type<index_sequence<Indices...>>{};

    template< size_t N >
    constexpr auto
    generate_indices(){
      return typename Generate_indices<N>::type{};
    }
    

    template< typename ... Ts >
    constexpr auto
    generate_indices(){
      return generate_indices<count_types<Ts...>()>();
    }

    template< size_t index, size_t ... indices >
    constexpr auto
    rotate( index_sequence< index, indices...> ){
      return index_sequence<indices..., index>();
    }

    
    
    
  } // end of namespace Cre
} // end of namespace TypeUtility

#endif // !defined INTEGER_HPP_INCLUDED_2236071534764956228

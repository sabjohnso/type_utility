#ifndef TYPE_SEQUENCE_HPP_INCLUDED_921095977076239931
#define TYPE_SEQUENCE_HPP_INCLUDED_921095977076239931 1

//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/type.hpp>
#include <type_utility/type1.hpp>


namespace TypeUtility
{
  namespace Core
  {

    struct No_type{};
    
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


    template< size_t n, typename ... Ts >
    struct Nth_type;

    template< size_t n, typename T, typename ... Ts >
    struct Nth_type<n,T,Ts...>  : Nth_type<n-1,Ts...>{};

    template< typename T, typename ... Ts >
    struct Nth_type<0,T,Ts...>  : Type<T>
    {};

    template< size_t n, typename ... Ts >
    constexpr auto
    nth_type(){ return type<typename Nth_type<n,Ts...>::type>; }


    template< typename T, typename ... Ts >
    struct Find_type
    {
      
      static_assert( Has_type<T,Ts...>::value, "Expected the subect type to be present" );

      template< size_t, typename ... >
      struct Aux;

      template< size_t i, typename U, typename ... Us >
      struct Aux<i, U, Us ...> : Aux<i+1,Us...>
      {};

      template< size_t i, typename ... Us >
      struct Aux<i, T, Us ...> : integral_constant<size_t,i>{};

      
      static constexpr size_t value = Aux<0,Ts...>::value;
	
    }; // end of struct Find_type

    template<typename ... >
    struct First_pred;

    template< template< typename ... > class Pred, typename T, typename ... Ts >
    struct First_pred<Type1<Pred>,T,Ts...>
      : conditional_t<Pred<T>::value, Type<T>, First_pred<Type1<Pred>, Ts... >>{};
    
    template< template< typename ... > class Pred >
    struct First_pred<Type1<Pred>>
      : Type<No_type>{};
    
    template< typename ... Ts >
    struct Type_sequence
    {

      static constexpr size_t
      size(){ return count_types<Ts...>(); }

      template< size_t index >
      static constexpr auto
      at(){
	static_assert( index < size(), "Expected a valid index" );
	return nth_type<index, Ts...>();
      }

      template< typename T >
      static constexpr bool
      ismember(){ return Has_type<T,Ts...>::value; }

      template< typename T >
      static constexpr size_t
      find(){
	static_assert( Has_type<T,Ts...>::value, "Expected type subject type to be present" );
	return Find_type<T,Ts...>::value;
      }

      template< typename Pred >
      static constexpr auto
      first_pred(){
	
      }
      

    }; // end of struct  Type_sequence

    template< typename ... Ts >
    constexpr Type_sequence<Ts...> types{};
    
    
  } // end of namespace Core
} // end of namespace TypeUtility

#endif // !defined TYPE_SEQUENCE_HPP_INCLUDED_921095977076239931

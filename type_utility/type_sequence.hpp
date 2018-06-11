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

    

    struct No_type{ using type = No_type; };
    
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


    
    template< typename Pred, typename ... Ts >
    struct Sat;

    template< template< typename ... > class Pred >
    struct Sat<Type1<Pred>> : false_type{};

    template< template< typename ... > class Pred, typename T, typename ... Ts >
    struct Sat<Type1<Pred>, T, Ts ... >
      : conditional_t< Pred<T>::value, true_type, Sat<Type1<Pred>,Ts...>>{};

    template< typename ... >
    struct First_sat;

    template< template< typename ... > class Pred, typename T, typename ... Ts >
    struct First_sat<Type1<Pred>, T, Ts ...>
      : conditional_t<Pred<T>::value,Type<T>,First_sat<Type1<Pred>,Ts...>>{};

    template< template< typename ... > class Pred >
    struct First_sat<Type1<Pred>> : No_type {};
        
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

      template< size_t index >
      static constexpr auto
      at( integral_constant<size_t, index> ){
	return at<index>();
      }

      template< typename T >
      static constexpr bool
      ismember(){ return Has_type<T,Ts...>::value; }

      template< typename T >
      static constexpr bool
      ismember( Type<T> ){ return ismember<T>();  }

      template< typename T >
      static constexpr size_t
      find(){
	static_assert( Has_type<T,Ts...>::value, "Expected type subject type to be present" );
	return Find_type<T,Ts...>::value;
      }

      template< typename T >
      static constexpr size_t
      find( Type<T> ){
	static_assert( Has_type<T,Ts...>::value, "Expected type subject type to be present" );
	return Find_type<T,Ts...>::value;
      }

      /** Return true if any of the types satisfy the predicate, otherwise false
       */
      template< template< typename ... > class Pred >
      static constexpr bool
      sat(){
	return Sat<Type1<Pred>,Ts...>::value;
      }

      /** Return true if any of the types satisfy the predicate, otherwise false
       */
      template< template< typename ... > class Pred >
      static constexpr bool
      sat( Type1<Pred> ){
	return Sat<Type1<Pred>,Ts...>::value;
      }

      
      template< template< typename  ... > class Pred >
      static constexpr auto
      first_sat(){
	static_assert( sat<Pred>(), "Expected at least one type to satisfy Pred" );
	return type<typename First_sat<Type1<Pred>,Ts ...>::type>;
      }
           
      template< template< typename  ... > class Pred >
      static constexpr auto
      first_sat( Type1<Pred> ){ 
	static_assert( sat<Pred>(), "Expected at least one type to satisfy Pred" );
	return type<typename First_sat<Type1<Pred>,Ts ...>::type>;
      }
      
    }; // end of struct  Type_sequence

    
    template< typename ... Ts >
    constexpr Type_sequence<Ts...> types{};


    constexpr bool
    operator ==( Type_sequence<>, Type_sequence<> ){ return true; }

    template< typename T, typename ... Ts, typename ... Us >
    constexpr bool
    operator ==( Type_sequence<T,Ts...>, Type_sequence<T,Us...> ){
      return types<Ts...> == types<Us...>;
    }
    
    template< typename T, typename ... Ts, typename U, typename ... Us >
    constexpr bool
    operator ==( Type_sequence<T,Ts...>, Type_sequence<U,Us...> ){
      return false;
    }

    template< typename T, typename ... Ts >
    constexpr bool
    ismember( Type_sequence< Ts ...>, Type<T> ){
      return Type_sequence< Ts ...>::ismember( type<T> );
    }
    
      
    

    template< typename T, typename ... Ts >
    constexpr auto
    cons( Type<T>, Type_sequence<Ts ...> ){
      return types<T,Ts...>;
    }

    template< typename ... Ts >
    constexpr size_t
    length( Type_sequence<Ts...> ){
      return types<Ts...>.size();
    }

    template< typename T, typename ... Ts, typename ... Us >
    constexpr auto
    rappend( Type_sequence<T, Ts...>, Type_sequence<Us ...> ){
      return rappend( types<Ts...>, types<T,Us...> );
    }
    
    template< typename ... Us >
    constexpr auto
    rappend( Type_sequence<>, Type_sequence<Us ...> ){ return types<Us...>; }
    
    template< typename ... Ts >
    constexpr auto
    reverse( Type_sequence<Ts ...> ){ return rappend( types<Ts...>, types<> ); }

    template< typename ... Ts, typename ... Us >
    constexpr auto
    append( Type_sequence<Ts...>, Type_sequence<Us...> ){
      return rappend( reverse( types<Ts...> ), types<Us...> );
    }

    template< typename T, typename ... Ts >
    constexpr auto
    head( Type_sequence<T,Ts...> ){ return type<T>; }

    template< typename T, typename ... Ts >
    constexpr auto
    tail( Type_sequence<T,Ts...> ){ return types<Ts...>; }

    constexpr auto
    tail( Type_sequence<> ){ return types<>; }

    template< typename F, typename T, typename ... Ts >
    constexpr auto
    type_sequence_transform( F,  Type_sequence< T, Ts ... > ){
      return cons( type_transform<decay_t<F>>( type<T> ), type_sequence_transform<F>( types<Ts...> )); }

    template< typename F, typename T, typename ... Ts >
    constexpr auto
    type_sequence_transform( Type_sequence< T, Ts ... > ){
      return cons( type_transform<F>( type<T> ), type_sequence_transform<F>( types<Ts...> )); }

    
    
    template< typename F >
    constexpr auto
    type_sequence_transform( F, Type_sequence<> ){ return types<>; }

    template< typename F >
    constexpr auto
    type_sequence_transform( Type_sequence<> ){ return types<>; }

    template< typename T >
    constexpr auto
    type_sequence_pure( T&& ){ return types<decay_t<T>>; }

    template< typename F, typename ... Fs,  typename ... Ts >
    constexpr auto
    type_sequence_apply( Type_sequence<F, Fs ...>, Type_sequence<Ts ...> ){
      return append( type_sequence_transform<F>( types<Ts ... > ),
		     type_sequence_apply( types<Fs...>, types<Ts...> ));
    }




	
    template< typename ... Ts >
    constexpr auto
    type_sequence_apply( Type_sequence<>, Type_sequence<Ts ...> ){
      return types<>;
    }

    template< typename Ts, typename ... Tss >
    constexpr auto
    type_sequence_join( Type_sequence<Ts, Tss ... > ){
      return append( Ts{}, type_sequence_join( types<Tss...> ));
    }

    template< typename ... Ts, typename F >
    constexpr auto
    type_sequence_bind( Type_sequence<Ts...>, F ){
      return type_sequence_bind<F>( types<Ts...> );
    }

    template< typename F, typename T, typename ... Ts >
    constexpr auto
    type_sequence_bind( Type_sequence<T, Ts...> ){
      return append(
	result_of_t<F(T)>{},
	type_sequence_bind<F>( types<Ts...> ));
    }

    template< typename F >
    constexpr auto
    type_sequence_bind( F, Type_sequence<> ){
      return types<>;
    }

    template< typename F >
    constexpr auto
    type_sequence_bind( Type_sequence<> ){
      return types<>;
    }





    
     
    constexpr auto
    type_list(){ return types<>; }

    template< typename T, typename ... Ts >
    constexpr auto
    type_list( Type<T>, Type<Ts> ... ){
      return cons( type<T>, type_list( type<Ts> ... ));
    }

    template< typename Stream, typename T>
    Stream &
    operator <<( Stream& os, Type_sequence<T> ){
      os << type<T>;
      return os;
    }

    template< typename Stream, typename T, typename U, typename ... Vs >
    Stream &
    operator <<( Stream& os, Type_sequence<T,U,Vs...> ){
      os << type<T> << ',' << types<U,Vs...>;
      return os;
    }
    
    template< typename Stream, template< typename ... > class K, typename ... Ts >
    Stream&
    operator <<( Stream& os, Type<K<Ts...>> ){
      os << type<Type1<K>> << '<' << types<Ts...> << '>';
      return os;
    }



    
  } // end of namespace Core
} // end of namespace TypeUtility

#endif // !defined TYPE_SEQUENCE_HPP_INCLUDED_921095977076239931

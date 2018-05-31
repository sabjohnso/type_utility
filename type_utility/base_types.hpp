#ifndef BASE_TYPES_HPP_INCLUDED_2173693085049882071
#define BASE_TYPES_HPP_INCLUDED_2173693085049882071 1

//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/import.hpp>
#include <type_utility/type_sequence.hpp>


namespace TypeUtility
{
  namespace Core
  {


    template< size_t size, typename T >
    struct has_sizeof : conditional_t<sizeof(T) == size, true_type, false_type>{};

    template< size_t size >
    struct make_size_predicate
    {
      template< typename T >
      using pred = has_sizeof<size,T>;
    };

    template< typename T >
    using is_8bit = make_size_predicate<1>::template pred<T>;
    

    template< typename T >
    using is_16bit = make_size_predicate<2>::template pred<T>;
    
    template< typename T >
    using is_32bit = make_size_predicate<4>::template pred<T>;

    template< typename T >
    using is_64bit = make_size_predicate<8>::template pred<T>;

    template< typename T >
    using is_128bit = make_size_predicate<16>::template pred<T>;

    template< typename T >
    using is_256bit = make_size_predicate<32>::template pred<T>;

    template< typename T >
    using is_512bit = make_size_predicate<64>::template pred<T>;
    
    

    using Signed_integer_types =
      Type_sequence<short,int,long,long long>;

    using Int16 = typename decltype(Signed_integer_types::first_sat<is_16bit>() )::type;
    using Int32 = typename decltype(Signed_integer_types::first_sat<is_32bit>() )::type;
    using Int64 = typename decltype(Signed_integer_types::first_sat<is_64bit>() )::type;

    template< size_t size >
    using Int = typename decltype(
      Signed_integer_types::first_sat<
      make_size_predicate<size/8>::template pred>())::type;
    


    
    using Unsigned_integer_types =
      Type_sequence<unsigned short,unsigned, unsigned long, unsigned long long>;

    using UInt16 = typename decltype(Unsigned_integer_types::first_sat<is_16bit>() )::type;
    using UInt32 = typename decltype(Unsigned_integer_types::first_sat<is_32bit>() )::type;
    using UInt64 = typename decltype(Unsigned_integer_types::first_sat<is_64bit>() )::type;
    
    template< size_t size >
    using UInt = typename decltype(
      Unsigned_integer_types::first_sat<
      make_size_predicate<size/8>::template pred>())::type;

    

    using Floating_point_types =
      Type_sequence<float, double, long double>;
    
    using Float32 = typename decltype(Floating_point_types::first_sat<is_32bit>() )::type;
    using Float64 = typename decltype(Floating_point_types::first_sat<is_64bit>() )::type;
    using Float128 = typename decltype(Floating_point_types::first_sat<is_128bit>() )::type;

    template< size_t size >
    using Float = typename decltype(
      Floating_point_types::first_sat<
      make_size_predicate<size/8>::template pred>())::type;

    


    
    
  } // end of namespace Core
} // end of namespace TYPE_UTILITY_NAMESPACE


#endif // !defined BASE_TYPES_HPP_INCLUDED_2173693085049882071

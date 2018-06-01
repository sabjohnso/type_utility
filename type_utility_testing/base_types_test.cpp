//
// ... Type Utility header files
//
#include <type_utility/base_types.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>


using namespace TypeUtility::Core;

/** Test the base types */
struct Base_types_test
{
  Base_types_test() : accum( 0 ) {
    
    TYPE_UTILITY_STATIC_TEST( type<Int<16>>.size() == 2 );
    TYPE_UTILITY_STATIC_TEST( type<Int<32>>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<Int<64>>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<Int<16>>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int<32>>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int<64>>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int<16>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int<32>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int<64>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int<16>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Int<32>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Int<64>>.isarithmetic());


    TYPE_UTILITY_STATIC_TEST( type<UInt<16>>.size() == 2 );
    TYPE_UTILITY_STATIC_TEST( type<UInt<32>>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<UInt<64>>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<UInt<16>>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt<32>>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt<64>>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt<16>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt<32>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt<64>>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt<16>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<UInt<32>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<UInt<64>>.isarithmetic());
    
       
    TYPE_UTILITY_STATIC_TEST( type<Float<32>>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<Float<64>>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<Float<128>>.size() == 16 );
    TYPE_UTILITY_STATIC_TEST( type<Float<32>>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float<64>>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float<128>>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float<32>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Float<64>>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Float<128>>.isarithmetic());




  }
  operator int() const { return accum; }
  int accum;
   }; // end of struct Base_types_test


int
main( int, char** )
{
  int accum = 0;
  accum += Base_types_test();
  return accum;
}

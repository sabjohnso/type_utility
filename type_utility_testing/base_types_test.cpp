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
    
    TYPE_UTILITY_STATIC_TEST( type<Int16>.size() == 2 );
    TYPE_UTILITY_STATIC_TEST( type<Int32>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<Int64>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<Int16>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int32>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int64>.issigned());
    TYPE_UTILITY_STATIC_TEST( type<Int16>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int32>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int64>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<Int16>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Int32>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Int64>.isarithmetic());


    TYPE_UTILITY_STATIC_TEST( type<UInt16>.size() == 2 );
    TYPE_UTILITY_STATIC_TEST( type<UInt32>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<UInt64>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<UInt16>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt32>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt64>.isunsigned());
    TYPE_UTILITY_STATIC_TEST( type<UInt16>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt32>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt64>.isintegral());
    TYPE_UTILITY_STATIC_TEST( type<UInt16>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<UInt32>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<UInt64>.isarithmetic());
    
       
    TYPE_UTILITY_STATIC_TEST( type<Float32>.size() == 4 );
    TYPE_UTILITY_STATIC_TEST( type<Float64>.size() == 8 );
    TYPE_UTILITY_STATIC_TEST( type<Float128>.size() == 16 );
    TYPE_UTILITY_STATIC_TEST( type<Float32>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float64>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float128>.isfloating_point());
    TYPE_UTILITY_STATIC_TEST( type<Float32>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Float64>.isarithmetic());
    TYPE_UTILITY_STATIC_TEST( type<Float128>.isarithmetic());




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

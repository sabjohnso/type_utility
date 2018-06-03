//
// ... Type Utility header files
//
#include <type_utility/integer.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>
#include <type_utility_testing/test_tools.hpp>


/** Test integer constant sequeces */
struct Integer_test
{
  Integer_test() : accum( 0 ) {
    using namespace TypeUtility::Core;
    using TypeUtility::Testing::string_repr;
    TYPE_UTILITY_STATIC_TEST( integer<int,0> == integer<int,0> );
    TYPE_UTILITY_STATIC_TEST( succ( integer<int,0> ) == integer<int,1> );
    TYPE_UTILITY_STATIC_TEST( pred( integer<int,0> ) == integer<int,-1> );
    TYPE_UTILITY_STATIC_TEST( integer<int,2> + integer<int,3> == integer<int,5> );
    TYPE_UTILITY_STATIC_TEST( integer<int,2> - integer<int,3> == integer<int,-1> );
    TYPE_UTILITY_STATIC_TEST( integer<int,2> * integer<int,3> == integer<int,6> );
    TYPE_UTILITY_STATIC_TEST( integer<int,2> / integer<int,3> == integer<int,0> );
    TYPE_UTILITY_STATIC_TEST( integer<int,3> / integer<int,2> == integer<int,1> );
    TYPE_UTILITY_STATIC_TEST( integer<int,6> / integer<int,2> == integer<int,3> );
    TYPE_UTILITY_STATIC_TEST( integer<int,3> % integer<int,2> == integer<int,1> );


    TYPE_UTILITY_TEST( accum, integer<int,0> == integer<int,0> );
    TYPE_UTILITY_TEST( accum, succ( integer<int,0> ) == integer<int,1> );
    TYPE_UTILITY_TEST( accum, pred( integer<int,0> ) == integer<int,-1> );
    TYPE_UTILITY_TEST( accum, integer<int,2> + integer<int,3> == integer<int,5> );
    TYPE_UTILITY_TEST( accum, integer<int,2> - integer<int,3> == integer<int,-1> );
    TYPE_UTILITY_TEST( accum, integer<int,2> * integer<int,3> == integer<int,6> );
    TYPE_UTILITY_TEST( accum, integer<int,2> / integer<int,3> == integer<int,0> );
    TYPE_UTILITY_TEST( accum, integer<int,3> / integer<int,2> == integer<int,1> );
    TYPE_UTILITY_TEST( accum, integer<int,6> / integer<int,2> == integer<int,3> );
    TYPE_UTILITY_TEST( accum, integer<int,3> % integer<int,2> == integer<int,1> );

    TYPE_UTILITY_TEST( accum, string_repr( integer<short,2> ) == "[2:short]" );
    TYPE_UTILITY_TEST( accum, string_repr( integer<int,1> ) == "[1:int]" );
    TYPE_UTILITY_TEST( accum, string_repr( integer<size_t, 10> ) == "[10:unsigned long]" );

  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Integer_test



int
main( int, char** )
{
  int accum = 0;
  accum += Integer_test();
  return accum;
}

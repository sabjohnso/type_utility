//
// ... Type Utility header files
//
#include <type_utility/type_utility.hpp>

//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>

using namespace TypeUtility;


/** Test taking types */
struct Take_types_test
{
  Take_types_test() : accum( 0 ) {

    TYPE_UTILITY_STATIC_TEST( take( types<>,   nat<0> ) == types<> );
    TYPE_UTILITY_STATIC_TEST( take( types<int>,nat<0> ) == types<> );
    TYPE_UTILITY_STATIC_TEST( take( types<int>,nat<1> ) == types<int> );
    TYPE_UTILITY_STATIC_TEST( take( types<short,int,long>, nat<0> ) == types<> );
    TYPE_UTILITY_STATIC_TEST( take( types<short,int,long>, nat<1> ) == types<short> );
    TYPE_UTILITY_STATIC_TEST( take( types<short,int,long>, nat<2> ) == types<short,int> ); 
    TYPE_UTILITY_STATIC_TEST( take( types<short,int,long>, nat<3> ) == types<short,int,long>);
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Take_types_test



/** Test taking integers  */
struct Take_integers_test
{
  Take_integers_test() : accum( 0 ) {
    TYPE_UTILITY_STATIC_TEST( take( integers<int,1,2,3,4>, nat<0> ) == integers<int> );
    TYPE_UTILITY_STATIC_TEST( take( integers<int,1,2,3,4>, nat<1> ) == integers<int,1> );
    TYPE_UTILITY_STATIC_TEST( take( integers<int,1,2,3,4>, nat<2> ) == integers<int,1,2> );
    TYPE_UTILITY_STATIC_TEST( take( integers<int,1,2,3,4>, nat<3> ) == integers<int,1,2,3> );
    TYPE_UTILITY_STATIC_TEST( take( integers<int,1,2,3,4>, nat<4> ) == integers<int,1,2,3,4> );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Take_integers_test



/** Test dropping types */
struct Drop_types_test
{
  Drop_types_test() : accum( 0 ) {
    TYPE_UTILITY_STATIC_TEST( drop( types<short,int,long>, nat<0> ) == types<short,int,long> );
    TYPE_UTILITY_STATIC_TEST( drop( types<short,int,long>, nat<1> ) == types<int,long> );
    TYPE_UTILITY_STATIC_TEST( drop( types<short,int,long>, nat<2> ) == types<long> );
    TYPE_UTILITY_STATIC_TEST( drop( types<short,int,long>, nat<3> ) == types<> );
                
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Drop_types_test



/** Test dropping integers */
struct Drop_integers_test
{
  Drop_integers_test() : accum( 0 ) {

    TYPE_UTILITY_STATIC_TEST( drop( integers<int,1,2,3,4>, nat<0> ) == integers<int,1,2,3,4> );
    TYPE_UTILITY_STATIC_TEST( drop( integers<int,1,2,3,4>, nat<1> ) == integers<int,2,3,4> );
    TYPE_UTILITY_STATIC_TEST( drop( integers<int,1,2,3,4>, nat<2> ) == integers<int,3,4> );
    TYPE_UTILITY_STATIC_TEST( drop( integers<int,1,2,3,4>, nat<3> ) == integers<int,4> );
    TYPE_UTILITY_STATIC_TEST( drop( integers<int,1,2,3,4>, nat<4> ) == integers<int> );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Drop_integers_test

int
main( int, char** )
{
  int accum = 0;
  accum += Take_types_test();
  accum += Take_integers_test();
  accum += Drop_types_test();
  accum += Drop_integers_test();
  return accum;
}

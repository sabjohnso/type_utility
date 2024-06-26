//
// ... Type Utility header files
//
#include <type_utility/integer.hpp>
#include <type_utility/type_utility.hpp>

//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>
#include <type_utility_testing/test_tools.hpp>


/** Test integer constant sequeces */
struct Integer_test {

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
    TYPE_UTILITY_STATIC_TEST( integers<int,0> == integers<int,0> );
    TYPE_UTILITY_STATIC_TEST( integers<int,1,2,3> == integers<int,1,2,3> );
    TYPE_UTILITY_STATIC_TEST( ! (integers<int,0,2,3> == integers<int,1,2,3> ));
    TYPE_UTILITY_STATIC_TEST( ! ismember( integers<int>, integer<int,0> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integers<int,0>, integer<int,0> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integers<int,0,1>, integer<int,0>));
    TYPE_UTILITY_STATIC_TEST( ismember( integers<int,0,1>, integer<int,1>));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1>, integer<int,0> ));
    TYPE_UTILITY_STATIC_TEST( issubset( integer_set<int,0,1>, integer_set<int> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1,2,3,4>, integer<int,0> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1,2,3,4>, integer<int,1> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1,2,3,4>, integer<int,2> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1,2,3,4>, integer<int,3> ));
    TYPE_UTILITY_STATIC_TEST( ismember( integer_set<int,0,1,2,3,4>, integer<int,4> ));
    TYPE_UTILITY_STATIC_TEST( issubset( integer_set<int,0,1>, integer_set<int,0> ));
    TYPE_UTILITY_STATIC_TEST( integer_set<int> == integer_set<int> );
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0> == integer_set<int,0> );
    TYPE_UTILITY_STATIC_TEST( issubset( integer_set<int,0>, integer_set<int> ));
    TYPE_UTILITY_STATIC_TEST( issubset( integer_set<int,0>, integer_set<int,0> ));
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0,1> == integer_set<int,0,1> );
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0,1,2> == integer_set<int,0,1,2> );
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0,1,2> == integer_set<int,1,2,0> );
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0,1,2> == integer_set<int,2,0,1> );
    TYPE_UTILITY_STATIC_TEST( !( integer_set<int,0,1,2> == integer_set<int,2,0> ));
    TYPE_UTILITY_STATIC_TEST( integer_set<int,0,1,2> != integer_set<int,2,0> );
    TYPE_UTILITY_STATIC_TEST(
      integer_set_intersection( integer_set<int,0,1>, integer_set<int,1,2> ) ==
      integer_set<int,1>);
    TYPE_UTILITY_STATIC_TEST(
      integer_set_difference( integer_set<int,0,1,2>, integer_set<int,1,2> ) ==
      integer_set<int,0> );
    TYPE_UTILITY_STATIC_TEST(
      integer_set_remove( integer_set<int,0,1,2>, integer<int,2> ) ==
      integer_set<int,0,1> );
  }

  operator int() const { return accum; }

  int accum;

}; // end of struct Integer_test


/** Test the generation of an index sequence */
struct Generate_indices_test{

  Generate_indices_test() : accum( 0 ) {
    from_integer_test();
    from_types_test();
  }

  void
  from_integer_test(){
    using namespace TypeUtility;
    using std::index_sequence;
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<0>())> == type<index_sequence<>> );
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<1>())> == type<index_sequence<0>> );
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<2>())> == type<index_sequence<0,1>> );
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<3>())> == type<index_sequence<0,1,2>> );
    TYPE_UTILITY_TEST( accum, type<decltype(generate_indices<0>())> == type<index_sequence<>> );
    TYPE_UTILITY_TEST( accum, type<decltype(generate_indices<1>())> == type<index_sequence<0>> );
    TYPE_UTILITY_TEST( accum, type<decltype(generate_indices<2>())> == type<index_sequence<0,1>> );
    TYPE_UTILITY_TEST( accum, type<decltype(generate_indices<3>())> == type<index_sequence<0,1,2>> );
  }

  void
  from_types_test(){
    using namespace TypeUtility;
    using std::index_sequence;
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<>())> == type<index_sequence<>> );
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<int>())> == type<index_sequence<0>> );
    TYPE_UTILITY_STATIC_TEST( type<decltype(generate_indices<int,long>())> ==
			      type<index_sequence<0,1>> );
  }

  operator int() const { return accum; }

  int accum;

}; // end of struct Generate_indices_test


/** Test rotation of indices */
struct Rotate_test{

  Rotate_test() : accum( 0 ) {
    using namespace TypeUtility::Core;
    TYPE_UTILITY_STATIC_TEST( rotate( generate_indices<3>()) == index_sequence<1,2,0>());
    TYPE_UTILITY_STATIC_TEST( rotate( rotate( rotate( generate_indices<3>()))) ==
			      index_sequence<0,1,2>());
  }

  operator int() const { return accum; }

  int accum;

}; // end of struct Rotate_test



int
main( int, char** ){
  int accum = 0;
  accum += Integer_test();
  accum += Generate_indices_test();
  return accum;
}

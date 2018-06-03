//
// ... Type Utility header files
//
#include <type_utility/type_set.hpp>

//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>


/** UNDOCUMENTED TEST */
struct Type_set_test
{
  Type_set_test() : accum( 0 ) {
    using namespace TypeUtility::Core;

    TYPE_UTILITY_STATIC_TEST( ! type_set<>.ismember( type<int> ));
      
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Type_set_test

int
main( int, char** )
{
  int accum = 0;
    
  return accum;
}

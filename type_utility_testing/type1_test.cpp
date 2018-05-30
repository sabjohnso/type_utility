//
// ... Type Utility header files
//
#include <type_utility/type1.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>

/** Test type template proxy functionality 
 */
struct Type1Test
{
  Type1Test() : accum( 0 ) {
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Type1Test



int
main( int, char** )
{
  int accum = 0;
  accum += Type1Test();
  return accum;
}

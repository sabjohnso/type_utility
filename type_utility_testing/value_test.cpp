//
// ... Type Utility header files
//
#include <type_utility/type_utility.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>

/** Test  */
struct Value_test
{
  class MyValue : TypeUtility::Value<int> {
  public:
    using base = Value<int>;
    using base::base;

    using base::get;
  };
  
  Value_test() : accum( 0 ) {
    TYPE_UTILITY_STATIC_TEST( MyValue( 3 ).get() == 3 );
    
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct Value_test


int
main( int, char** )
{
  int accum = 0;
  accum += Value_test();
  return accum;
}

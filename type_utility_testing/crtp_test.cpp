//
// ... Standard header files
//
#include <string>
#include <sstream>

//
// ... Type Utility header files
//
#include <type_utility/crtp.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>


using namespace TypeUtility::Core;

template< typename T >
class Show : public CRTP<Show,T>{
public:
  template< typename Stream >
  friend Stream&
  operator <<( Stream& os, const Show& arg ){
    os << static_cast<const T&>( arg ).show();
    return os;
  }
  
}; // end of class Show


class Named : public Show<Named> {
public:

  Named( std::string input_name ) : name( input_name ){}

  std::string
  show() const & { return name; }
private:
  std::string name;
};
  
  

/**
 * @brief Test the CRTP base class
 */
struct CRTP_test
{
  CRTP_test() : accum( 0 ) {
    using std::stringstream;
    stringstream ss;
    ss << Named( "x" );
    TYPE_UTILITY_TEST( accum, ss.str() == "x" );
  }
  operator int() const { return accum; }
  int accum;
}; // end of struct CRTP_test

int
main( int, char** )
{
  int accum = 0;
  accum += CRTP_test();
  return accum;
}

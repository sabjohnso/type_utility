//
// ... Standard header files
//
#include <type_traits>
#include <cmath>
#include <string>
#include <sstream>


//
// ... Type Utility header files
//
#include <type_utility/config.hpp>
#include <type_utility/type.hpp>

//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>

using namespace TypeUtility::Core;


constexpr auto cosine = []( auto x ){ return std::cos( x ); };

template< typename T >
std::string
string_repr( const T& arg ){
  std::stringstream ss;
  ss << arg;
  return ss.str();
}



/** Test the type proxy class */
struct TypeTest
{
  TypeTest() : accum( 0 ) {
    construction_and_value_test();
    comparison_test();
    abstraction_test();
    print_test();
  }

  /** Test construction from type proxies 
   */
  void
  construction_and_value_test(){    
    TYPE_UTILITY_STATIC_TEST( std::is_same<int, typename Type<int>::type>::value );
    TYPE_UTILITY_STATIC_TEST( std::is_same<int,decltype( Type<int>::make( 3 ))>::value );
    TYPE_UTILITY_STATIC_TEST( std::is_same<int,decltype( type<int>( 3 ))>::value );

    auto value = type<int>( 3 );
    TYPE_UTILITY_TEST( accum, value == 3);
  }

  /** test equality comparison between type proxies comparison */
  void
  comparison_test(){
    
    TYPE_UTILITY_STATIC_TEST( type<int> == Type<int>{ });
    TYPE_UTILITY_STATIC_TEST( !( type<int> != Type<int>{ }));
    TYPE_UTILITY_STATIC_TEST( !( type<char> == type<int> ));
    TYPE_UTILITY_STATIC_TEST( type<char> != type<int> );

    
    TYPE_UTILITY_TEST( accum, type<int> == Type<int>{ });
    TYPE_UTILITY_TEST( accum, !( type<int> != Type<int>{ }));
    TYPE_UTILITY_TEST( accum, !( type<char> == type<int> ));
    TYPE_UTILITY_TEST( accum, type<char> != type<int> );
  }
  
  void
  abstraction_test(){
    
    TYPE_UTILITY_STATIC_TEST( type_transform( cosine, type<int> ) == type<double> );
    TYPE_UTILITY_STATIC_TEST( type_pure( 1 ) == type<int> );
    TYPE_UTILITY_STATIC_TEST( type_pure( 1u ) == type<unsigned> );
    TYPE_UTILITY_STATIC_TEST( type_apply( type_pure( cosine ), type<int> ) == type<double> );

    TYPE_UTILITY_STATIC_TEST(
      type_bind( type<int> , []( auto x ){ return type_pure( x ); }) == type<int> );

    TYPE_UTILITY_STATIC_TEST( type_join( type<Type<int>> ) == type<int> );

  }

  void
  print_test(){
    TYPE_UTILITY_TEST( accum,  string_repr( type<char> ) == "char" );
  }

  
  operator int() const { return accum; }
  int accum;
}; // end of struct TypeTest

int
main( int, char** )
{
  int accum = 0;
  accum += TypeTest();
  return accum;
}


//
// ... Type Utility header files
//
#include <type_utility/type_sequence.hpp>


//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>

using namespace TypeUtility::Core;

/** Test type sequences */
struct Type_sequence_test
{

  Type_sequence_test() : accum( 0 ) {
    count_test();
    has_type_test();
    find_type_test();
    sequence_test();
    list_test();
  }
  
  void
  count_test(){
    TYPE_UTILITY_STATIC_TEST( count_types<>() == 0 );
    TYPE_UTILITY_STATIC_TEST( count_types<int>() == 1 );
    TYPE_UTILITY_STATIC_TEST( count_types<int,double>() == 2 );

    TYPE_UTILITY_TEST( accum, count_types<>() == 0 );
    TYPE_UTILITY_TEST( accum, count_types<int>() == 1 );
    TYPE_UTILITY_TEST( accum, count_types<int,double>() == 2 );
  }

  void
  has_type_test(){
    TYPE_UTILITY_STATIC_TEST( ! Has_type<int>::value );
    TYPE_UTILITY_STATIC_TEST( Has_type<int,int>::value );
    TYPE_UTILITY_STATIC_TEST( ! Has_type<int, double>::value );
    TYPE_UTILITY_STATIC_TEST( Has_type<int,char,int>::value );

    TYPE_UTILITY_TEST( accum, ! Has_type<int>::value );
    TYPE_UTILITY_TEST( accum, Has_type<int,int>::value );
    TYPE_UTILITY_TEST( accum, ! Has_type<int, double>::value );
    TYPE_UTILITY_TEST( accum, Has_type<int,char,int>::value );
  }

  void
  find_type_test(){
    TYPE_UTILITY_STATIC_TEST( Find_type<int,int>::value == 0 );
    TYPE_UTILITY_STATIC_TEST( Find_type<int,char,int>::value == 1 );
    TYPE_UTILITY_STATIC_TEST( Find_type<int,char,int,double>::value == 1 );

    TYPE_UTILITY_STATIC_TEST( Find_type<char,char,short,int,long>::value == 0 );
    TYPE_UTILITY_STATIC_TEST( Find_type<short,char,short,int,long>::value == 1 );
    TYPE_UTILITY_STATIC_TEST( Find_type<int,char,short,int,long>::value == 2 );
    TYPE_UTILITY_STATIC_TEST( Find_type<long,char,short,int,long>::value == 3 );

    TYPE_UTILITY_TEST( accum, Find_type<int,int>::value == 0 );
    TYPE_UTILITY_TEST( accum, Find_type<int,char,int>::value == 1 );
    TYPE_UTILITY_TEST( accum, Find_type<int,char,int,double>::value == 1 );
  }

  void
  sequence_test(){
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.size() == 4 );
    
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.ismember<char>() );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.ismember<short>() );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.ismember<int>());
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.ismember<long>() );

    TYPE_UTILITY_STATIC_TEST( ! types<char,short,int,long>.ismember<double>() );
    
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.find<char>() == 0 );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.find<short>() == 1 );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.find<int>() == 2 );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.find<long>() == 3 );

    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.at<0>() == type<char> );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.at<1>() == type<short> );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.at<2>() == type<int> );
    TYPE_UTILITY_STATIC_TEST( types<char,short,int,long>.at<3>() == type<long> );

    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.size() == 4 );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.ismember<char>() );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.ismember<short>() );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.ismember<int>());
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.ismember<long>() );
    TYPE_UTILITY_TEST( accum, ! types<char,short,int,long>.ismember<double>() );    
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.find<char>() == 0 );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.find<short>() == 1 );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.find<int>() == 2 );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.find<long>() == 3 );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.at<0>() == type<char> );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.at<1>() == type<short> );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.at<2>() == type<int> );
    TYPE_UTILITY_TEST( accum, types<char,short,int,long>.at<3>() == type<long> );
  }

  void
  list_test(){

    constexpr auto char_types = type_list( type<char>, type<char16_t>, type<char32_t> );
    TYPE_UTILITY_STATIC_TEST( char_types == types<char,char16_t,char32_t> );
    TYPE_UTILITY_STATIC_TEST( length( char_types ) == 3 );
    TYPE_UTILITY_STATIC_TEST( head( char_types ) == type<char> );
    TYPE_UTILITY_STATIC_TEST( tail( char_types ) == types<char16_t,char32_t> );
    TYPE_UTILITY_STATIC_TEST( reverse( char_types ) == types<char32_t,char16_t,char> );
    TYPE_UTILITY_STATIC_TEST( 
      append( char_types, char_types ) ==
      types<char,char16_t,char32_t,char,char16_t,char32_t> );

    constexpr auto to_int = []( auto x ){ return int( x ); };
    
    TYPE_UTILITY_STATIC_TEST( type_sequence_transform<decltype(to_int)>( types<> ) == types<> );
    TYPE_UTILITY_STATIC_TEST( type_sequence_transform( to_int, types<> ) == types<> );
    TYPE_UTILITY_STATIC_TEST( type_sequence_transform( to_int, char_types ) == types<int,int,int> );
    TYPE_UTILITY_STATIC_TEST( type_sequence_pure( to_int ) == types<decay_t<decltype(to_int)>> );
    TYPE_UTILITY_STATIC_TEST(
      type_sequence_apply(
	type_sequence_pure( to_int ),
	char_types ) == types<int,int,int> );
    TYPE_UTILITY_STATIC_TEST(
      type_sequence_bind( char_types, []( auto x ){ return type_sequence_pure( x ); }) ==
      char_types );
  }
  
  
  
  operator int() const { return accum; }
  int accum;
}; // end of struct Type_sequence_test


int
main( int, char** )
{
  int accum = 0;
  accum += Type_sequence_test();
  return accum;
}

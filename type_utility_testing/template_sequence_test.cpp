//
// ... Testing header files
//
#include <type_utility_testing/test_macros.hpp>


//
// ... Type Utility header files
//
#include <type_utility/template_sequence.hpp>

namespace // anonymous
{
  using TypeUtility::Core::Template_sequence;


  
  class Template_sequence_tester
  {
    int accum = {0};
  public:
    operator int () const { return accum; }
    Template_sequence_tester(){

    }
  }; // end of class Template_sequene_tester
    

} // end of anonymous namespace 

int
main( int, char** )
{
  int accum = 0;
  accum += Template_sequence_tester{};
  return accum;
}

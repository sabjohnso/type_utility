#ifndef TEST_TOOLS_HPP_INCLUDED_482621442056030402
#define TEST_TOOLS_HPP_INCLUDED_482621442056030402 1

//
// ... Standard header files
//
#include <string>
#include <sstream>


namespace TypeUtility::Testing{

  using std::string;
  using std::stringstream;

  template< typename T >
  string
  string_repr( const T& arg ){
    stringstream ss;
    ss << arg;
    return ss.str();
  }

} // end of namespace TypeUtility::Testing

#endif // !defined TEST_TOOLS_HPP_INCLUDED_482621442056030402

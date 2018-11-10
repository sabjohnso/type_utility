#ifndef TEMPLATE_SEQUENCE_HPP_INCLUDED_136933748870103469
#define TEMPLATE_SEQUENCE_HPP_INCLUDED_136933748870103469 1

namespace TypeUtility::Core
{
  
  template< template< typename ... > typename ... Ks >
  class Template_sequence
  {}; // end of class


  template< template< typename ... > typename ... Ks >
  constexpr Template_sequence<Ks ...> templates{};

  

  


} // end of namespace TypeUtility::Core

#endif // !defined TEMPLATE_SEQUENCE_HPP_INCLUDED_136933748870103469

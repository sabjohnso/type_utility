#ifndef TYPE_UTILITY_HPP_INCLUDED_1323111970257335075
#define TYPE_UTILITY_HPP_INCLUDED_1323111970257335075 1

//
// ... Type Utility header files
//
#include <type_utility/type.hpp>
#include <type_utiliy/type1.hpp>
#include <type_utility/type_sequence.hpp>
#include <base_types.hpp>



namespace TypeUtility
{

  //
  // ... base types
  //
  using Core::Int;
  using Core::UInt;
  using Core::Float;

  //
  // ... type proxies
  //  
  using Core::Type;
  using Core::type;
  using Core::type_transform;
  using Core::type_pure;
  using Core::type_apply;
  using Core::type_bind;
  using Core::type_join;


  //
  // ... template proxies
  //
  using Core::Type1;
  using Core::type1;


  //
  // ... type sequences
  //
  using Core::Type_sequence;
  using Core::cons;
  using Core::head;
  using Core::tail;
  using Core::length;
  using Core::rappend;
  using Core::append;
  using Core::reverse;
  using Core::type_sequence_transform;
  using Core::Type_sequence_pure;
  using Core::Type_sequence_apply;
  using Core::Type_sequence_bind;
  using Core::Type_sequence_join;

  
  



  
  
  
} // end of namespace TypeUtility

#endif // !defined TYPE_UTILITY_HPP_INCLUDED_1323111970257335075

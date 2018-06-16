#ifndef TYPE_UTILITY_HPP_INCLUDED_1323111970257335075
#define TYPE_UTILITY_HPP_INCLUDED_1323111970257335075 1

//
// ... Type Utility header files
//
#include <type_utility/type.hpp>
#include <type_utility/type1.hpp>
#include <type_utility/type_sequence.hpp>
#include <type_utility/type_set.hpp>
#include <type_utility/integer.hpp>
#include <type_utility/base_types.hpp>
#include <type_utility/crtp.hpp>
#include <type_utility/undeletable.hpp>
#include <type_utility/value.hpp>
#include <type_utility/take.hpp>
#include <type_utility/drop.hpp>



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
  using Core::types;
  using Core::cons;
  using Core::head;
  using Core::tail;
  using Core::length;
  using Core::rappend;
  using Core::append;
  using Core::reverse;
  using Core::type_sequence_transform;
  using Core::type_sequence_pure;
  using Core::type_sequence_apply;
  using Core::type_sequence_bind;
  using Core::type_sequence_join;


  using Core::take;
  using Core::drop;


  //
  // ... type sets
  //
  using Core::Type_set;


  //
  // ... integers
  //
  using Core::Nat;
  using Core::nat;
  using Core::Integer;
  using Core::integer;
  using Core::integer_sequence;
  using Core::integers;

  using Core::generate_indices;

  //
  // ... integer sets
  //
  using Core::Integer_set;
  using Core::integer_set;
  using Core::integer_set_add;
  using Core::integer_set_remove;
  using Core::integer_set_union;
  using Core::integer_set_intersection;
  using Core::integer_set_difference;
  using Core::integer_set_symmetric_difference;
  


  //
  // ... CRTP
  //
  using Core::Base_delete_protection;
  using Core::CRTP;
  

  //
  // ... Value
  //
  using Core::Value;


  
  
  
} // end of namespace TypeUtility

#endif // !defined TYPE_UTILITY_HPP_INCLUDED_1323111970257335075

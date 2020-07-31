#pragma once

//
// ... Type Utility header files
//
#include <type_utility/base_types.hpp>
#include <type_utility/crtp.hpp>
#include <type_utility/drop.hpp>
#include <type_utility/integer.hpp>
#include <type_utility/integer_set.hpp>
#include <type_utility/take.hpp>
#include <type_utility/type.hpp>
#include <type_utility/type1.hpp>
#include <type_utility/type_sequence.hpp>
#include <type_utility/type_set.hpp>
#include <type_utility/value.hpp>

namespace TypeUtility {
  //
  // ... size
  //
  using Core::size_type;

  //
  // ... base types
  //
  using Core::Float;
  using Core::Int;
  using Core::UInt;

  //
  // ... type proxies
  //
  using Core::Type;
  using Core::type;
  using Core::type_apply;
  using Core::type_bind;
  using Core::type_join;
  using Core::type_pure;
  using Core::type_transform;

  //
  // ... template proxies
  //
  using Core::Type1;
  using Core::type1;

  //
  // ... type sequences
  //
  using Core::append;
  using Core::cons;
  using Core::head;
  using Core::length;
  using Core::rappend;
  using Core::reverse;
  using Core::tail;
  using Core::Type_sequence;
  using Core::type_sequence_apply;
  using Core::type_sequence_bind;
  using Core::type_sequence_join;
  using Core::type_sequence_pure;
  using Core::type_sequence_transform;
  using Core::types;

  using Core::drop;
  using Core::select;
  using Core::take;

  using Core::nth_type;

  //
  // ... type sets
  //
  using Core::Type_set;

  //
  // ... integers
  //
  using Core::Integer;
  using Core::integer;
  using Core::integer_sequence;
  using Core::integers;
  using Core::Nat;
  using Core::nat;

  using Core::generate_indices;

  //
  // ... integer sets
  //
  using Core::Integer_set;
  using Core::integer_set;
  using Core::integer_set_add;
  using Core::integer_set_difference;
  using Core::integer_set_intersection;
  using Core::integer_set_remove;
  using Core::integer_set_symmetric_difference;
  using Core::integer_set_union;

  using Core::rotate;

  //
  // ... CRTP
  //
  using Core::CRTP;

  //
  // ... Value
  //
  using Core::Value;

  using Core::count_args;
  using Core::count_types;
  using Core::type_count;

  using Core::operator<<;

} // end of namespace TypeUtility

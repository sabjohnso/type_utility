


if( TYPE_UTILITY_USE_RTTI )
  set( TYPE_UTILITY_RTTI_USED true )
else()
  set( TYPE_UTILITY_RTTI_USED false )
endif()

configure_file( config.hpp.in config.hpp )


install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  import.hpp
  drop.hpp
  take.hpp
  type.hpp
  type1.hpp
  type_sequence.hpp
  type_sequence_utility.hpp
  type_set.hpp
  base_types.hpp
  integer.hpp
  integer_set.hpp
  undeletable.hpp
  crtp.hpp
  type_utility.hpp
  value.hpp
  DESTINATION ${TYPE_UTILITY_INSTALL_INCLUDE_DIR})



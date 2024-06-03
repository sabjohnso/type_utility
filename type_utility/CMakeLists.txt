if(type_utility_USE_RTTI)
  set(type_utility_RTTI_USED true)
else()
  set(type_utility_RTTI_USED false)
endif()

configure_file(config.hpp.in config.hpp)

install(
  TARGETS ${type_utility_CONFIG_NAME}
  EXPORT type_utility
  DESTINATION ${type_utility_INSTALL_EXEC_DIR}
)

install(FILES
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
  crtp.hpp
  template_sequence.hpp
  partial_template.hpp
  type_utility.hpp
  value.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/type_utility
)

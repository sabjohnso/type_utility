#
# ... Build script for type_utility
#
cmake_minimum_required(VERSION 3.22)

project(type_utility VERSION 0.3.1 LANGUAGES CXX)

set(type_utility_COMPILE_FEATURES cxx_std_23)
list(INSERT CMAKE_MODULE_PATH 0 ${type_utility_SOURCE_DIR}/cmake)

include(type_utility_deps)
include(GNUInstallDirs)

#
# ... Build options
#
option(type_utility_BUILD_TESTING  "Build the type_utility  tests" ON)
option(type_utility_USE_RTTI "Use runtime type information" OFF)
option(type_utility_BUILD_DOCUMENTATION "Build the documentation" OFF)

add_library(type_utility_compiler_settings INTERFACE)
target_compile_features(type_utility_compiler_settings INTERFACE ${type_utility_COMPILE_FEATURES})
set_target_properties(type_utility_compiler_settings PROPERTIES EXPORT_NAME compiler_settings)
if(type_utility_USE_RTTI)
  target_compile_definitions(type_utility_compiler_settings INTERFACE TYPE_UTILITY_USE_RTTI)
endif()
add_library(type_utility::compiler_settings ALIAS type_utility_compiler_settings)

#
# ... Add the interface library
#
add_library(type_utility_header INTERFACE)

target_include_directories(type_utility_header INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${type_utility_SOURCE_DIR}>
  $<BUILD_INTERFACE:${type_utility_BINARY_DIR}>
)
target_link_libraries(type_utility_header INTERFACE type_utility::compiler_settings)
set_target_properties(type_utility_header PROPERTIES EXPORT_NAME header)
add_library(type_utility::header ALIAS type_utility_header)

#
# ... Walk the source tree
#
add_subdirectory(type_utility)

#
# ... Build the tests
#
if(type_utility_BUILD_TESTING)
  enable_testing()
  add_subdirectory(type_utility_testing)
endif()

if(type_utility_BUILD_DOCUMENTATION)
  set(type_utility_INSTALL_DOC_DIR
    share/doc/type_utility-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    CACHE PATH "Path for the installation of the type utility documentation"
  )

  set(type_utility_INSTALL_MAN_DIR
    share
    CACHE PATH "Path for the installation of the type utility manual pages"
  )

  find_package(Doxygen REQUIRED )
  configure_file(Doxyfile.in Doxyfile)
  add_custom_command(
    OUTPUT ${type_utility_BINARY_DIR}/type_utility_doxygen.log
    COMMAND "${DOXYGEN_EXECUTABLE}" "${type_utility_BINARY_DIR}/Doxyfile" > type_utility_doxygen.log
    MAIN_DEPENDENCY "${type_utility_BINARY_DIR}/Doxyfile"
    DEPENDS
    ${type_utility_SOURCE_DIR}/type_utility/base_types.hpp
    ${type_utility_SOURCE_DIR}/type_utility/config.hpp.in
    ${type_utility_SOURCE_DIR}/type_utility/import.hpp
    ${type_utility_SOURCE_DIR}/type_utility/type1.hpp
    ${type_utility_SOURCE_DIR}/type_utility/type.hpp
    ${type_utility_SOURCE_DIR}/type_utility/type_sequence.hpp
    ${type_utility_SOURCE_DIR}/type_utility/type_utility.hpp
    ${type_utility_SOURCE_DIR}/type_utility/type_utility.hpp
    WORKING_DIRECTORY ${type_utility_BINARY_DIR}
  )

  add_custom_target(
    affix_documentation ALL
    DEPENDS ${type_utility_BINARY_DIR}/type_utility_doxygen.log
  )

  install(DIRECTORY ${type_utility_BINARY_DIR}/doc/html DESTINATION ${type_utility_INSTALL_DOC_DIR})
  install(DIRECTORY ${type_utility_BINARY_DIR}/doc/man DESTINATION ${type_utility_INSTALL_MAN_DIR})
endif(type_utility_BUILD_DOCUMENTATION)

#
# ... Header library target
#
install(TARGETS type_utility_compiler_settings type_utility_header
  EXPORT type_utility_EXPORTS
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility
)

install(EXPORT type_utility_EXPORTS
  NAMESPACE type_utility::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility
  FILE type_utility-exports.cmake
)

configure_file(type_utility-config.cmake.in type_utility-config.cmake)
install( FILES ${type_utility_BINARY_DIR}/type_utility-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility)


# end of build definition for type_utility

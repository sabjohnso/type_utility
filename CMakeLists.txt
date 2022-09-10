#
# ... Build script for type_utility
#
cmake_minimum_required( VERSION 3.8 )

project( TYPE_UTILITY VERSION 0.3.1 LANGUAGES CXX )
set(TYPE_UTIITY_CXX_STANDARD 20 CACHE STRING "C++ standard for TYPE_UTILITY")
list( INSERT CMAKE_MODULE_PATH 0 ${TYPE_UTILITY_SOURCE_DIR}/cmake )

include( type_utility_deps )
include( GNUInstallDirs )

#
# ... Build options
#
option( BUILD_TYPE_UTILITY_TESTING  "Build the type_utility  tests" ON )
option( TYPE_UTILITY_USE_RTTI "Use runtime type information" ON )
option( BUILD_TYPE_UTILITY_DOCUMENTATION "Build the documentation" OFF )


#
# ... Add the interface library
#
add_library( type_utility INTERFACE )

target_include_directories( type_utility INTERFACE
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<BUILD_INTERFACE:${TYPE_UTILITY_SOURCE_DIR}>
  $<BUILD_INTERFACE:${TYPE_UTILITY_BINARY_DIR}> )

add_library( type_utility::type_utility ALIAS type_utility )

#
# ... Walk the source tree
#
add_subdirectory( type_utility )


#
# ... Build the tests
#
if( BUILD_TYPE_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( type_utility_testing )
endif( BUILD_TYPE_UTILITY_TESTING )

if( BUILD_TYPE_UTILITY_DOCUMENTATION )
  set( TYPE_UTILITY_INSTALL_DOC_DIR
    share/doc/type_utility-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    CACHE PATH "Path for the installation of the type utility documentation" )

  set( TYPE_UTILITY_INSTALL_MAN_DIR
    share
    CACHE PATH "Path for the installation of the type utility manual pages" )

  find_package( Doxygen REQUIRED  )
  configure_file( Doxyfile.in Doxyfile )
  add_custom_command(
    OUTPUT ${TYPE_UTILITY_BINARY_DIR}/type_utility_doxygen.log
    COMMAND "${DOXYGEN_EXECUTABLE}" "${TYPE_UTILITY_BINARY_DIR}/Doxyfile" > type_utility_doxygen.log
    MAIN_DEPENDENCY "${TYPE_UTILITY_BINARY_DIR}/Doxyfile"
    DEPENDS
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/base_types.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/config.hpp.in
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/import.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/type1.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/type.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/type_sequence.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/type_utility.hpp
    ${TYPE_UTILITY_SOURCE_DIR}/type_utility/type_utility.hpp

    WORKING_DIRECTORY ${TYPE_UTILITY_BINARY_DIR} )

  add_custom_target(
    affix_documentation ALL
    DEPENDS ${TYPE_UTILITY_BINARY_DIR}/type_utility_doxygen.log )

  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/html DESTINATION ${TYPE_UTILITY_INSTALL_DOC_DIR} )
  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/man DESTINATION ${TYPE_UTILITY_INSTALL_MAN_DIR} )
endif( BUILD_TYPE_UTILITY_DOCUMENTATION )

#
# ... Header library target
#
install( TARGETS type_utility
  EXPORT type_utility
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility )

install( EXPORT type_utility
  NAMESPACE type_utility::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility
  FILE type_utility-exports.cmake )

configure_file(type_utility-config.cmake.in type_utility-config.cmake)
install( FILES ${TYPE_UTILITY_BINARY_DIR}/type_utility-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/type_utility)


# end of build definition for type_utility

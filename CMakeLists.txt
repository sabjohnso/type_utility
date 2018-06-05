#
# ... Build script for type_utility
#
cmake_minimum_required( VERSION 3.8 )

project( TYPE_UTILITY )


include( cmake/version.cmake )


option( BUILD_TYPE_UTILITY_TESTING  "Build the type_utility  tests" ON )
option( TYPE_UTILITY_USE_VERSION_NAMESPACE "Add the version to the type utility namespace" OFF )
option( TYPE_UTILITY_USE_RTTI "Use runtime type information" ON )
option( TYPE_UTILITY_ACTIVATE_VERSION_ON_INSTALLATION
  "Link the unversioned include directory to this version." ON )
option( BUILD_TYPE_UTILITY_DOCUMENTATION "Build the documentation" ON )

set( TYPE_UTILITY_NAMESPACE TypeUtility
  CACHE STRING "The top-level namespace to use for the type utility library" )


string( CONCAT TYPE_UTILITY_VERSION
  ${TYPE_UTILITY_MAJOR} "_" ${TYPE_UTILITY_MINOR} "_" ${TYPE_UTILITY_UPDATE})



if( TYPE_UTILITY_USE_VERSION_NAMESPACE )
  string(APPEND TYPE_UTILITY_NAMESPACE ${TYPE_UTILITY_VERSION})
endif( TYPE_UTILITY_USE_VERSION_NAMESPACE )


if( NOT TYPE_UTILITY_INSTALL_INCLUDE_DIR )
  set( TYPE_UTILITY_INSTALL_INCLUDE_DIR
    include/type_utility
    CACHE PATH "Path for the installation of the type utility header files" )
endif( NOT TYPE_UTILITY_INSTALL_INCLUDE_DIR )


include_directories( 
  ${TYPE_UTILITY_SOURCE_DIR}
  ${TYPE_UTILITY_BINARY_DIR} )

add_subdirectory( type_utility )

if( BUILD_TYPE_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( type_utility_testing )
endif( BUILD_TYPE_UTILITY_TESTING )



if( BUILD_TYPE_UTILITY_DOCUMENTATION )

  
  if( NOT TYPE_UTILITY_INSTALL_DOC_DIR )
    set( TYPE_UTILITY_INSTALL_DOC_DIR
      share/doc/type_utility-${TYPE_UTILITY_MAJOR}.${TYPE_UTILITY_MINOR}
      CACHE PATH "Path for the installation of the type utility documentation" )
  endif( NOT TYPE_UTILITY_INSTALL_DOC_DIR )

  if( NOT TYPE_UTILITY_INSTALL_MAN_DIR )
    set( TYPE_UTILITY_INSTALL_MAN_DIR
      share
      CACHE PATH "Path for the installation of the type utility manual pages" )
  endif( NOT TYPE_UTILITY_INSTALL_MAN_DIR )
  


  
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
  
  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/html DESTINATION ${TYPE_UTILITY_INSTALL_DOC_DIR})
  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/man DESTINATION ${TYPE_UTILITY_INSTALL_MAN_DIR})
endif( BUILD_TYPE_UTILITY_DOCUMENTATION )


install( SCRIPT cmake/post_install.cmake )

# end of build definition for type_utility


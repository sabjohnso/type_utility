#
# ... Build script for type_utility
#
cmake_minimum_required( VERSION 3.8 )

project( TYPE_UTILITY )
set( TYPE_UTILITY_MAJOR 0)
set( TYPE_UTILITY_MINOR 1)
set( TYPE_UTILITY_UPDATE 0)

set( TYPE_UTILITY_VERSION type_utility-${TYPE_UTILITY_MAJOR}.{TYPE_UTILITY_MINOR})
set( TYPE_UTILITY_VERSION_UPDATE ${TYPE_UTILITY_VERSION}.${TYPE_UTILITY_UPDATE} )



option( BUILD_TYPE_UTILITY_TESTING  "Build the type_utility  tests" ON )
option( TYPE_UTILITY_USE_RTTI "Use runtime type information" ON )
option( BUILD_TYPE_UTILITY_DOCUMENTATION "Build the documentation" ON )


set( TYPE_UTILITY_INSTALL_INCLUDE_DIR include/type_utility
  CACHE PATH "Path for the installation of the type utility header files" )


include_directories( 
  ${TYPE_UTILITY_SOURCE_DIR}
  ${TYPE_UTILITY_BINARY_DIR} )

add_subdirectory( type_utility )

if( BUILD_TYPE_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( type_utility_testing )
endif( BUILD_TYPE_UTILITY_TESTING )



if( BUILD_TYPE_UTILITY_DOCUMENTATION )
  set( TYPE_UTILITY_INSTALL_DOC_DIR
    share/doc/type_utility-${TYPE_UTILITY_MAJOR}.${TYPE_UTILITY_MINOR}
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
  
  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/html DESTINATION ${TYPE_UTILITY_INSTALL_DOC_DIR})
  install( DIRECTORY ${TYPE_UTILITY_BINARY_DIR}/doc/man DESTINATION ${TYPE_UTILITY_INSTALL_MAN_DIR})
endif( BUILD_TYPE_UTILITY_DOCUMENTATION )


install( SCRIPT cmake/post_install.cmake )

# end of build definition for type_utility


#
# ... Build script for type_utility
#
cmake_minimum_required( VERSION 3.8 )

project( TYPE_UTILITY )


include( cmake/version.cmake )


option( BUILD_TYPE_UTILITY_TESTING  "Build the type_utility  tests" ON )
option( TYPE_UTILITY_USE_VERSION_NAMESPACE "Add the version to the type utility namespace" OFF )
option( TYPE_UTILITY_USE_RTTI "Use runtime type information" ON )

set( TYPE_UTILITY_NAMESPACE TypeUtility
  CACHE STRING "The top-level namespace to use for the type utility library" )


string( CONCAT TYPE_UTILITY_VERSION
  ${TYPE_UTILITY_MAJOR} "_" ${TYPE_UTILITY_MINOR} "_" ${TYPE_UTILITY_UPDATE})


if( TYPE_UTILITY_USE_VERSION_NAMESPACE )
  string(APPEND TYPE_UTILITY_NAMESPACE ${TYPE_UTILITY_VERSION})
endif( TYPE_UTILITY_USE_VERSION_NAMESPACE )
  

include_directories( 
  ${TYPE_UTILITY_SOURCE_DIR}
  ${TYPE_UTILITY_BINARY_DIR} )

add_subdirectory( type_utility )

if( BUILD_TYPE_UTILITY_TESTING )
  enable_testing()
  add_subdirectory( type_utility_testing )
endif( BUILD_TYPE_UTILITY_TESTING )

# end of build definition for type_utility



if( TYPE_UTILITY_USE_RTTI )
  set( TYPE_UTILITY_RTTI_USED true )
else()
  set( TYPE_UTILITY_RTTI_USED false )
endif()

configure_file( config.hpp.in config.hpp )

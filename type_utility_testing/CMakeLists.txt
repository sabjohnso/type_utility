find_package(GTest)

macro( type_utility_add_simple_test name )
  add_executable( ${name}_test ${name}_test.cpp )
  set_target_properties( ${name}_test
    PROPERTIES
    CXX_STANDARD 17)
  target_link_libraries( ${name}_test PRIVATE type_utility )    
  add_test( ${name} ${name}_test )
endmacro( type_utility_add_simple_test name )

macro( type_utility_add_test name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries( ${exe_name}
    PRIVATE
    type_utility::type_utility
    GTest::gtest_main )
  set_target_properties( ${exe_name}
    PROPERTIES
    CXX_STANDARD 17 )
  add_test( ${name} ${exe_name} )
endmacro()

type_utility_add_test( type type_test type_test.cpp )


type_utility_add_simple_test( type1 )
type_utility_add_simple_test( type_sequence )
type_utility_add_simple_test( type_set )
type_utility_add_simple_test( base_types )
type_utility_add_simple_test( integer )
type_utility_add_simple_test( crtp )
type_utility_add_simple_test( value )
type_utility_add_simple_test( take_and_drop )
type_utility_add_simple_test( template_sequence )


type_utility_add_test(partial_template partial_template_test partial_template_test.cpp)

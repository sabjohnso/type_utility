find_package(Catch2)
find_package(GTest)

macro( type_utility_add_simple_test name )
  add_executable( ${name}_test ${name}_test.cpp)
  target_link_libraries( ${name}_test PRIVATE type_utility::header)
  add_test(${name} ${name}_test)
endmacro()

macro(type_utility_add_test test_name)
  set(exe_name ${test_name}_test)
  set(src_name ${exe_name}.cpp)
  add_executable(${exe_name} ${src_name})
  target_link_libraries(${exe_name}
    PRIVATE
    type_utility::header
    GTest::gtest_main )
  add_test(${test_name} ${exe_name})
endmacro()

type_utility_add_test( type type_test type_test.cpp )





type_utility_add_simple_test(integer)
type_utility_add_simple_test(crtp)
type_utility_add_simple_test(value)
type_utility_add_simple_test(take_and_drop)
type_utility_add_simple_test(template_sequence)

type_utility_add_test(type_set)
type_utility_add_test(base_types)
type_utility_add_test(type1)
type_utility_add_test(type_sequence)
type_utility_add_test(partial_template)

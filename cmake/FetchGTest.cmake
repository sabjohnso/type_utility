include(FetchContent)

option(BUILD_GTEST_EXTERNALLY "Build googletest outside of project" OFF)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest)

FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  
  if(NOT BUILD_GTEST_EXTERNALLY)
    
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    add_library(GTest::gtest ALIAS gtest)
    add_library(GTest::gtest_main ALIAS gtest_main)
    add_library(GTest::gmock ALIAS gmock)
    add_library(GTest::gmock_main ALIAS gmock_main)

  else()
    set(googletest_STAGING_DIR ${googletest_BINARY_DIR}/staging CACHE INTERNAL "")
       
    execute_process(
      COMMAND ${CMAKE_COMMAND}
      -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
      --Wno-dev
      -G ${CMAKE_GENERATOR}
      -DCMAKE_INSTALL_PREFIX=${googletest_STAGING_DIR}

      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      ${googletest_SOURCE_DIR}
      WORKING_DIRECTORY ${googletest_BINARY_DIR})

    execute_process(
      COMMAND ${CMAKE_MAKE_PROGRAM} install -j 
      WORKING_DIRECTORY ${googletest_BINARY_DIR})

    find_package(GTest REQUIRED PATHS ${googletest_STAGING_DIR})

  endif()  
endif()

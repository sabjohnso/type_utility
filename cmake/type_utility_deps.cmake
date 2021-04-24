if(NOT EXISTS ${PROJECT_SOURCE_DIR}/cmake_utilities/FindCMakeUtilities.cmake)
  find_package( Git REQUIRED )
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()
list(INSERT CMAKE_MODULE_PATH 0 ${TYPE_UTILITY_SOURCE_DIR}/cmake_utilities)
find_package(CMakeUtilties)

find_package(nlohmann_json REQUIRED)

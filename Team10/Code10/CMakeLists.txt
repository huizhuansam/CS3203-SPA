cmake_minimum_required (VERSION 3.20.2)
project (SPA)

# CMake settings
# Turn this on to view detailed build logs. Turn off to cut through noise.
set(CMAKE_VERBOSE_MAKEFILE off)


set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/cmake")
message (STATUS "${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR}")
include(cmake/PreventInSourceBuilds.cmake)

# Build type settings
if (NOT CMAKE_BUILD_TYPE)
  # Release build by default
  # To build in debug mode, run cmake with -DCMAKE_BUILD_TYPE=Debug
  # To build in CI mode, run cmake with -DCMAKE_BUILD_TYPE=CI
  set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler settings
include(cmake/CompilerSettings.cmake)

# C++ language settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if (CMAKE_BUILD_TYPE STREQUAL "CI")
  set(AUTOTESTER_ROOT "${CMAKE_CURRENT_LIST_DIR}/lib/autotester/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM_NAME}/Release")
else()
  set(AUTOTESTER_ROOT "${CMAKE_CURRENT_LIST_DIR}/lib/autotester/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
endif()

list(APPEND CMAKE_PREFIX_PATH "${AUTOTESTER_ROOT}")
find_package(autotester REQUIRED)
include_directories("${CMAKE_CURRENT_LIST_DIR}/lib") # include catch.hpp

add_subdirectory(src/spa)
add_subdirectory(src/autotester)
# add_subdirectory(src/autotester_gui)
add_subdirectory(src/unit_testing)
add_subdirectory(src/integration_testing)

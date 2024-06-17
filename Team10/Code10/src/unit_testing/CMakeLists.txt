file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../spa/src/*.cpp")

add_executable(unit_testing ${srcs})

target_link_libraries(unit_testing spa)

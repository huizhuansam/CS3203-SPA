file(GLOB_RECURSE srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(integration_testing ${srcs})

target_link_libraries(integration_testing spa)

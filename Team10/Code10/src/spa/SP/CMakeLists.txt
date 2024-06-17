# Get all .cpp files recursively from src directory
file(GLOB_RECURSE srcs "src/*.cpp")

# Create library from all source files
add_library(SP ${srcs})

# The following line allows SP to #include files from other libraries
target_link_libraries(SP PUBLIC PKB)
target_link_libraries(SP PUBLIC common)
# ONLY LINK WHAT YOU NEED

# The following line makes the listed directories available for other libraries/executables to #include
target_include_directories(SP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(SP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/exception)
target_include_directories(SP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/extractor)
target_include_directories(SP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/parser)
target_include_directories(SP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/tokenizer)
target_include_directories(SP PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/validator)

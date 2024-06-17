# Get all .cpp files recursively from src directory
file(GLOB_RECURSE srcs "src/*.cpp")

# Create library from all source files
add_library(QPS ${srcs})

target_link_libraries(QPS PUBLIC PKB)
target_link_libraries(QPS PUBLIC common)

# The following line makes the listed directories available for other libraries/executables to #include
target_include_directories(QPS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/evaluator)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/strategy)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/strategy/argument_types)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/strategy/strategy_types)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/strategy/stubs)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/exception)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/parser)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/result)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/tokenizer)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/validator)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/validator/syntax_validator)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/validator/semantic_validator)
target_include_directories(QPS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/optimizer)
target_include_directories(QPS PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/cache")

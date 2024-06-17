add_subdirectory(common)
add_subdirectory(PKB)
add_subdirectory(SP)
add_subdirectory(QPS)

add_library(spa INTERFACE)
target_link_libraries(spa INTERFACE PKB SP QPS common)

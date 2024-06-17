# common library
add_library(common STATIC
    src/FileReader.cpp
    src/StringHandler.cpp
)

# The following line makes the listed directories available for other libraries/executables to #include
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

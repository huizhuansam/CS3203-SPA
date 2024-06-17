# PKB library
add_library(PKB STATIC
        src/PKB.cpp
        # Add more source files as needed
        src/TwoWayMapManager.cpp
        src/relationship_manager/CallStarStore.cpp
        src/WriteFacade.cpp
        src/ReadFacade.cpp
        src/entity_manager/EntityManager.cpp
        src/entity_manager/EntitySetStore.cpp
        src/entity_manager/StatementStore.cpp
        src/pattern_manager/AssignExpPatternStore.cpp
        src/pattern_manager/PatternManager.cpp
        src/relationship_manager/RelationshipManager.cpp
        include/ReadFacadeStub.h
        include/WriteFacadeStub.h
 )

# The following line allows PKB to #include files from other libraries
target_link_libraries(PKB PUBLIC common)
# ONLY LINK WHAT YOU NEED

# The following line makes the listed directories available for other libraries/executables to #include
target_include_directories(PKB PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/relationship_manager
        ${CMAKE_CURRENT_SOURCE_DIR}/include/entity_manager
        ${CMAKE_CURRENT_SOURCE_DIR}/include/pattern_manager)

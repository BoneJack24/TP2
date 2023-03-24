set(TEST_SOURCES Tests.cpp ${PROJECT_SOURCE_DIR}/Graphe.cpp ${PROJECT_SOURCE_DIR}/ReseauAerien.cpp)

add_executable(
        Tests
        ${TEST_SOURCES}
)

target_include_directories(Tests PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(
        Tests
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(Tests)
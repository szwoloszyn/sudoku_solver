# tests/CMakeLists.txt

add_executable(unit_tests
    test_main.cpp
)

target_link_libraries(unit_tests
    sourceCode
    gtest
    gtest_main
    pthread
)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)

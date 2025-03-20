set(_test test_chapter7_refactored_3)
add_executable(${_test} Refactored_3.cpp)
target_link_libraries(
    ${_test}
    GTest::gtest_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})
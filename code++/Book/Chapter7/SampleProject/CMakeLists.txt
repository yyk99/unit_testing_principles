set(_test test_chapter7_sampleproject)
add_executable(${_test} SampleProject.cpp)
target_link_libraries(
    ${_test}
    GTest::gtest_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})
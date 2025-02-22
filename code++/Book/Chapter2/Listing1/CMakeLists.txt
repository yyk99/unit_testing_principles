add_executable(
    test_2_1 
    CustomerTests.cpp 
    Other.cpp
)

target_link_libraries(
    test_2_1
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_2_1)
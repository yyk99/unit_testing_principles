set (_test "test_ch2_lst2")
add_executable(
  ${_test} 
  CustomerTests.cpp 
  Other.cpp
)

target_link_libraries(
  ${_test}
  GTest::gtest
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${_test})

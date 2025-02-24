set (_test "test_ch2_lst1")
add_executable(
  ${_test} 
  CustomerTests.cpp 
  Other.cpp
)

target_link_libraries(
  ${_test}
  GTest::gtest_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})
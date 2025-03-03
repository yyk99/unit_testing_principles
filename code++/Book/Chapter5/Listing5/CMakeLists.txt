set (_test "test_chapter5_listing5")
add_executable(
  ${_test} 
  Listing5.cpp 
)

target_link_libraries(
  ${_test}
  GTest::gtest
  GTest::gmock_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})
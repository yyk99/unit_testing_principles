set (_test "test_chapter3_listing_6")
add_executable(
  ${_test} 
  DeliveryServiceTests.cpp 
)

target_link_libraries(
  ${_test}
  GTest::gtest
  GTest::gmock_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})
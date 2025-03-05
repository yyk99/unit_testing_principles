#
# Book/Chapter7/DomainEvents/CMakeLists.txt
#

set (_test "test_chapter7_DomainEvents")
add_executable(
  ${_test} 
  DomainEvents.cpp
)

target_link_libraries(
  ${_test}
  GTest::gtest
  GTest::gmock_main
)

set_target_properties(${_test} PROPERTIES FOLDER "Tests")

include(GoogleTest)
gtest_discover_tests(${_test})



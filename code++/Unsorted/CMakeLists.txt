include(GoogleTest)

macro (add_unsorted_test _test)
	add_executable(
		${_test}
		${_test}.cpp
	)

	target_link_libraries(
		${_test}
		GTest::gtest
		GTest::gmock
		GTest::gmock_main
	)

	set_target_properties(${_test} PROPERTIES FOLDER "Tests")
	gtest_discover_tests(${_test})
endmacro(add_unsorted_test)

add_unsorted_test(tiny_test)
add_unsorted_test(datetime_test)
add_unsorted_test(string_test)

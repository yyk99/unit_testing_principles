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
	)

	set_target_properties(${_test} PROPERTIES FOLDER "Tests")
	gtest_discover_tests(${_test})
endmacro()

add_unsorted_test(tiny_test)


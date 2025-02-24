# The source code examples

The source code examples from "Unit Testing Principles, Practices, and Patterns"
(See https://www.manning.com/books/unit-testing) 

The original examples are in C#

Added C++ "equivalents"

## Windows

	cmake -B build-vs2022-clang -S code++ -T ClangCL
	cmake --build build-vs2022-clang
	cmake --build build-vs2022-clang --target RUN_TESTS

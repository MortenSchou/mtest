add_executable(my_example_test my_test.c)
target_link_libraries(my_example_test mtest)

target_compile_options(my_example_test PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Automatically discover test cases in my_example_test and add them to CTest.
discover_tests(my_example_test)

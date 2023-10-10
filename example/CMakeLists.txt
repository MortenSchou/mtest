add_executable(my_example_test my_test.c)
target_link_libraries(my_example_test mtest)

# Automatically discover test cases in my_example_test and add them to CTest.
discover_tests(my_example_test)

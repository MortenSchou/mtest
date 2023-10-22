add_executable(test_mtest test_mtest.c)
target_link_libraries(test_mtest mtest)
# Avoid relying on hidden compiler behavior when compiling test_mtest.
target_compile_options(test_mtest PRIVATE -Wall -Wextra -Wpedantic)

# Automatically discover test cases in test_mtest and add them to CTest.
discover_tests(test_mtest)

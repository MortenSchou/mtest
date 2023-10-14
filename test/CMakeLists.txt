add_executable(test_mtest test_mtest.c)
target_link_libraries(test_mtest mtest)

# Automatically discover test cases in test_mtest and add them to CTest.
discover_tests(test_mtest)

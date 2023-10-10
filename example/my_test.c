#include "mtest.h"

TEST_CASE(my_first_test_case, {
    int i = 42;
    CHECK_EQ_INT(1, i);    // Test fails but test case continues.
    REQUIRE_GT_INT(i, 0);  // Test succeeds.
})

TEST_CASE(my_other_test_case, {
    double i = 3.14;
    // When comparing doubles, we need to specify a tolerance - here we choose 0.01
    REQUIRE_EQ_DOUBLE(4.0, i, 0.01);  // Test fails and the test case exits.
    CHECK_TRUE(1);                    // Not executed but it would succeed.
})

// This macro creates a main function that can call each test case, and it tells CTest which test cases are available.
MAIN_RUN_TESTS(my_first_test_case, my_other_test_case)

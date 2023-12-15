#include "mtest.h"

TEST_CASE(my_first_test_case, {
    int i = 42;
    // A simple check, similar to asking if `42 == i`.
    CHECK_EQ_INT(42, i);
})

TEST_CASE(my_other_test_case, {
    double i = 3.14;
    // When comparing doubles, we need to specify a tolerance - here we choose 0.01
    CHECK_EQ_DOUBLE(3.14, i, 0.01);
})

TEST_CASE(my_dependent_test_case, {
    double i = 0;
    // REQUIRE checks will stop executing a test case early if it fails.
    // This is helpful for when our test modifies a shared variable. For example:
    REQUIRE_EQ_INT(0, i++);
    // Now the following check would only make sense if the above condition succeeded.
    // Therefore, we say the above test is required, since otherwise our check wouldn't
    // give us any meaningful output.
    CHECK_EQ_INT(1, i);
})

// This macro creates a main function that can call each test case, and it tells CTest which test cases are available.
MAIN_RUN_TESTS(my_first_test_case, my_other_test_case, my_dependent_test_case)

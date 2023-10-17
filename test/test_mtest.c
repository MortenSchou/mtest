#include "mtest.h"

// We make a test case for each test macro in "mtest.h".
// This does not guarantee correctness, but it ensures that all code is covered.

TEST_CASE(message, {
    MESSAGE("They see me rolling.");
})
TEST_CASE(check_msg, {
    int a = 0, b = 1;
    CHECK(a < b, "This should be true.");
})
TEST_CASE(require_msg, {
    int a = 0, b = 1;
    REQUIRE(a < b, "This should be true.");
})
TEST_CASE(check_fail, {
    int a = 0, b = 1;
    if (a < b) CHECK_FAIL("Ohh, a was less than b.");  // Should fail
})
TEST_CASE(require_fail, {
    int a = 0, b = 1;
    if (a < b) REQUIRE_FAIL("Ohh, a was less than b.");  // Should fail
})

TEST_CASE(check_true, {
    int a = 0, b = 1;
    CHECK_TRUE(a < b);
})
TEST_CASE(check_false, {
    int a = 0, b = 1;
    CHECK_FALSE(a < b);  // Should fail
})
TEST_CASE(require_true, {
    int a = 0, b = 1;
    REQUIRE_TRUE(a < b);
})
TEST_CASE(require_false, {
    int a = 0, b = 1;
    REQUIRE_FALSE(a < b);  // Should fail
})

TEST_CASE(check_eq_int, {
    int a = 0, b = 1;
    CHECK_EQ_INT(a, b);  // Should fail
})
TEST_CASE(check_ne_int, {
    int a = 0, b = 1;
    CHECK_NE_INT(a, b);
})
TEST_CASE(check_lt_int, {
    int a = 0, b = 1;
    CHECK_LT_INT(a, b);
})
TEST_CASE(check_gt_int, {
    int a = 0, b = 1;
    CHECK_GT_INT(a, b);  // Should fail
})
TEST_CASE(check_le_int, {
    int a = 0, b = 1;
    CHECK_LE_INT(a, b);
})
TEST_CASE(check_ge_int, {
    int a = 0, b = 1;
    CHECK_GE_INT(a, b);  // Should fail
})

TEST_CASE(require_eq_int, {
    int a = 0, b = 1;
    REQUIRE_EQ_INT(a, b);  // Should fail
})
TEST_CASE(require_ne_int, {
    int a = 0, b = 1;
    REQUIRE_NE_INT(a, b);
})
TEST_CASE(require_lt_int, {
    int a = 0, b = 1;
    REQUIRE_LT_INT(a, b);
})
TEST_CASE(require_gt_int, {
    int a = 0, b = 1;
    REQUIRE_GT_INT(a, b);  // Should fail
})
TEST_CASE(require_le_int, {
    int a = 0, b = 1;
    REQUIRE_LE_INT(a, b);
})
TEST_CASE(require_ge_int, {
    int a = 0, b = 1;
    REQUIRE_GE_INT(a, b);  // Should fail
})

TEST_CASE(check_eq_double, {
    double a = M_PI, b = 3.141592;
    CHECK_EQ_DOUBLE(a, b, 0.000001);
})
TEST_CASE(check_ne_double, {
    double a = M_PI, b = 3.141592;
    CHECK_NE_DOUBLE(a, b, 0.000001);  // Should fail
})
TEST_CASE(require_eq_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_EQ_DOUBLE(a, b, 0.000001);
})
TEST_CASE(require_ne_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_NE_DOUBLE(a, b, 0.000001);  // Should fail
})

TEST_CASE(check_lt_double, {
    double a = M_PI, b = 3.141592;
    CHECK_LT_DOUBLE(a, b);  // Should fail
})
TEST_CASE(check_gt_double, {
    double a = M_PI, b = 3.141592;
    CHECK_GT_DOUBLE(a, b);
})
TEST_CASE(check_le_double, {
    double a = M_PI, b = 3.141592;
    CHECK_LE_DOUBLE(a, b);  // Should fail
})
TEST_CASE(check_ge_double, {
    double a = M_PI, b = 3.141592;
    CHECK_GE_DOUBLE(a, b);
})

TEST_CASE(require_lt_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_LT_DOUBLE(a, b);  // Should fail
})
TEST_CASE(require_gt_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_GT_DOUBLE(a, b);
})
TEST_CASE(require_le_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_LE_DOUBLE(a, b);  // Should fail
})
TEST_CASE(require_ge_double, {
    double a = M_PI, b = 3.141592;
    REQUIRE_GE_DOUBLE(a, b);
})

TEST_CASE(check_eq_char, {
    int a = 'A', b = 'B';
    CHECK_EQ_CHAR(a, b);  // Should fail
})
TEST_CASE(check_ne_char, {
    int a = 'A', b = 'B';
    CHECK_NE_CHAR(a, b);
})
TEST_CASE(require_eq_char, {
    int a = 'A', b = 'B';
    REQUIRE_EQ_CHAR(a, b);  // Should fail
})
TEST_CASE(require_ne_char, {
    int a = 'A', b = 'B';
    REQUIRE_NE_CHAR(a, b);
})

TEST_CASE(check_eq_string, {
    char a[] = "abc,def";
    char b1[8] = "abc";
    char b2[] = "def";
    strcat(b1, ",");
    strcat(b1, b2);
    CHECK_EQ_STRING(a, b1);
})
TEST_CASE(check_ne_string, {
    char a[] = "abc,def";
    char b1[8] = "abc";
    char b2[] = "def";
    strcat(b1, ",");
    strcat(b1, b2);
    CHECK_NE_STRING(a, b1);  // Should fail
})
TEST_CASE(require_eq_string, {
    char a[] = "abc,def";
    char b1[8] = "abc";
    char b2[] = "def";
    strcat(b1, ",");
    strcat(b1, b2);
    REQUIRE_EQ_STRING(a, b1);
})
TEST_CASE(require_ne_string, {
    char a[] = "abc,def";
    char b1[8] = "abc";
    char b2[] = "def";
    strcat(b1, ",");
    strcat(b1, b2);
    REQUIRE_NE_STRING(a, b1);  // Should fail
})

MAIN_RUN_TESTS(message, check_msg, require_msg, check_fail, require_fail,
               check_true, check_false, require_true, require_false,
               check_eq_int, check_ne_int, check_lt_int, check_gt_int, check_le_int, check_ge_int,
               require_eq_int, require_ne_int, require_lt_int, require_gt_int, require_le_int, require_ge_int,
               check_eq_double, check_ne_double, require_eq_double, require_ne_double,
               check_lt_double, check_gt_double, check_le_double, check_ge_double,
               require_lt_double, require_gt_double, require_le_double, require_ge_double,
               check_eq_char, check_ne_char, require_eq_char, require_ne_char,
               check_eq_string, check_ne_string, require_eq_string, require_ne_string)

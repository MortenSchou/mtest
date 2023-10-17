#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILENAME (strrchr("/"__FILE__, '/') + 1)

// Add file name and line number to messages.
#define MESSAGE_(format, ...)       printf(format" in %s:%d\n", __VA_ARGS__, FILENAME, __LINE__)
// The 'do {...} while(0)' trick allows having multiple statements in a macro and requires a terminating semicolon.
#define CHECK_(test, format, ...)   do { if (!(test)) { MESSAGE_(format, __VA_ARGS__); _mtest_result_ = 1; } } while (0)
#define REQUIRE_(test, format, ...) do { if (!(test)) { MESSAGE_(format, __VA_ARGS__); return 1;           } } while (0)

#define MESSAGE(message)        MESSAGE_("%s", message)
#define CHECK(test, message)    CHECK_(test, "%s", message)
#define REQUIRE(test, message)  REQUIRE_(test, "%s", message)
#define CHECK_FAIL(message)     CHECK_(0, "CHECK_FAIL: %s", message)
#define REQUIRE_FAIL(message)   REQUIRE_(0, "REQUIRE_FAIL: %s", message)
#define CHECK_TRUE(test)    CHECK_(test,      "CHECK_TRUE(%s) failed",    #test)
#define CHECK_FALSE(test)   CHECK_(!(test),   "CHECK_FALSE(%s) failed",   #test)
#define REQUIRE_TRUE(test)  REQUIRE_(test,    "REQUIRE_TRUE(%s) failed",  #test)
#define REQUIRE_FALSE(test) REQUIRE_(!(test), "REQUIRE_FALSE(%s) failed", #test)

// Comparison for integer values
#define CHECK_EQ_INT(expected, actual)   CHECK_((expected) == (actual),   "CHECK_EQ_INT(%s,%s) failed (%d != %d)",   #expected, #actual, expected, actual)
#define CHECK_NE_INT(expected, actual)   CHECK_((expected) != (actual),   "CHECK_NE_INT(%s,%s) failed (%d == %d)",   #expected, #actual, expected, actual)
#define CHECK_LT_INT(expected, actual)   CHECK_((expected) < (actual),    "CHECK_LT_INT(%s,%s) failed (%d >= %d)",   #expected, #actual, expected, actual)
#define CHECK_GT_INT(expected, actual)   CHECK_((expected) > (actual),    "CHECK_GT_INT(%s,%s) failed (%d <= %d)",   #expected, #actual, expected, actual)
#define CHECK_LE_INT(expected, actual)   CHECK_((expected) <= (actual),   "CHECK_LE_INT(%s,%s) failed (%d > %d)",    #expected, #actual, expected, actual)
#define CHECK_GE_INT(expected, actual)   CHECK_((expected) >= (actual),   "CHECK_GE_INT(%s,%s) failed (%d < %d)",    #expected, #actual, expected, actual)
#define REQUIRE_EQ_INT(expected, actual) REQUIRE_((expected) == (actual), "REQUIRE_EQ_INT(%s,%s) failed (%d != %d)", #expected, #actual, expected, actual)
#define REQUIRE_NE_INT(expected, actual) REQUIRE_((expected) != (actual), "REQUIRE_NE_INT(%s,%s) failed (%d == %d)", #expected, #actual, expected, actual)
#define REQUIRE_LT_INT(expected, actual) REQUIRE_((expected) < (actual),  "REQUIRE_LT_INT(%s,%s) failed (%d >= %d)", #expected, #actual, expected, actual)
#define REQUIRE_GT_INT(expected, actual) REQUIRE_((expected) > (actual),  "REQUIRE_GT_INT(%s,%s) failed (%d <= %d)", #expected, #actual, expected, actual)
#define REQUIRE_LE_INT(expected, actual) REQUIRE_((expected) <= (actual), "REQUIRE_LE_INT(%s,%s) failed (%d > %d)",  #expected, #actual, expected, actual)
#define REQUIRE_GE_INT(expected, actual) REQUIRE_((expected) >= (actual), "REQUIRE_GE_INT(%s,%s) failed (%d < %d)",  #expected, #actual, expected, actual)

// Comparison for floating point values. For (non-)equality we need to specify a tolerance 'delta'.
#define CHECK_EQ_DOUBLE(expected, actual, delta)    CHECK_(fabs((expected) - (actual)) <= (delta),   "CHECK_EQ_DOUBLE(%s,%s,%s) failed (%f != %f  +- %f)",   #expected, #actual, #delta, expected, actual, delta)
#define CHECK_NE_DOUBLE(expected, actual, delta)    CHECK_(fabs((expected) - (actual)) > (delta),    "CHECK_EQ_DOUBLE(%s,%s,%s) failed (%f == %f  +- %f)",   #expected, #actual, #delta, expected, actual, delta)
#define REQUIRE_EQ_DOUBLE(expected, actual, delta)  REQUIRE_(fabs((expected) - (actual)) <= (delta), "REQUIRE_EQ_DOUBLE(%s,%s,%s) failed (%f != %f  +- %f)", #expected, #actual, #delta, expected, actual, delta)
#define REQUIRE_NE_DOUBLE(expected, actual, delta)  REQUIRE_(fabs((expected) - (actual)) > (delta),  "REQUIRE_EQ_DOUBLE(%s,%s,%s) failed (%f == %f  +- %f)", #expected, #actual, #delta, expected, actual, delta)
#define CHECK_LT_DOUBLE(expected, actual)   CHECK_((expected) < (actual),    "CHECK_LT_DOUBLE(%s,%s) failed (%f >= %f)",   #expected, #actual, expected, actual)
#define CHECK_GT_DOUBLE(expected, actual)   CHECK_((expected) > (actual),    "CHECK_GT_DOUBLE(%s,%s) failed (%f <= %f)",   #expected, #actual, expected, actual)
#define CHECK_LE_DOUBLE(expected, actual)   CHECK_((expected) <= (actual),   "CHECK_LE_DOUBLE(%s,%s) failed (%f > %f)",    #expected, #actual, expected, actual)
#define CHECK_GE_DOUBLE(expected, actual)   CHECK_((expected) >= (actual),   "CHECK_GE_DOUBLE(%s,%s) failed (%f < %f)",    #expected, #actual, expected, actual)
#define REQUIRE_LT_DOUBLE(expected, actual) REQUIRE_((expected) < (actual),  "REQUIRE_LT_DOUBLE(%s,%s) failed (%f >= %f)", #expected, #actual, expected, actual)
#define REQUIRE_GT_DOUBLE(expected, actual) REQUIRE_((expected) > (actual),  "REQUIRE_GT_DOUBLE(%s,%s) failed (%f <= %f)", #expected, #actual, expected, actual)
#define REQUIRE_LE_DOUBLE(expected, actual) REQUIRE_((expected) <= (actual), "REQUIRE_LE_DOUBLE(%s,%s) failed (%f > %f)",  #expected, #actual, expected, actual)
#define REQUIRE_GE_DOUBLE(expected, actual) REQUIRE_((expected) >= (actual), "REQUIRE_GE_DOUBLE(%s,%s) failed (%f < %f)",  #expected, #actual, expected, actual)

// Comparison of chars
#define CHECK_EQ_CHAR(expected, actual)   CHECK_((expected) == (actual),   "CHECK_EQ_CHAR(%s,%s) failed ('%c' != '%c')",   #expected, #actual, expected, actual)
#define CHECK_NE_CHAR(expected, actual)   CHECK_((expected) != (actual),   "CHECK_NE_CHAR(%s,%s) failed ('%c' == '%c')",   #expected, #actual, expected, actual)
#define REQUIRE_EQ_CHAR(expected, actual) REQUIRE_((expected) == (actual), "REQUIRE_EQ_CHAR(%s,%s) failed ('%c' != '%c')", #expected, #actual, expected, actual)
#define REQUIRE_NE_CHAR(expected, actual) REQUIRE_((expected) != (actual), "REQUIRE_NE_CHAR(%s,%s) failed ('%c' == '%c')", #expected, #actual, expected, actual)

// Comparison of strings
#define CHECK_EQ_STRING(expected, actual)   CHECK_(!strcmp((expected), (actual)),   "CHECK_EQ_STRING(%s,%s) failed (\"%s\" != \"%s\")",   #expected, #actual, expected, actual)
#define CHECK_NE_STRING(expected, actual)   CHECK_(strcmp((expected), (actual)),    "CHECK_NE_STRING(%s,%s) failed (\"%s\" == \"%s\")",   #expected, #actual, expected, actual)
#define REQUIRE_EQ_STRING(expected, actual) REQUIRE_(!strcmp((expected), (actual)), "REQUIRE_EQ_STRING(%s,%s) failed (\"%s\" != \"%s\")", #expected, #actual, expected, actual)
#define REQUIRE_NE_STRING(expected, actual) REQUIRE_(strcmp((expected), (actual)),  "REQUIRE_NE_STRING(%s,%s) failed (\"%s\" == \"%s\")", #expected, #actual, expected, actual)

// A test case is implemented as a function that returns 0 if the test passes and 1 if it fails.
#define TEST_CASE(test_name, command...)                                                                                \
static int test_name(void) {                                                                                            \
    int _mtest_result_ = 0;                                                                                             \
    { command }                                                                                                         \
    return _mtest_result_;                                                                                              \
}

// Create an array of the function pointers passed as arguments to the macro.
// Run each function and count success and failures.
#define RUN_TESTS(...) do {                                                                                             \
    int success = 0, failed = 0;                                                                                        \
    int(*test_functions[])(void) = {__VA_ARGS__};                                                                       \
    for (int i = 0; i < sizeof(test_functions)/sizeof(int(*)(void)); ++i)                                               \
        test_functions[i]() ? failed++ : success++;                                                                     \
    printf("Tests run: %d. Succeeded: %d. Failed: %d", success+failed, success, failed);                                \
    if (failed) exit(EXIT_FAILURE);                                                                                     \
} while(0)

// Create a main function that takes as command line argument the name of the test case to run.
// We search through the test case names passed as arguments to the macro and call the corresponding function (through the function pointer).
// If the command line argument is --list-test-cases then the test case names are listed (semicolon-seperated). This is used for automatically registering the tests in CTest.
// If no (or too many) command line arguments are given, all test cases are run using RUN_TESTS.
#define MAIN_RUN_TESTS(...)                                                                                             \
int main (int argc, char *argv[]) {                                                                                     \
    if (argc == 2) {                                                                                                    \
        int list_test_cases = strcmp(argv[1], "--list-test-cases") == 0;                                                \
        int(*test_functions[])(void) = {__VA_ARGS__};                                                                   \
        char* names_static = #__VA_ARGS__;                                                                              \
        char* names = (char *)malloc(strlen(names_static)+1);                                                           \
        strcpy(names, names_static);                                                                                    \
        char* token = strtok(names, " ,");                                                                              \
        for (int i = 0; token != NULL && i < sizeof(test_functions)/sizeof(int(*)(void)); ++i) {                        \
            if (list_test_cases) {                                                                                      \
                printf("%s;", token);                                                                                   \
            } else if (strcmp(argv[1], token) == 0) {                                                                   \
                free(names);                                                                                            \
                return test_functions[i]();                                                                             \
            }                                                                                                           \
            token = strtok(NULL, " ,");                                                                                 \
        }                                                                                                               \
        free(names);                                                                                                    \
        if (list_test_cases) return 0;                                                                                  \
        printf("Test case not found: %s\n", argv[1]);                                                                   \
        return EXIT_FAILURE;                                                                                            \
    } else RUN_TESTS(__VA_ARGS__);                                                                                      \
    return 0;                                                                                                           \
}

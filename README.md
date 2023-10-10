# mtest
A minimalist C unit testing framework

## Installation (CMake)
Recommended installation using CMake's FetchContent:
```cmake
include(FetchContent)
FetchContent_Declare(mtest
    GIT_REPOSITORY https://github.com/MortenSchou/mtest.git
    GIT_TAG        main  # Or specify a specific branch, tag, or commit hash.
)
FetchContent_MakeAvailable(mtest)
```

Now the CMake library target `mtest` is available. For [example](example/CMakeLists.txt):
```cmake
add_executable(my_example_test my_test.c)
target_link_libraries(my_example_test mtest)

# Automatically discover test cases in my_example_test and add them to CTest.
discover_tests(my_example_test)
```

## Usage
Example test file [`my_test.c`](example/my_test.c):
```C
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
```

See [`mtest.h`](include/mtest.h) for more test macros.

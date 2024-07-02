 # mtest
A minimalist C unit testing framework
 - A single header-file with plain C and `#define` macros.
 - Plays well with CTest with a `discover_tests()` CMake function.

**mtest** is a simple, C-only unit testing framework inspired by [CuTest](https://cutest.sourceforge.net/) with some modern features inspired by [doctest](https://github.com/doctest/doctest).

For mature and feature-complete C/C++ testing frameworks, take a look at [Boost.Test](https://github.com/boostorg/test), [Catch2](https://github.com/catchorg/Catch2), [doctest](https://github.com/doctest/doctest), or [Google Test](https://github.com/google/googletest).

## Installation (CMake)
Recommended installation using CMake's FetchContent to download the latest release:
```cmake
include(FetchContent)
FetchContent_Declare(mtest
    URL https://github.com/MortenSchou/mtest/archive/refs/tags/v0.1.3.zip
    URL_HASH SHA256=176b32fa263848030a758a09e3a2dbeb892cef1826a344468351376d7afb8603
)
FetchContent_MakeAvailable(mtest)
```
or (alternatively) specify the Git repository and version to download:
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
  CHECK_EQ_INT(1, i);    // Test fails, but we continue running.
  REQUIRE_GT_INT(i, 0);  // This test is executed and succeeds, but the test case failed due to the previous line.
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

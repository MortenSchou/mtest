# mtest
A minimalist C unit testing framework
 - A single header-file with plain C and `#define` macros.
 - Plays well with CTest with a `discover_tests()` CMake function.

**mtest** is a simple, C-only unit testing framework inspired by [CuTest](https://cutest.sourceforge.net/) with some modern features inspired by [doctest](https://github.com/doctest/doctest).

For more mature and feature-complete C/C++ testing frameworks, take a look at [Boost.Test](https://github.com/boostorg/test), [Catch2](https://github.com/catchorg/Catch2), [doctest](https://github.com/doctest/doctest), or [Google Test](https://github.com/google/googletest).

**Table of Contents**
- [Usage](#usage)
- [Installation](#installation)
    - [Using CMake's `FetchContent` (Recommended)](#using-cmakes-fetchcontent-recommended)
    - [Using Git external submodules](#using-git-external-submodules)
    - [Using system-installed `mtest` (Advanced)](#using-system-installed-mtest-advanced)

## Usage

Ensure the CMake library target `mtest` is available, see the below [Installation section](#installation).

Once you have installed `mtest`, add something like the following code to your [CMakeLists.txt](example/CMakeLists.txt).
```cmake
# Put `FetchContent_MakeAvailable(mtest)`, `add_subdirectory(mtest)` or `find_package(mtest)` here.

add_executable(my_example_test my_test.c)
target_link_libraries(my_example_test mtest)

# Automatically discover test cases in my_example_test and add them to CTest.
discover_tests(my_example_test)
```

Where the example test file [`my_test.c`](example/my_test.c) looks something like the following:
```c
#include "mtest.h"

TEST_CASE(my_first_test_case, {
    int i = 42;
    CHECK_EQ_INT(42, i); // A simple check, similar to asking if `42 == i`.
})

TEST_CASE(my_other_test_case, {
    double i = 3.14;
    CHECK_EQ_DOUBLE(3.14, i, 0.01); // When comparing doubles, we need to specify a tolerance - here we choose 0.01
})

TEST_CASE(my_dependent_test_case, {
    int i = 0;
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
```

See [`mtest.h`](include/mtest.h) for all test macros.

## Installation

### Using CMake's `FetchContent` (Recommended)

Recommended installation using CMake's FetchContent to download the latest release:
```cmake
include(FetchContent)
FetchContent_Declare(mtest
    URL https://github.com/MortenSchou/mtest/archive/refs/tags/v0.2.0.zip
    URL_HASH SHA256=bec1e90fb00a5bc155de12ed5ed39ea5d1a1b6fcfb6c80cce5ad3e38e360248c
)
FetchContent_MakeAvailable(mtest)
```

Or alternatively you can specify the Git repository and version to download:

```cmake
include(FetchContent)
FetchContent_Declare(mtest
    GIT_REPOSITORY https://github.com/MortenSchou/mtest.git
    GIT_TAG        main  # Or specify a specific branch, tag, or commit hash.
)
FetchContent_MakeAvailable(mtest)
```

Updates can be done by changing the `URL` and `URL_HASH` in the first approach,
or by changing the `GIT_TAG` in the second approach.

### Using Git external submodules

Lets you manage mtest as a linked directory managed by git. This is the
more traditional way of linking dependencies.

Open a terminal and ensure you are inside your project's root
(where your main CMakeLists.txt file is located). Then type the following:
```bash
mkdir extern
git submodule add https://github.com/MortenSchou/mtest.git extern/mtest
git commit -m "add mtest dependency"
```

Now you can add the following to your CMakeLists.txt:
```cmake
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/mtest/CMakeLists.txt")
    message(FATAL_ERROR "The git submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Did you forget to run `git submodule init` after cloning?")
else()
    add_subdirectory(extern/mtest)
endif()
```

Updating mtest can be done with the `git submodule update` command, then
using git to commit the updated submodule directory.

### Using system-installed `mtest` (Advanced)

This is likely not what you want, and it is recommended you pick one of the
other approaches, as this does not ensure that anyone using your project will
have the same mtest library installed as you, or even that its installed.

However, this approach can be helpful if you are packaging your project, or have
otherwise installed mtest as part of your operating system.

If you do not have mtest already installed, you can run the following two
commands:
```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
sudo cmake --install build
```

Then you can add the following to your primary CMakeLists.txt:
```cmake
find_package(mtest REQUIRED)
```

To update when using `cmake --install`, you need to `git pull` this project,
and rerun the above cmake commands.

To uninstall the `cmake --install` approach, you need to go manually
delete each file as listed in the generated `cmake_build/install_manifest.txt`
file.

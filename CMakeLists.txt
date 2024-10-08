cmake_minimum_required(VERSION 3.14)
project(mtest VERSION 0.1.1 LANGUAGES C)

# Determine if mtest is built as a subproject (using add_subdirectory) or if it is the main project.
set(MTEST_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MTEST_IS_MAIN_PROJECT ON)
endif()

# Define mtest as an interface target (since it is header-only).
add_library(mtest INTERFACE)

# Define the include directory (containing "mtest.h").
target_include_directories(
    mtest INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Make sure that mtest will be linked together with the C math library.
target_link_libraries(mtest INTERFACE m)

# Include the CMake script to get the discover_tests function.
include(cmake/mtestDiscoverTests.cmake)

# Configure the example and tests if this is the main project (and not built as
# a subproject using for example add_subdirectory).
if(MTEST_IS_MAIN_PROJECT)
    # Add the needed install configuration to allow mtest to be installed as a
    # system wide library.
    include(cmake/mtestInstall.cmake)

    # Enable testing in CMake and include our /example and /test subdirectories
    # which hold the internal mtest tests to validate mtest functions as
    # expected.
    enable_testing()
    add_subdirectory(example)
    add_subdirectory(test)
endif()

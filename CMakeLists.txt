cmake_minimum_required(VERSION 3.14)
project(mtest VERSION 0.1.1 LANGUAGES C)

# Optional configuration of the CMakeLists.txt file. You can change these with
# the `-D` argument on the command line.
# Typically, you do not need to touch these unless you know you need to.
option(MTEST_INSTALL "install mtest as a system wide library" NO)

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

# If cmake is called with `-DMTEST_INSTALL=YES`, it will add the needed install
# configuration to allow mtest to be installed as a system wide library.
if (MTEST_INSTALL)
    include(cmake/mtestInstall.cmake)
endif()

# Include the CMake Helper to get the discover_tests function.
include(cmake/mtestCMakeHelpers.cmake)

# Configure the example test if this is the main project.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(example)
    add_subdirectory(test)
endif()

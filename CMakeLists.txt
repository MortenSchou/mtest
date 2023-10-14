cmake_minimum_required(VERSION 3.14)
project(mtest VERSION 0.1.0 LANGUAGES C)

# Determine if mtest is built as a subproject (using add_subdirectory) or if it is the main project.
set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

add_library(mtest INTERFACE)                        # Define mtest as an interface target (since it is header-only). 
target_include_directories(mtest INTERFACE include) # Here we define the include directory (containing "mtest.h"), and
target_link_libraries(mtest INTERFACE m)            # we make sure that projects using mtest will link with the C math library.

# Include the definition of the discover_tests function.
include(cmake/mtest.cmake)

# Configure the example test if this is the main project.
if(${MAIN_PROJECT})
    enable_testing()
    add_subdirectory(example)
    add_subdirectory(test)
endif()

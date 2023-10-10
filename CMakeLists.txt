cmake_minimum_required(VERSION 3.10)
project(mtest C)

include(cmake/mtest.cmake)

add_library(mtest INTERFACE)
target_include_directories(mtest INTERFACE include)

# discover_tests(<target>...) adds a post-build command to each <target> that calls CMake in script mode to generate the CTest script.

function(discover_tests)
    foreach (TARGET IN LISTS ARGN)
        set(ctest_tests_file "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_tests.cmake")
        add_custom_command(
            TARGET ${TARGET} POST_BUILD
            BYPRODUCTS "${ctest_tests_file}"
            COMMAND "${CMAKE_COMMAND}"
                -D "TEST_TARGET=${TARGET}"
                -D "TEST_EXECUTABLE=$<TARGET_FILE:${TARGET}>"
                -D "CTEST_FILE=${ctest_tests_file}"
                -P "${_MTEST_GENERATE_TEST_SCRIPT}"
            VERBATIM
        )
        set_property(DIRECTORY APPEND PROPERTY TEST_INCLUDE_FILES "${ctest_tests_file}")
    endforeach()
endfunction()

# Specify location of the mtestGenerateCTestFile.cmake script relative to current location (not relative to where discover_tests() is called).
if(DEFINED MTEST_IS_MAIN_PROJECT AND NOT MTEST_IS_MAIN_PROJECT)
    set(_MTEST_GENERATE_TEST_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/mtestGenerateCTestFile.cmake PARENT_SCOPE)
else ()
    set(_MTEST_GENERATE_TEST_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/mtestGenerateCTestFile.cmake)
endif ()

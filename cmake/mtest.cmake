# discover_tests(<target>) adds a post-build command to the given <target> that calls CMake in script mode to generate the CTest script.

function(discover_tests TARGET)
    set(ctest_tests_file "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_tests.cmake")
    add_custom_command(
        TARGET ${TARGET} POST_BUILD
        BYPRODUCTS "${ctest_tests_file}"
        COMMAND "${CMAKE_COMMAND}"
            -D "TEST_TARGET=${TARGET}"
            -D "TEST_EXECUTABLE=$<TARGET_FILE:${TARGET}>"
            -D "CTEST_FILE=${ctest_tests_file}"
            -P "${_MTEST_DISCOVER_TEST_SCRIPT}"
        VERBATIM
    )
    set_property(DIRECTORY APPEND PROPERTY TEST_INCLUDE_FILES "${ctest_tests_file}")
endfunction()

set(_MTEST_DISCOVER_TEST_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/mtest_add_tests.cmake PARENT_SCOPE)

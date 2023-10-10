set(script)  # Initialize script to empty string

# Run the test executable with command line argument "--list-test-cases". This should generate a ';'-seperated list of test-case names.
execute_process(
    COMMAND ${TEST_EXECUTABLE} --list-test-cases
    OUTPUT_VARIABLE output
    RESULT_VARIABLE result
)
if(${result} EQUAL 0)
    # If successful, add each test-case to the CTest script, where the test-case is given as the command line argument to the test executable.
    foreach(test_case ${output})
        set(script "${script}add_test(${TEST_TARGET}_${test_case} ${TEST_EXECUTABLE} ${test_case})\n")
    endforeach()
else ()
    # Otherwise, print a warning, and add a single test that calls the test executable without command line arguments. 
    message(WARNING
            "Error when running test executable '${TEST_EXECUTABLE}' to generate CTest script:\n"
            "  Result: ${result}\n"
            "  Output: ${output}\n"
    )
    set(script "${script}add_test(${TEST_TARGET} ${TEST_EXECUTABLE})\n")
endif()

# Write the CTest script to file
file(WRITE "${CTEST_FILE}" "${script}")

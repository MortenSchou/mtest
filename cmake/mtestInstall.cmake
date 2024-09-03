# This populates the following `CMAKE_INSTALL_*` variables to the
# operating system's defaults. In practice, these just contain a string with the
# same names as the variable. So INCLUDEDIR is "include", BINDIR is "bin",
# LIBDIR is "lib", and so on. But using the variables is good practice for
# cross platform support.
include(GNUInstallDirs)
# Install the mtest header file to the install directory under /include.
install(FILES include/mtest.h DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
# Export the mtest target as we made it in CMakeLists.txt. This will
# generate a new cmake file called mtestTargets.cmake which includes all changes
# that have been made to the mtest target.
# For example the definition of `target_link_libraries(mtest INTERFACE m)` in
# CMakeLists.txt will be put into this file for us automatically, and it only
# needs to be imported, which is done in the mtestConfig.cmake, the entry point
# for `find_package`.
install(TARGETS mtest EXPORT mtestTargets)
install(
    EXPORT mtestTargets
    FILE mtestTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mtest
)
# Generates a small cmake file that lets newer versions of the mtest library act
# as substitutes for an older version. If you write `find_package(mtest 0.1.1)`
# to a CMakeLists.txt but have newer mtest version 0.2.0 installed, this will
# let it act as compatible and get imported.
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "mtestConfigVersion.cmake"
    VERSION ${mtest_VERSION}
    COMPATIBILITY AnyNewerVersion
)
# Finally, install all the cmake files into the install directory under
# lib/cmake/mtest, as this is where `find_package(mtest)` would look for the
# package.
install(
    FILES
        cmake/mtestConfig.cmake
        cmake/mtestDiscoverTests.cmake
        cmake/mtestGenerateCTestFile.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/mtestConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/mtest"
)

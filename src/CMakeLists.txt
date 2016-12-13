find_package(glog REQUIRED)
find_package(gflags REQUIRED)

add_executable(hangman hello.cpp)
target_link_libraries (hangman glog gflags)

# Install
install (TARGETS hangman DESTINATION bin)
# install (FILES hangman.h DESTINATION include)

# Test
include(CTest)

add_test(HangmanRuns ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/hangman)

add_test (HangmanUsage ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/hangman)
set_tests_properties (HangmanUsage
  PROPERTIES
  PASS_REGULAR_EXPRESSION "^Hello World!\n$"
)

add_test (HangmanVersion ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/hangman --version)
set_tests_properties (HangmanVersion
  PROPERTIES
  PASS_REGULAR_EXPRESSION "^hangman version [0123456789]*\\.[0123456789]*"
)

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${Hangman_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Hangman_VERSION_MINOR}")
include (CPack)

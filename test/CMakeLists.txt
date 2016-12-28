find_package (gtest REQUIRED)
find_package (glog REQUIRED)

include_directories (${GTEST_INCLUDE_DIRS})

add_executable (util_tests
                $<TARGET_OBJECTS:utils>
                testRunner.cpp
                sortedTest.cpp
                statsTest.cpp
                nodeTest.cpp
                treeHelperTest.cpp)
target_compile_features (util_tests PRIVATE cxx_aggregate_default_initializers)
target_link_libraries (util_tests ${GTEST_BOTH_LIBRARIES} glog)

# Test
add_test (
    NAME util_tests
    COMMAND util_tests
)

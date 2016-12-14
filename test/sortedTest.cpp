#include "utils/sorted.h"

#include <gtest/gtest.h>

using namespace std;

TEST(sortedTest, sortedArray) {
    const vector<int> array = {0, 1, 2, 2, 10, 100};
    const bool isSorted = sorted(array);
    EXPECT_TRUE(isSorted);
}

TEST(sortedTest, notSortedArray) {
    const vector<int> array = {-10, 50, 39, 100};
    const bool isSorted = sorted(array);
    EXPECT_FALSE(isSorted);
}

TEST(sortedTest, oneItem) {
    const vector<int> array = {100};
    const bool isSorted = sorted(array);
    EXPECT_TRUE(isSorted);
}

TEST(sortedTest, empty) {
    const vector<int> array = {};
    const bool isSorted = sorted(array);
    EXPECT_TRUE(isSorted);
}

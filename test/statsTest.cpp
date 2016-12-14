#include "utils/stats.h"

#include <gtest/gtest.h>

using namespace std;

TEST(statsTest, canGetMode) {
    const vector<int> array = {100, 1, 2, 5, 10, 2};
    const int mode = getMode(array);
    EXPECT_EQ(2, mode);
}

TEST(statsTest, emptyMode) {
    const vector<int> array = {};
    ASSERT_THROW(getMode(array), std::length_error);
}

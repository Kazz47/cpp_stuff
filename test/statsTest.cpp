#include "utils/stats.h"

#include <gtest/gtest.h>

using namespace std;

TEST(statsModeTest, canGetMode) {
    const vector<int> array = {100, 1, 2, 5, 10, 2};
    const int mode = getMode(array);
    EXPECT_EQ(2, mode);
}

TEST(statsModeTest, emptyMode) {
    const vector<int> array = {};
    EXPECT_THROW(getMode(array), std::length_error);
}

TEST(statsMaxTest, canGetMax) {
    const vector<int> array = {60, 1, 2, 5, 10, 2};
    EXPECT_EQ(60, getMax(array));
}

TEST(statsMaxTest, getMaxThrowWhenEmpty) {
    const vector<int> array = {};
    EXPECT_THROW(getMax(array), std::length_error);
}

TEST(statsPercentileTest, throwWhenOutOfBounds) {
    const vector<int> array = {60, 1, 2, 5, 10, 2};
    EXPECT_THROW(getPercentile(array, 101U), std::invalid_argument);
}

TEST(statsPercentileTest, throwWhenEmpty) {
    const vector<int> array = {};
    EXPECT_THROW(getPercentile(array, 0U), std::length_error);
}

TEST(statsPercentileTest, canGet0Percentile) {
    const vector<int> array = {60, 1, 2, 5, 10, 2};
    const int val = getPercentile(array, 0U);
    EXPECT_EQ(1, val);
}

TEST(statsPercentileTest, canGet100Percentile) {
    const vector<int> array = {60, 1, 2, 5, 10, 2};
    const int val = getPercentile(array, 100U);
    EXPECT_EQ(60, val);
}

// We round up to the largest value rather than getting an average.
TEST(statsPercentileTest, canGet50Percentile) {
    const vector<int> array = {60, 1, 2, 5, 10, 2};
    const int val = getPercentile(array, 50U);
    EXPECT_EQ(5, val);
}

TEST(statsPercentileTest, canGet25Percentile) {
    const vector<int> array = {60, -15, 0, 7};
    const int val = getPercentile(array, 25U);
    EXPECT_EQ(0, val);
}

TEST(statsPercentileTest, canGet75Percentile) {
    const vector<int> array = {60, -15, 0, 7};
    const int val = getPercentile(array, 75U);
    EXPECT_EQ(7, val);
}

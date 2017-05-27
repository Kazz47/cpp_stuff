#include "utils/bits.h"

#include <gtest/gtest.h>
#include <bitset>

TEST(BitsTest, isLowSet_withOdd_isTrue) {
    EXPECT_TRUE(isLowSet(5));
}

TEST(BitsTest, isLowSet_withEven_isFalse) {
    EXPECT_FALSE(isLowSet(8));
}

TEST(BitsTest, isHighSet_withNegVal_isTrue) {
    EXPECT_TRUE(isHighSet(-1));
}

TEST(BitsTest, isHighSet_withZero_isFalse) {
    EXPECT_FALSE(isHighSet(0));
}

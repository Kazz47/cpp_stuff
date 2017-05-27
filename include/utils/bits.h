#pragma once

#include <limits>

inline bool isLowSet(int val) {
    return val & 1;
}

inline bool isHighSet(int val) {
    return val & (-std::numeric_limits<int>::max() - 1);
}

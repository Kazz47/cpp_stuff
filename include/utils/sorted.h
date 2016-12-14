#pragma once

#include <cassert>
#include <vector>

/**
 * Helper function for determining if a vector is sorted.
 */
template <typename T>
bool sorted(const std::vector<T>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        assert(i > 0);
        if (a[i-1] > a[i]) {
            return false;
        }
    }
    return true;
}

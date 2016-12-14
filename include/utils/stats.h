#pragma once

#include <vector>

/**
 * Helper function for determining the mode of a vector.
 * TODO: Should this return a vector?
 */
template <typename T>
T getMode(std::vector<T> a) {
    if (a.empty()) throw std::length_error("Can not find mode of an empty vector.");
    std::sort(a.begin(), a.end());

    auto it = a.cbegin();

    size_t bestCount = 1;
    T mode = *it;

    size_t count = 1;
    T current = *it;

    for (++it; it != a.cend(); ++it) {
        if (*it > current) {
            if (count > bestCount) {
                bestCount = count;
                mode = current;
            }
            count = 0;
            current = *it;
        }
        count++;
    }
    return mode;
}

#pragma once

#include <vector>
#include "utils/stringIt.h"

/**
 * Helper function for determining the mode of a vector.
 * TODO: Should this return a vector?
 */
template <typename T>
T getMode(std::vector<T> vec) {
    if (vec.empty()) throw std::length_error("Vector can not be empty.");
    std::sort(vec.begin(), vec.end());

    auto it = vec.cbegin();

    size_t bestCount = 1;
    T mode = *it;

    size_t count = 1;
    T current = *it;

    for (++it; it != vec.cend(); ++it) {
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

template <typename T>
T getMax(std::vector<T> vec) {
    if (vec.empty()) throw std::length_error("Vector can not be empty.");
    auto it = vec.begin();
    T max = *it;
    for (; it != vec.end(); ++it) {
        if (*it > max) max = *it;
    }
    return max;
}

template <typename T>
T getPercentile(std::vector<T> vec, unsigned int p) {
    if (vec.empty()) throw std::length_error("Vector can not be empty.");
    if (p > 100U) throw std::invalid_argument(StringIt()
        << "Percentile can not be greater than 100. Was " << p << ".");
    if (p == 100U) return getMax(vec);
    std::sort(vec.begin(), vec.end());
    const size_t index = p/100.0 * (vec.size()-1) + 0.5f;
    return vec[index];
}

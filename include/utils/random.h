#pragma once

#include <random>
#include <iterator>

template <typename Iter>
Iter randomElement(const Iter& begin, const Iter& end)
{
    using namespace std;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    Iter it(begin);
    uniform_int_distribution<> dis(0, distance(begin, end) - 1);
    advance(it, dis(gen));
    return it;
}

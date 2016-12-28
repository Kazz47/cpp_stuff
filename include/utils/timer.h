#pragma once

#include <chrono>
#include <functional>

class Timer
{
public:
    explicit Timer(const std::function<void(size_t)>& callback);

    ~Timer();

private:
    std::chrono::high_resolution_clock::time_point mStart;
    std::function<void(size_t)> mCallback;
};

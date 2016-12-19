#pragma once

#include <chrono>

class Timer
{
public:
    explicit Timer(const std::function<void(size_t)>& callback)
        : mStart(std::chrono::high_resolution_clock::now()),
          mCallback(callback) {}

    ~Timer()
    {
        using namespace std::chrono;

        const auto end = high_resolution_clock::now();
        mCallback(duration_cast<nanoseconds>(end - mStart).count());
    }

private:
    std::chrono::high_resolution_clock::time_point mStart;
    std::function<void(size_t)> mCallback;
};

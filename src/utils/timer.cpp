#include "utils/timer.h"

using namespace std;
using namespace std::chrono;

Timer::Timer(const function<void(size_t)>& callback)
    : mStart(high_resolution_clock::now()),
      mCallback(callback) {}

Timer::~Timer() {
    const auto end = high_resolution_clock::now();
    mCallback(duration_cast<microseconds>(end - mStart).count());
}

#include "utils/timerLog.h"
#include <glog/logging.h>

TimerLog::TimerLog(const std::string& message)
    : mMessage(message) {}

void TimerLog::operator()(size_t usec) const {
    LOG(INFO) << mMessage << " " << usec/1000 << " msec";
}

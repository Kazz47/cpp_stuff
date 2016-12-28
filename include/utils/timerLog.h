#pragma once

#include <glog/logging.h>
#include <string>

class TimerLog {
public:
    explicit TimerLog(const std::string& message);

    void operator()(size_t usec) const;

private:
    std::string mMessage;
};

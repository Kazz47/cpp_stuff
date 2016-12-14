#pragma once

#include <string>
#include <sstream>

/**
 * Helper class for creating a string.
 */
class StringIt {

public:
    template <typename T>
    StringIt& operator<<(const T& t) {
        mStream << t;
        return *this;
    }

    operator std::string() const {
        return mStream.str();
    }

private:
    std::ostringstream mStream;

};

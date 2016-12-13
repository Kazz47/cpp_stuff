#pragma once

#include <string>
#include <sstream>

class Stringify {
  private:
    std::ostringstream mStream;

  public:
    template<class T>
    Stringify& operator<<(const T& t)
    {
        mStream << t;
        return *this;
    }

    operator std::string() const
    {
        return mStream.str();
    }
};

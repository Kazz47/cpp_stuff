#pragma once

#include <string>
#include <sstream>

/**
 * Helper class for printing a progress bar.
 */
class ProgressBar {
public:
    ProgressBar();

    void setProgress(float progress);
    void print() const;

private:
    const static std::string BEGINNING;
    const static std::string END;
    const static std::string FILLER;
    const static size_t LENGTH;

    double mProgress;
};

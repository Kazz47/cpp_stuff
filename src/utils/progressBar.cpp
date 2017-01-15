#include "utils/progressBar.h"
#include <iostream>
#include <cmath>
#include <glog/logging.h>

using namespace std;

const std::string ProgressBar::BEGINNING = "[";
const std::string ProgressBar::END = "]";
const std::string ProgressBar::FILLER = "-";
const size_t ProgressBar::LENGTH = 50;

ProgressBar::ProgressBar()
    : mProgress(0)
{}

void ProgressBar::setProgress(float progress) {
    mProgress = progress;
}

void ProgressBar::print() const {
    cout << "\r" << BEGINNING;

    const int amountOfFiller = static_cast<int>(mProgress * LENGTH);
    for (size_t i = 0; i < amountOfFiller; i++) {
        cout << FILLER;
    }

    LOG_IF(ERROR, amountOfFiller > LENGTH) << "Bad size";
    const int remaningSpace = LENGTH - amountOfFiller;
    for (size_t i = 0; i < remaningSpace; i++) {
        cout << " ";
    }

    cout << END
        << round(mProgress * 100) << "%"
        << flush;
}

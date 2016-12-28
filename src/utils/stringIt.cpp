#include "utils/stringIt.h"

using namespace std;

StringIt::operator string() const {
    return mStream.str();
}

#include "hangman/lexicon.h"
#include "utils/timer.h"
#include "utils/timerLog.h"
#include <glog/logging.h>
#include <string>
#include <algorithm>

using namespace std;

Lexicon::Lexicon() {}
Lexicon::Lexicon(std::istream& inputStream) {
    TimerLog timerLog("Loaded lexicon from stream in");
    Timer timer(timerLog);
    string line;
    while (getline(inputStream, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        mWordSet.insert(line);
    }
}

bool Lexicon::hasSize(int length) const {
    for (const_iterator it = mWordSet.cbegin(); it != mWordSet.cend(); ++it) {
        if (it->length() == length) {
            return true;
        }
    }
    return false;
}

size_t Lexicon::size() const {
    return mWordSet.size();
}

void Lexicon::add(const std::string& val) {
    mWordSet.insert(val);
}

Lexicon::iterator Lexicon::erase(Lexicon::const_iterator it) {
    return mWordSet.erase(it);
}

ostream& operator<<(ostream& stream, const Lexicon& lex) {
    stream << "[";
    for (auto it = lex.cbegin(); it != lex.cend(); ++it) {
        stream << *it;
        if (next(it) != lex.cend()) stream << ", ";
    }
    stream << "]";
    return stream;
}

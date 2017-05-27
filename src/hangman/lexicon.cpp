#include "hangman/lexicon.h"
#include "utils/timer.h"
#include "utils/timerLog.h"
#include <glog/logging.h>
#include <string>
#include <algorithm>
#include <unordered_map>

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

float Lexicon::complexity() const {
    typedef unordered_map<char, size_t> CharMap;

    float complexity = 0.0;
    for (auto it = mWordSet.cbegin(); it != mWordSet.cend(); ++it) {
        CharMap charMap;
        for (auto cit = it->cbegin(); cit != it->cend(); ++cit) {
            pair<CharMap::iterator, bool> ret = charMap.insert(make_pair(*cit, 1));
            if (!ret.second) ret.first->second++;
        }
        complexity += static_cast<float>(charMap.size()) / it->size();
    }
    LOG(INFO) << "Lexicon has complexity " << complexity;
    return complexity;
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

#include "hangman/guesser.h"
#include "utils/random.h"
#include "utils/timer.h"
#include "utils/timerLog.h"
#include <glog/logging.h>
#include <unordered_map>
#include <map>

using namespace std;

typedef unordered_map<char, size_t> CharMap;
typedef multimap<size_t, char> FreqMap;

namespace {
    Lexicon getFilteredLexicon(const Lexicon& lex, const string& pattern) {
        Lexicon filtered;
        for (auto it = lex.cbegin(); it != lex.cend(); ++it) {
            bool patternMatch = true;
            if (pattern.size() != it->size()) continue; // Only check pattern for same size words.
            for (size_t i = 0; i < pattern.size(); ++i) {
                if (pattern.at(i) != '_'
                 && pattern.at(i) != it->at(i)) {
                     patternMatch = false;
                     break;
                }
            }
            if (patternMatch) filtered.add(*it);
        }
        return filtered;
    }

    CharMap buildCharMap(const Lexicon& lex, const set<char>& filter) {
        CharMap charMap;
        for (auto it = lex.cbegin(); it != lex.cend(); ++it) {
            for (auto cit = it->cbegin(); cit != it->cend(); ++cit) {
                if (filter.find(*cit) != filter.cend()) continue; // Filter out already guessed letters.
                pair<CharMap::iterator, bool> ret = charMap.insert(make_pair(*cit, 1));
                if (!ret.second) ret.first->second++;
            }
        }
        return charMap;
    }

    FreqMap buildFrequencyMap(const CharMap& map) {
        FreqMap freqMap;
        for (auto it = map.cbegin(); it != map.cend(); ++it) {
            freqMap.insert(make_pair(it->second, it->first));
        }
        return freqMap;
    }
}

Guesser::Guesser(const Lexicon& lex)
        : mLex(lex) {}

Guesser::Guesser(const Lexicon& lex, int wordLength)
        : mLex(lex) {
    for (auto it = mLex.begin(); it != mLex.end();) {
        if (it->size() != wordLength) it = mLex.erase(it);
        else ++it;
    }
}

char Guesser::guessLetter(const string& pattern, const set<char>& guessed) {
    const TimerLog callback("Made a guess in");
    const Timer timer(callback);

    for (auto it = guessed.cbegin(); it != guessed.cend(); ++it) {
        if (pattern.find(*it) == string::npos) this->removeLetter(*it);
    }
    CHECK(mLex.size() > 0);

    const Lexicon filteredLex = getFilteredLexicon(mLex, pattern);
    CHECK(filteredLex.size() > 0);

    const CharMap charMap = buildCharMap(filteredLex, guessed);
    CHECK(charMap.cbegin() != charMap.cend());

    const FreqMap freqMap = buildFrequencyMap(charMap);
    CHECK(freqMap.crbegin() != freqMap.crend());

    // Guess from FreqMap
    const pair<FreqMap::const_iterator, FreqMap::const_iterator> ret
        = freqMap.equal_range(freqMap.crbegin()->first); // Get most frequent letters.
    return randomElement(ret.first, ret.second)->second;
}

void Guesser::removeLetter(char letter) {
    for (auto it = mLex.begin(); it != mLex.end();) {
        if (it->find(letter) != string::npos) {
            it = mLex.erase(it);
        } else {
            ++it;
        }
    }
}

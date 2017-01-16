#include "hangman/cheatingManager.h"
#include "hangman/lexicon.h"
#include "utils/random.h"
#include "utils/timer.h"
#include "utils/timerLog.h"
#include <glog/logging.h>
#include <vector>
#include <map>

using namespace std;

CheatingManager::CheatingManager(const Lexicon& lex, int wordLength)
    : mLex(make_shared<Lexicon>(lex)),
      mWord(wordLength, '_') {
    for (auto it = mLex->begin(); it != mLex->end();) {
        if (it->size() != wordLength) it = mLex->erase(it);
        else ++it;
    }
}

std::string CheatingManager::getWord() const {
    return *(randomElement(mLex->cbegin(), mLex->cend()));
}

bool CheatingManager::guessLetter(char letter) {
    const TimerLog callback("Updated active lexicon in");
    const Timer timer(callback);

    // Create map of unique patterns and trim lexicon to most common pattern
    typedef vector<char> LetterPattern;
    typedef map<LetterPattern, shared_ptr<Lexicon>> PatternMap;

    PatternMap patternMap;

    for (auto it = mLex->cbegin(); it != mLex->cend(); ++it) {
        LetterPattern pattern;
        size_t foundPos = it->find(letter);
        while (foundPos != string::npos) {
            pattern.push_back(foundPos);
            foundPos = it->find(letter, foundPos+1);
        }
        pair<PatternMap::iterator, bool> ret;
        shared_ptr<Lexicon> newLex = make_shared<Lexicon>();
        newLex->add(*it);
        ret = patternMap.insert(make_pair(pattern, newLex));
        if (!ret.second) ret.first->second->add(*it);
    }

    auto it = patternMap.cbegin();
    vector<pair<LetterPattern, shared_ptr<Lexicon>>> lexPaternPairs;
    lexPaternPairs.push_back(make_pair(it->first, it->second));
    float largestLexComplexity = it->second->complexity();
    ++it;
    for (; it != patternMap.cend(); ++it) {
        const float complexity = it->second->complexity();
        if (complexity > largestLexComplexity) {
            lexPaternPairs.clear();
            lexPaternPairs.push_back(make_pair(it->first, it->second));
            largestLexComplexity = complexity;
        } else if (complexity == largestLexComplexity) {
            lexPaternPairs.push_back(make_pair(it->first, it->second));
        }
    }

    LetterPattern nextPattern;
    tie(nextPattern, mLex) = *randomElement(lexPaternPairs.cbegin(), lexPaternPairs.cend());

    DLOG(INFO) << "Lexicon: " << mLex;

    // Update word
    for (auto it = nextPattern.cbegin(); it != nextPattern.cend(); ++it) {
        mWord.replace(*it, 1, 1, letter);
    }

    return !nextPattern.empty();
}

bool CheatingManager::wordGuessed() const {
    return mWord.find('_') == string::npos;
}

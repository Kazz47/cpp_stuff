#include "hangman/cheatingManager.h"
#include "utils/random.h"
#include "utils/timer.h"
#include "utils/timerLog.h"
#include <glog/logging.h>
#include <vector>
#include <map>

using namespace std;

CheatingManager::CheatingManager(const Lexicon& lex, int wordLength)
    : mLex(lex),
      mWord(wordLength, '_') {
    for (auto it = mLex.begin(); it != mLex.end();) {
        if (it->size() != wordLength) it = mLex.erase(it);
        else ++it;
    }
}

std::string CheatingManager::getWord() const {
    return *(randomElement(mLex.cbegin(), mLex.cend()));
}

bool CheatingManager::guessLetter(char letter) {
    const TimerLog callback("Updated active lexicon in");
    const Timer timer(callback);

    // Create map of unique patterns and trim lexicon to most common pattern
    typedef vector<char> LetterPattern;
    map<LetterPattern, Lexicon> patternMap;

    for (auto it = mLex.cbegin(); it != mLex.cend(); ++it) {
        LetterPattern pattern;
        size_t foundPos = it->find(letter);
        while (foundPos != string::npos) {
            pattern.push_back(foundPos);
            foundPos = it->find(letter, foundPos+1);
        }
        pair<map<LetterPattern, Lexicon>::iterator, bool> ret;
        Lexicon newLex;
        newLex.add(*it);
        ret = patternMap.insert(make_pair(pattern, newLex));
        if (!ret.second) ret.first->second.add(*it);
    }

    auto it = patternMap.cbegin();
    LetterPattern mostCommonPattern = it->first;
    Lexicon largestLexicon = it->second;
    for (; it != patternMap.cend(); ++it) {
        if (it->second.size() > largestLexicon.size()) {
            mostCommonPattern = it->first;
            largestLexicon = it->second;
        }
    }

    mLex = largestLexicon;

    // Log lexicon
    for (auto it = mLex.cbegin(); it != mLex.cend(); ++it) {
        DLOG(INFO) << "Word: '" << *it << "'";
    }

    // Update word
    for (auto it = mostCommonPattern.cbegin(); it != mostCommonPattern.cend(); ++it) {
        mWord.replace(*it, 1, 1, letter);
    }

    return !mostCommonPattern.empty();
}

bool CheatingManager::wordGuessed() const {
    return mWord.find('_') == string::npos;
}

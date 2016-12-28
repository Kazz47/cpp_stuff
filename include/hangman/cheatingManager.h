#pragma once

#include "hangman/lexicon.h"

class CheatingManager {

public:
    explicit CheatingManager(const Lexicon& lex, int wordLength);

    std::string getWordState() const { return mWord; }
    std::string getWord() const;

    bool guessLetter(char letter);
    bool wordGuessed() const;

private:
    Lexicon mLex;
    std::string mWord;
};

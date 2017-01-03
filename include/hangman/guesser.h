#pragma once

#include "hangman/lexicon.h"

class Guesser {

public:
    explicit Guesser(const Lexicon& lex);

    char guessLetter(const std::string& pattern, const std::set<char>& guessed) const;

private:
    Lexicon mLex;
};

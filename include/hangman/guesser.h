#pragma once

#include "hangman/lexicon.h"
#include <set>

class Guesser {

public:
    explicit Guesser(const Lexicon& lex);
    explicit Guesser(const Lexicon& lex, int wordLength);

    char guessLetter(const std::string& pattern, const std::set<char>& guessed);

private:
    Lexicon mLex;

    void removeLetter(char letter);
};

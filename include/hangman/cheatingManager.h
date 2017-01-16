#pragma once

#include <string>
#include <memory>

class Lexicon;

class CheatingManager {

public:
    explicit CheatingManager(const Lexicon& lex, int wordLength);

    std::string getWordState() const { return mWord; }
    std::string getWord() const;

    bool guessLetter(char letter);
    bool wordGuessed() const;

private:
    std::shared_ptr<Lexicon> mLex;
    std::string mWord;
};

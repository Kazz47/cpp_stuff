#pragma once

#include <istream>
#include <string>
#include <set>

class Lexicon {

public:
    typedef std::set<std::string>::iterator iterator;
    typedef std::set<std::string>::const_iterator const_iterator;

    Lexicon();
    explicit Lexicon(std::istream& inputStream);

    bool hasSize(int length) const;

    size_t size() const;
    void add(const std::string& val);
    iterator erase(iterator);

    const_iterator cbegin() const { return mWordSet.cbegin(); }
    const_iterator cend() const { return mWordSet.cend(); }
    iterator begin() { return mWordSet.begin(); }
    iterator end() { return mWordSet.end(); }

private:
    std::set<std::string> mWordSet;
};

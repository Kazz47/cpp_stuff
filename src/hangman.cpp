#include "hangman/version.h"
#include "utils/stringIt.h"
#include "utils/timer.h"
#include "utils/random.h"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

DEFINE_string(word_file, "lexicon.txt", "filepath for the hangman dictionary");

namespace {
    class TimerLog {
    public:
        explicit TimerLog(const string& message)
            : mMessage(message) {}

        void operator()(size_t usec) const {
            LOG(INFO) << mMessage << " " << usec/1000 << " msec";
        }

    private:
        string mMessage;
    };
}

int main(int argc, char* argv[]) {
    gflags::SetVersionString(StringIt() << VERSION_MAJOR << "." << VERSION_MINOR);
    gflags::SetUsageMessage(StringIt() << "This program plays hangman with words from a dictionary!\n"
        << argv[0] << " --word_file <some filepath>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "VERSION: " << VERSION_MAJOR << "." << VERSION_MINOR;

    /**
     * Load the lexicon.
     */
    vector<string> lexicon;
    {
        const TimerLog callback(StringIt() << "Loaded lexicon from " << FLAGS_word_file << " in");
        const Timer timer(callback);
        ifstream lexiconFile(FLAGS_word_file);
        string line;
        while (getline(lexiconFile, line)) {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            lexicon.push_back(line);
        }
    }

    /**
     * Get game params from the user.
     */
    int wordLength = 0;
    bool haveWords = false;
    do {
        string input;
        cout << "What length word would you like? ";
        getline(cin, input);
        stringstream(input) >> wordLength;

        // Make sure there is at least one of that size
        for (auto it = lexicon.cbegin(); it != lexicon.cend(); ++it) {
            if (it->size() == wordLength) {
                haveWords = true;
                break;
            }
        }
        if (!haveWords) {
            cout << "There are no words in of length " << wordLength << "." << endl;
        }
    } while(!haveWords);

    int numTries = 0;
    cout << "How many tries would you like? ";
    string input;
    getline(cin, input);
    stringstream(input) >> numTries;

    LOG(INFO) << "Starting game with a length " << wordLength
        << " word and " << numTries << " tries.";

    // Trim words
    for (auto it = lexicon.begin(); it != lexicon.end();) {
        LOG_IF(INFO, it->size() == wordLength) << "Word: '" << *it << "'";
        if (it->size() != wordLength) it = lexicon.erase(it);
        else ++it;
    }

    string word(wordLength, '_');

    /**
     * Start game loop
     */
    bool playerWin = false;
    set<char> lettersGuessed;
    int missesRemaining = numTries;
    cout << endl << endl;
    while (missesRemaining > 0) {
        // Print game state.
        cout << "Misses remaining: " << missesRemaining << endl;
        cout << "Letters guessed: ";
        for (char letter : lettersGuessed) {
            cout << letter << ' ';
        }
        cout << endl;
        cout << "Current word: " << word << endl << endl;
        char letterGuess;
        pair<set<char>::iterator, bool> ret;
        do {
            cout << "Which letter would you like to guess? ";
            string guess;
            getline(cin, guess);
            letterGuess = guess[0];
            ret = lettersGuessed.insert(letterGuess);
            if (!ret.second) {
                cout << "You have already guessed '" << letterGuess << "'." << endl;
            }
        } while (!ret.second);
        LOG(INFO) << "Guessed letter: '" << letterGuess << "'";

        const TimerLog callback(StringIt() << "Updated active lexicon in");
        const Timer timer(callback);

        // Create map of unique patterns and trim lexicon to most common pattern
        typedef vector<size_t> LetterPattern;
        typedef vector<string> Lexicon;
        map<LetterPattern, Lexicon> patternMap;

        for (auto it = lexicon.cbegin(); it != lexicon.cend(); ++it) {
            LetterPattern pattern;
            size_t foundPos = it->find(letterGuess);
            while (foundPos != string::npos) {
                pattern.push_back(foundPos);
                foundPos = it->find(letterGuess, foundPos+1);
            }
            pair<map<LetterPattern, Lexicon>::iterator, bool> ret;
            ret = patternMap.insert(make_pair(pattern, Lexicon(1, *it)));
            if (!ret.second) ret.first->second.push_back(*it);
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
        lexicon = largestLexicon;

        // Log lexicon
        for (auto it = lexicon.cbegin(); it != lexicon.cend(); ++it) {
            DLOG(INFO) << "Word: '" << *it << "'";
        }

        // Update word
        for (auto it = mostCommonPattern.cbegin(); it != mostCommonPattern.cend(); ++it) {
            word.replace(*it, 1, 1, letterGuess);
        }

        // If the user didn't enter a matching letter, decrement the number
        // of remaning tries.
        if (mostCommonPattern.empty()) missesRemaining--;

        // Check for win
        if (word.find('_') == string::npos) {
            playerWin = true;
            break;
        }
    }

    if (playerWin) {
        cout << endl << "Congrats! You win this time!" << endl;
    } else {
        cout << endl << "Game over! You didn't win this time. :(" << endl;
        // Pick a random word from the remaining lexicon.
        word = *(randomElement(lexicon.cbegin(), lexicon.cend()));
    }
    cout << "The word was '" << word << "'." << endl;

    return 0;
}

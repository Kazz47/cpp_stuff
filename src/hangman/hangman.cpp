#include "hangman/version.h"
#include "hangman/cheatingManager.h"
#include "hangman/lexicon.h"
#include "utils/stringIt.h"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

DEFINE_string(word_file, "lexicon.txt", "filepath for the hangman dictionary");

namespace {
    Lexicon readLexicon(const string& filepath) {
        LOG(INFO) << "Loading lexicon from '" << FLAGS_word_file << "'.";
        ifstream lexiconFile(filepath);
        return Lexicon(lexiconFile);
    }
}

int main(int argc, char* argv[]) {
    gflags::SetVersionString(StringIt() << VERSION_MAJOR << "." << VERSION_MINOR);
    gflags::SetUsageMessage(StringIt() << "This program plays hangman with words from a dictionary!\n"
        << argv[0] << " --word_file <some filepath>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "VERSION: " << VERSION_MAJOR << "." << VERSION_MINOR;

    Lexicon lexicon = readLexicon(FLAGS_word_file);

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

    CheatingManager manager(lexicon, wordLength);

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
        cout << "Current word: " << manager.getWordState() << endl << endl;
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

        const bool foundLetter = manager.guessLetter(letterGuess);

        // If the user didn't enter a matching letter, decrement the number
        // of remaning tries.
        if (!foundLetter) missesRemaining--;

        // Check for win
        if (manager.wordGuessed()) {
            playerWin = true;
            break;
        }
    }

    if (playerWin) {
        cout << endl << "Congrats! You win this time!" << endl;
    } else {
        cout << endl << "Game over! You didn't win this time. :(" << endl;
    }
    cout << "The word was '" << manager.getWord() << "'." << endl;

    return 0;
}

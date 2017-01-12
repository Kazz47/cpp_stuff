#include "hangman/version.h"
#include "hangman/cheatingManager.h"
#include "hangman/lexicon.h"
#include "hangman/guesser.h"
#include "utils/stringIt.h"
#include "utils/progressBar.h"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

namespace {
    DEFINE_string(word_file, "words.txt", "filepath for the hangman dictionary");
    DEFINE_string(lex_file, "lexicon.txt", "filepath for the guesser dictionary");
    DEFINE_uint64(length, 0, "word legth to use");
    DEFINE_uint64(tries, 0, "number of tries the guesser has");
    DEFINE_uint64(iterations, 0, "number of iterations to run");

    Lexicon readLexicon(const string& filepath) {
        LOG(INFO) << "Loading words from '" << FLAGS_word_file << "'.";
        ifstream lexiconFile(filepath);
        return Lexicon(lexiconFile);
    }
}

int main(int argc, char* argv[]) {
    gflags::SetVersionString(StringIt() << VERSION_MAJOR << "." << VERSION_MINOR);
    gflags::SetUsageMessage(StringIt() << "This program benchmarks a guesser vs a word manager.\n"
        << argv[0] << " --word_file <some filepath> --lex_file <some filepath> --length <int> --tries <int> --iterations <int>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "VERSION: " << VERSION_MAJOR << "." << VERSION_MINOR;

    Lexicon words = readLexicon(FLAGS_word_file);

    const Guesser guesser(readLexicon(FLAGS_lex_file));

    /**
     * Get simulations params from the user.
     */
    const uint64_t wordLength = FLAGS_length;
    // Make sure there is at least one of that size
    bool haveWords = false;
    for (auto it = words.cbegin(); it != words.cend(); ++it) {
        if (it->size() == wordLength) {
            haveWords = true;
            break;
        }
    }
    if (!haveWords) {
        cout << "There are no words in of length " << wordLength << " in the words file." << endl;
        return 1;
    }

    const uint64_t numTries = FLAGS_tries;
    const uint64_t numIterations = FLAGS_iterations;

    LOG(INFO) << "Starting benchmark with word length " << wordLength
        << " and " << numTries << " tries for " << numIterations<< " iterations.";

    size_t numGuesserWins = 0;
    size_t numManagerWins = 0;
    ProgressBar pBar;
    for (size_t i = 0; i < numIterations; ++i) {
        pBar.setProgress(static_cast<float>(i) / numIterations);
        pBar.print();
        CheatingManager manager(words, wordLength);

        /**
         * Start game loop
         */
        bool guesserWin = false;
        set<char> lettersGuessed;
        int missesRemaining = numTries;
        while (missesRemaining > 0) {
            const char letterGuess = guesser.guessLetter(manager.getWordState(), lettersGuessed);
            lettersGuessed.insert(letterGuess);
            LOG(INFO) << "Guessed letter: '" << letterGuess << "'";

            const bool foundLetter = manager.guessLetter(letterGuess);

            // If the guesser didn't enter a matching letter, decrement the number
            // of remaning tries.
            if (!foundLetter) missesRemaining--;

            // Check for win
            if (manager.wordGuessed()) {
                guesserWin = true;
                break;
            }
        }

        if (guesserWin) {
            numGuesserWins++;
        } else {
            numManagerWins++;
        }
        LOG(INFO) << "The word was '" << manager.getWord() << "'.";
    }
    pBar.setProgress(1.0);
    pBar.print();

    cout << endl << endl;
    cout << "Total iterations: " << numIterations << endl;
    cout << "Guesser wins: " << numGuesserWins << endl;
    cout << "Manger wins: " << numManagerWins << endl;
    LOG_IF(ERROR, numGuesserWins + numManagerWins != numIterations)
        << "The number of guesser and manger wins does not total to the number of iterations.";

    return 0;
}

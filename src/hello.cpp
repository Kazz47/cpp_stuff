#include "hangman/version.h"
#include "hangman/utils.h"
#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

int main(int argc, char* argv[]) {
    gflags::SetVersionString(Stringify() << VERSION_MAJOR << "." << VERSION_MINOR);
    gflags::SetUsageMessage(Stringify() << "This program prints hello!\n"
        << argv[0] << " <some-param>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "VERSION: " << VERSION_MAJOR << "." << VERSION_MINOR;

    cout << "Hello World!" << endl;
    return 0;
}

#include "hangman/version.h"
#include "utils/stringIt.h"
#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace std;

int main(int argc, char* argv[]) {
    gflags::SetVersionString(StringIt() << VERSION_MAJOR << "." << VERSION_MINOR);
    gflags::SetUsageMessage(StringIt() << "This program prints hello!\n"
        << argv[0] << " <some-param>");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    LOG(INFO) << "VERSION: " << VERSION_MAJOR << "." << VERSION_MINOR;

    cout << "Hello World!" << endl;
    return 0;
}

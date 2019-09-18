#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

using std::cout;
using std::endl;

ABSL_FLAG(bool, enabled, true, "Enable the flag");

int main(int argc, char** argv){
    absl::ParseCommandLine(argc, argv);
    bool enabled = absl::GetFlag(FLAGS_enabled);
    if (enabled){
        cout << "Enabled" << endl;
    } else {
        cout << "Disabled" << endl;
    }
    return 0;
}


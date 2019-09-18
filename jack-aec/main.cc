#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"
#include "jack/jack.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

ABSL_FLAG(string, clientName, "jack-aec", "Client name to use when connecting to JACK server.");
ABSL_FLAG(string, serverName, "", "Server name to connect to. Leave empty for default server.");

int main(int argc, char** argv){
    absl::SetProgramUsageMessage("A JACK application for acoustic echo cancellation.");
    absl::ParseCommandLine(argc, argv);

    const char* clientName = absl::GetFlag(FLAGS_clientName).c_str();
    const char* serverName = NULL;
    const string serverNameString = absl::GetFlag(FLAGS_serverName);
    if (!serverNameString.empty()) {
        serverName = serverNameString.c_str();
    }
    //jack_options_t options = JackNullOption;

    cout << clientName << endl;
    if (serverName) {
        cout << serverName << endl;
    }

    return 0;
}


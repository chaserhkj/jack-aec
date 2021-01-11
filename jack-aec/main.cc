#include <iostream>
#include <string>
#include <signal.h>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/flags/usage.h"

#include "flags.h"
#include "jack_mgr.h"

using std::cerr;

void int_term_handler(int sig) {
    cerr << "Handled sig " << sig << "\n";
}

int main(int argc, char** argv){
    absl::SetProgramUsageMessage("A JACK application for acoustic echo cancellation.");
    absl::ParseCommandLine(argc, argv);

    JackAEC::JackManager mgr;
    
    if (mgr.setup() != 0) {
        cerr << "JackMgr setup failed\n";
    }

    if (mgr.run() != 0) {
        cerr << "JackMgr run failed\n";
    }

    signal(SIGTERM, int_term_handler);
    signal(SIGINT, int_term_handler);

    pause();

    cerr << "Exiting gracefully\n";
    return 0;
}


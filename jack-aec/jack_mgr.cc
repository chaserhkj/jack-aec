#include "jack_mgr.h"

#include <iostream>

#include "flags.h"

#include "absl/flags/flag.h"
#include "absl/strings/str_format.h"
#include "jack/jack.h"

namespace JackAEC
{
using absl::StrFormat;
using std::cerr;

JackManager::JackManager( bool loadFromFlags ) {
    if (loadFromFlags) {
        this->clientName = absl::GetFlag(FLAGS_clientName);
        this->channels = absl::GetFlag(FLAGS_channels);
    }
}

JackManager::~JackManager() {
    if (this->client != nullptr) {
        jack_client_close(this->client);
    }
}

int JackManager::openClient() {
    this->client = jack_client_open(this->clientName.c_str(), JackNullOption, NULL);
    if (this->client == 0) {
        return 1;
    } else {
        return 0;
    }
}

int JackManager::setup() {
    int rtn;
    if ((rtn = this->openClient()) != 0) {
        return rtn;
    }
    if ((rtn = this->setupProcess()) != 0) {
        return rtn;
    }
    this->setupShutdown();
    return 0;
}

int JackManager::activateClient() {
    return jack_activate(this->client);
}

int JackManager::openPorts() {
    for (size_t i = 0; i < this->channels ; i++) {
        jack_port_t* port;
        if ((port = jack_port_register(this->client,
                StrFormat("input%d", i + 1).c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                JackPortIsInput, 0)) == 0) {
            return 1;
        }
        this->input_ports.push_back(port);
    }

    for (size_t i = 0; i < this->channels ; i++) {
        jack_port_t* port;
        if ((port = jack_port_register(this->client,
                StrFormat("sample%d", i + 1).c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                JackPortIsInput, 0)) == 0) {
            return 1;
        }
        this->sample_ports.push_back(port);
    }

    for (size_t i = 0; i < this->channels ; i++) {
        jack_port_t* port;
        if ((port = jack_port_register(this->client,
                StrFormat("output%d", i + 1).c_str(),
                JACK_DEFAULT_AUDIO_TYPE,
                JackPortIsOutput, 0)) == 0) {
            return 1;
        }
        this->output_ports.push_back(port);
    }
    return 0;
}

int JackManager::run() {
    int rtn;
    if ((rtn = this->activateClient()) != 0) {
        return rtn;
    }
    if ((rtn = this->openPorts()) != 0) {
        return rtn;
    }
    return 0;
}

int JackManager::process(jack_nframes_t nframes) {
    cerr << "Received " << nframes << " Frames\n";
    return 0;
}

void JackManager::shutdown() {
    cerr << "JACK Shutdown\n";
    abort();
}

namespace 
{

int process_proxy(jack_nframes_t nframes, void* arg) {
    JackManager* mgr = static_cast<JackManager*>(arg);
    return mgr->process(nframes);
}

void shutdown_proxy(void* arg) {
    JackManager* mgr = static_cast<JackManager*>(arg);
    mgr->shutdown();
}

} // namespace 

int JackManager::setupProcess() {
    if (this->client == nullptr) {
        return 1;
    }
    return jack_set_process_callback(this->client, process_proxy, this);
}

void JackManager::setupShutdown(){
    if (this->client == nullptr) {
        return;
    }
    return jack_on_shutdown(this->client, shutdown_proxy, this);
}


} // namespace name

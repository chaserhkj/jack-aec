#if !defined(JACK_MGR_H)
#define JACK_MGR_H
#include <string>
#include <vector>

#include "jack/jack.h"

namespace JackAEC
{
using std::string;
using std::vector;

class JackManager {
    jack_client_t* client = nullptr;
    string clientName = "jack-aec";
    uint channels = 2;
    vector<jack_port_t*> input_ports;
    vector<jack_port_t*> sample_ports;
    vector<jack_port_t*> output_ports;

protected:
    // setup() procedures
    int openClient();
    int setupProcess();
    void setupShutdown();

    // run() procedures
    int activateClient();
    int openPorts();

public:
    JackManager( bool loadFromFlags = true );
    ~JackManager();

    int setup();
    int run();

    int process(jack_nframes_t nframes);
    void shutdown();

};

} // namespace JackAEC
#endif // JACK_MGR_H

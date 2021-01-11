#include "flags.h"

#include "absl/flags/flag.h"

ABSL_FLAG(std::string, clientName, "jack-aec", "Client name to use when connecting to JACK server.");
ABSL_FLAG(uint, channels, 2, "Number of channels");
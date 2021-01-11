#if !defined(FLAGS_H)
#define FLAGS_H

#include <string>

#include "absl/flags/declare.h"

ABSL_DECLARE_FLAG(std::string, clientName);
ABSL_DECLARE_FLAG(uint, channels);

#endif // FLAGS_H
#pragma once

#include <string>
#include "extern/cdmapi.h"
using namespace cdm;

std::string session_type_str(SessionType st);
std::string message_type_str(MessageType mt);
std::string hdcp_version_str(HdcpVersion hv);

std::string with_str(bool c);

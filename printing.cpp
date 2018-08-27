#include "printing.h"

std::string session_type_str(SessionType st) {
    switch(st) {
        case kTemporary:
            return "Temporary";
        case kPersistentLicense:
            return "Persistent License";
        case kPersistentKeyRelease:
            return "Persistent Key Release";
        default:
            return "Invalid";
    }
}


std::string message_type_str(MessageType mt) {
    switch(mt) {
        case kLicenseRequest:
            return "License Request";
        case kLicenseRenewal:
            return "License Renewal";
        case kLicenseRelease:
            return "License Release";
        default:
            return "Invalid";
    }
}


std::string hdcp_version_str(HdcpVersion hv) {
    switch(hv) {
        case kHdcpVersionNone:
            return "None";
        case kHdcpVersion1_0:
            return "1.0";
        case kHdcpVersion1_1:
            return "1.1";
        case kHdcpVersion1_2:
            return "1.2";
        case kHdcpVersion1_3:
            return "1.3";
        case kHdcpVersion1_4:
            return "1.4";
        case kHdcpVersion2_0:
            return "2.0";
        case kHdcpVersion2_1:
            return "2.1";
        case kHdcpVersion2_2:
            return "2.2";
        default:
            return "Invalid";
    }
}

std::string with_str(bool c) {
    return c ? "with" : "without";
}

void dump_memory(void *ptr, uint32_t len) {
    auto bytes = (uint8_t*)ptr;
    for(uint32_t i = 0; i < len; i++) {
        fprintf(stderr, "%02x", bytes[i]);
    }
    fprintf(stderr, "\n");
}
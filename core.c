#include "core.h"

#include <stdio.h>
#include <dlfcn.h>

// Exported functions

char *GetCdmVersion() {
    if(!widevine) load_widevine();

    GetCdmVersion_t orig_GetCdmVersion = (GetCdmVersion_t) dlsym(widevine, "GetCdmVersion");
    char *version = orig_GetCdmVersion();
    printf("CDM Version '%s'", version);
    return version;
}
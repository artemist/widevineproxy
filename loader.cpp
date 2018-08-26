#include "loader.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int load_widevine(void) {
    char *widevine_path = getenv("WIDEVINE_PATH");
    if(widevine_path == NULL) {
        fprintf(stderr, "No Widevine CDM found, please set WIDEVINE_PATH\n");
        exit(1);
    }
    widevine = dlopen(widevine_path, RTLD_NOW | RTLD_LOCAL);

    if(widevine) {
        fprintf(stderr, "Loaded Widevine CDM\n");
        return 1;
    } else {
        fprintf(stderr, "Failed to load Widevine CDM\n");
        exit(1);
    }
}
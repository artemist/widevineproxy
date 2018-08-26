#pragma once
#include "extern/cdmapi.h"
#include "base_interface.h"

// Welp, there isn't a good way not to have global variables
extern CdmHostFunction_t orig_host_function;
extern void *widevine;
int load_widevine(void);

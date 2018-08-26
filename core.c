#include "core.h"

#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdint.h>
// Exported functions

void InitializeCdmModule_4(void) {
    if(!widevine) load_widevine();

    InitializeCdmModule_t orig_InitializeCdmModule = (InitializeCdmModule_t) dlsym(widevine, "InitializeCdmModule_4");
    fprintf(stderr, "Initializing Widevine CDM\n");
    orig_InitializeCdmModule();
}

void DeinitializeCdmModule(void) {
    if(!widevine) load_widevine();

    DeinitializeCdmModule_t orig_DeinitializeCdmModule = (DeinitializeCdmModule_t) dlsym(widevine, "DeinitializeCdmModule");
    fprintf(stderr, "Deinitializing Widevine CDM");
    orig_DeinitializeCdmModule();
}

char *GetCdmVersion() {
    if(!widevine) load_widevine();

    GetCdmVersion_t orig_GetCdmVersion = (GetCdmVersion_t) dlsym(widevine, "GetCdmVersion");
    char *version = orig_GetCdmVersion();
    printf("CDM Version '%s'", version);
    return version;
}

bool VerifyCdmHost_0(struct HostFile* host_files, uint32_t num_files) {
    if(!widevine) load_widevine();

    VerifyCdmHost_t orig_VerifyCdmHost = (VerifyCdmHost_t) dlsym(widevine, "VerifyCdmHost_0");

    for(uint32_t i = 0; i < num_files; i++) {
        fprintf(stderr, "Checking host file with name '%s', fd '%d', and  sig_fd '%d'\n",
                host_files[i].file_path, host_files[i].fd, host_files[i].sig_fd);
    }

    bool verification_result = orig_VerifyCdmHost(host_files, num_files);
    if(verification_result) fprintf(stderr, "Verification succeeded\n");
    else fprintf(stderr, "Verification failed\n");

    return true;
}

void *CreateCdmInstance(int interface_version, const char *key_system, uint32_t key_system_len,
                        CdmHostFunction host_function, void *extra_data) {
    if(!widevine) load_widevine();
    fprintf(stderr, "Creating Widevine CDM Interface with key system '");
    for(uint32_t i = 0; i < key_system_len; i++) fputc(key_system[i], stderr);
    fprintf(stderr, "'\n");

    fprintf(stderr, "TODO: Not intercepting host function");


    CreateCdmInstance_t orig_CreateCdmInstance = (CreateCdmInstance_t) dlsym(widevine, "CreateCdmInstance");
    return orig_CreateCdmInstance(interface_version, key_system, key_system_len, host_function, extra_data);

}
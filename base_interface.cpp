#include "base_interface.h"
#include "loader.h"
#include "extern/cdmapi.h"
#include "cdmproxy.h"

#include <cstdio>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdint.h>
// Exported functions

extern "C" EXPORT void InitializeCdmModule_4(void) {
    if(!widevine) load_widevine();

    auto orig_InitializeCdmModule = (InitializeCdmModule_t) dlsym(widevine, "InitializeCdmModule_4");
    fprintf(stderr, "Initializing Widevine CDM\n");
    orig_InitializeCdmModule();
}

extern "C" EXPORT void DeinitializeCdmModule(void) {
    if(!widevine) load_widevine();

    auto orig_DeinitializeCdmModule = (DeinitializeCdmModule_t) dlsym(widevine, "DeinitializeCdmModule");
    fprintf(stderr, "Deinitializing Widevine CDM");
    orig_DeinitializeCdmModule();
}

extern "C" EXPORT char *GetCdmVersion() {
    if(!widevine) load_widevine();

    auto orig_GetCdmVersion = (GetCdmVersion_t) dlsym(widevine, "GetCdmVersion");
    char *version = orig_GetCdmVersion();
    printf("CDM Version '%s'", version);
    return version;
}

extern "C" EXPORT bool VerifyCdmHost_0(struct HostFile* host_files, uint32_t num_files) {
    if(!widevine) load_widevine();

    auto orig_VerifyCdmHost = (VerifyCdmHost_t) dlsym(widevine, "VerifyCdmHost_0");

    for(uint32_t i = 0; i < num_files; i++) {
        fprintf(stderr, "Checking host file with name '%s', fd '%d', and  sig_fd '%d'\n",
                host_files[i].file_path, host_files[i].fd, host_files[i].sig_fd);
    }

    bool verification_result = orig_VerifyCdmHost(host_files, num_files);
    if(verification_result) fprintf(stderr, "Verification succeeded\n");
    else fprintf(stderr, "Verification failed\n");

    return true;
}

extern "C" EXPORT void *HostFunction(int host_version, void* user_data) {
    fprintf(stderr, "Called host function with version %d and user data at %p\n", host_version, user_data);
    return orig_host_function(host_version, user_data);
}


extern "C" EXPORT void *CreateCdmInstance(int interface_version, const char *key_system, uint32_t key_system_len,
                        CdmHostFunction_t host_function, void *extra_data) {
    if(!widevine) load_widevine();
    fprintf(stderr, "Creating Widevine CDM Interface with version %d and key system '", interface_version);
    for(uint32_t i = 0; i < key_system_len; i++) fputc(key_system[i], stderr);
    fprintf(stderr, "'\n");

    orig_host_function = host_function;


    auto orig_CreateCdmInstance = (CreateCdmInstance_t) dlsym(widevine, "CreateCdmInstance");
    void *instance =  orig_CreateCdmInstance(interface_version, key_system, key_system_len, HostFunction, extra_data);

    if(instance == nullptr) return nullptr;

    auto proxy = new CDMProxy_8(static_cast<cdm::ContentDecryptionModule_8*>(instance));
    auto interface = (cdm::ContentDecryptionModule_8*)proxy;
    return reinterpret_cast<void*>(interface);

}


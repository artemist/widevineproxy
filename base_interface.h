#pragma once
#include "extern/cdmapi.h"
#include <stdbool.h>
#include <stdint.h>

struct HostFile {
    const char *file_path;
    int fd;
    int sig_fd;
};

typedef void* (*CdmHostFunction_t)(int, void*);

typedef void (*InitializeCdmModule_t)(void);
typedef void (*DeinitializeCdmModule_t)(void);
typedef char* (*GetCdmVersion_t)(void);
typedef bool (*VerifyCdmHost_t)(struct HostFile*, uint32_t);
typedef void* (*CreateCdmInstance_t)(int, const char*, uint32_t, CdmHostFunction_t, void *);

extern "C" EXPORT void InitializeCdmModule_4(void);
extern "C" EXPORT void DeinitializeCdmModule(void);
extern "C" EXPORT char *GetCdmVersion(void);
extern "C" EXPORT bool VerifyCdmHost_0(struct HostFile* host_files, uint32_t num_files);
extern "C" EXPORT void *CreateCdmInstance(int interface_version, const char *key_system, uint32_t key_system_len,
        CdmHostFunction_t host_function, void *extra_data);

extern "C" EXPORT void* HostFunction(int host_version, void* user_data);
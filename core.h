#pragma once
#include <stdbool.h>
#include <stdint.h>

void *widevine;

struct HostFile {
    const char *file_path;
    int fd;
    int sig_fd;
};

typedef void* (*CdmHostFunction)(int, void*);

typedef void (*InitializeCdmModule_t)(void);
typedef void (*DeinitializeCdmModule_t)(void);
typedef char* (*GetCdmVersion_t)(void);
typedef bool (*VerifyCdmHost_t)(struct HostFile*, uint32_t);
typedef void* (*CreateCdmInstance_t)(int, const char*, uint32_t, CdmHostFunction, void *);

int load_widevine(void);

void InitializeCdmModule_4(void);
void DeinitializeCdmModule(void);
char *GetCdmVersion(void);
bool VerifyCdmHost_0(struct HostFile* host_files, uint32_t num_files);
void *CreateCdmInstance(int interface_version, const char *key_system, uint32_t key_system_len,
        CdmHostFunction host_function, void *extra_data);
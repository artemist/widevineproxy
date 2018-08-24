#pragma once

void *widevine;

typedef char* (*GetCdmVersion_t)(void);


int load_widevine(void);
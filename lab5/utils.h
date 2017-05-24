#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include.h"

// A somewhat reasonable timeout for a long process
#define PROCESS_TIMEOUT 360000

BOOL CreatePipedProcess(char* cmd, PROCESS_INFORMATION* proc_info, STARTUPINFO* start_info);
BOOL CleanUpProcess(PROCESS_INFORMATION* proc_info);

#endif // __UTILS_H__
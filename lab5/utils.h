// Kainoa Seto
// Source-Filter-Sink 
// Contains utliites for the main program to execute processes
// lab5/utils.h

#ifndef __UTILS_H__
#define __UTILS_H__

#include "../include.h"

// A somewhat reasonable timeout for a long process
#define PROCESS_TIMEOUT 360000

// Creates a Piped Process based on a command, proc_info and startup_info passed to it
BOOL CreatePipedProcess(char* cmd, PROCESS_INFORMATION* proc_info, STARTUPINFO* start_info);

// Cleans up a process given its Process information by waiting, closing handles and getting
// and exit code.
BOOL CleanUpProcess(PROCESS_INFORMATION* proc_info);

#endif // __UTILS_H__
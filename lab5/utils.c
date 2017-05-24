// Kainoa Seto
// Source-Filter-Sink 
// Utilities to help with process management
// lab5/utils.c

#include "utils.h"

BOOL CreatePipedProcess(char* cmd, PROCESS_INFORMATION* proc_info, STARTUPINFO* start_info)
{
	// Prepare our CreateProcess arguments
	DWORD					proc_flags = 0;
	BOOL					is_created;

	is_created = CreateProcess(
		NULL,			// lpApplicationName
		cmd,			// lpCommandLine
		NULL,			// lpProcessAttributes
		NULL,			// lpThreadAttributes
		TRUE,			// bInheritHandles
		proc_flags,		// dwCreationFlags
		NULL,			// lpEnvironment
		NULL,			// lpCurrentDirectory
		start_info,		// lpStartupInfo
		proc_info		// lpProcessInformation
		);

	// Failed to create so return the failed flag
	if (!is_created)
		return FALSE;

	return TRUE;
}


BOOL CleanUpProcess(PROCESS_INFORMATION* proc_info)
{
	DWORD		exit_status, wait_status;

	// Waits for process to complete or until the timeout completes
	wait_status = WaitForSingleObject(proc_info->hProcess, PROCESS_TIMEOUT);

	if (wait_status == WAIT_FAILED)
		fprintf(stderr, "Failed waiting for cmd to process\n");

	// Get the process' exit code
	GetExitCodeProcess(proc_info->hProcess, &exit_status);

	// Cleanup after our process and its thread
	CloseHandle(proc_info->hProcess);
	CloseHandle(proc_info->hThread);

	return (int)exit_status;
}
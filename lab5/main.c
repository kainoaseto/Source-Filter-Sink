// Kainoa Seto
// Source-Filter-Sink 
// This demonstrates anonymous pipes in the win32 api while executing 3 seperate processes
// connected by two of the anonymous pipes to filter data between processes by stdout->stdin
// Lab5/main.c
#include "utils.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Error could not find both arguments.\n Usage: lab5 source_file_path destination_file_path\n");
		return 1;
	}

	// Process information and startup info
	PROCESS_INFORMATION source_proc_info;
	PROCESS_INFORMATION filter_proc_info;
	PROCESS_INFORMATION sink_proc_info;

	STARTUPINFO source_startup_info;
	STARTUPINFO filter_startup_info;
	STARTUPINFO sink_startup_info;
	
	// First pipe handles for source | filter
	HANDLE source_stdout;
	HANDLE filter_stdin;

	// Second pipe handles for filter | sink
	HANDLE filter_stdout;
	HANDLE sink_stdin;

	// Pipe security attributes
	SECURITY_ATTRIBUTES pipe_sec_attr;

	// Setup the security attributes so the pipe hanldes are passed between processes
	pipe_sec_attr.nLength				= sizeof(SECURITY_ATTRIBUTES);
	pipe_sec_attr.bInheritHandle		= TRUE;
	pipe_sec_attr.lpSecurityDescriptor	= NULL;

	// Create the pipe between the source and the filter programs
	if (!CreatePipe(&source_stdout, &filter_stdin, &pipe_sec_attr, 0))
	{
		fprintf(stderr, "Failed to create source | filter pipe\n");
		return 2;
	}

	// Create the pipe between the filter and the sink program
	if (!CreatePipe(&filter_stdout, &sink_stdin, &pipe_sec_attr, 0))
	{
		fprintf(stderr, "Failed to create filter | sink pipe\n");
		return 3;
	}

	// Setup the startup info with current process information
	GetStartupInfo(&source_startup_info);
	source_startup_info.cb			= sizeof(STARTUPINFO);
	source_startup_info.hStdError	= GetStdHandle(STD_ERROR_HANDLE);
	source_startup_info.hStdOutput  = filter_stdin;
	source_startup_info.hStdInput	= GetStdHandle(STD_INPUT_HANDLE);
	source_startup_info.dwFlags     |= STARTF_USESTDHANDLES;

	GetStartupInfo(&filter_startup_info);
	filter_startup_info.cb			= sizeof(STARTUPINFO);
	filter_startup_info.hStdError	= GetStdHandle(STD_ERROR_HANDLE);
	filter_startup_info.hStdOutput	= sink_stdin;
	filter_startup_info.hStdInput	= source_stdout;
	filter_startup_info.dwFlags		|= STARTF_USESTDHANDLES;

	GetStartupInfo(&sink_startup_info);
	sink_startup_info.cb			= sizeof(STARTUPINFO);
	sink_startup_info.hStdError		= GetStdHandle(STD_ERROR_HANDLE);
	sink_startup_info.hStdOutput	= GetStdHandle(STD_OUTPUT_HANDLE);
	sink_startup_info.hStdInput		= filter_stdout;
	sink_startup_info.dwFlags		|= STARTF_USESTDHANDLES;

	char cmd[MAX_PATH];
	
	// Create Source Process
	sprintf_s(cmd, MAX_PATH, "source.exe %s", argv[1]);
	if (!CreatePipedProcess(cmd, &source_proc_info, &source_startup_info))
	{
		fprintf(stderr, "Failed to start source process\n");
		return 4;
	}

	// Important to close our handle so the process reading knows when we are done
	CloseHandle(filter_stdin);

	// Create Filter Process
	if (!CreatePipedProcess("filter.exe", &filter_proc_info, &filter_startup_info))
	{
		fprintf(stderr, "Failed to start filter process\n");
		return 5;
	}

	// Important to close our handle so the process reading knows when we are done
	CloseHandle(sink_stdin);

	// Create Sink Process
	*cmd = '\0';
	sprintf_s(cmd, MAX_PATH, "sink.exe %s", argv[2]);
	if (!CreatePipedProcess(cmd, &sink_proc_info, &sink_startup_info))
	{
		fprintf(stderr, "Failed to start source process\n");
		return 6;
	}

	// Close our processes
	CleanUpProcess(&source_proc_info);
	CleanUpProcess(&filter_proc_info);
	CleanUpProcess(&sink_proc_info);

	return 0;
}
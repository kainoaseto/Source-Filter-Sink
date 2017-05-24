#include "utils.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s source_file_path destination_file_path\n", argv[0]);
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

	if (!CreatePipe(&source_stdout, &filter_stdin, &pipe_sec_attr, 0))
	{
		fprintf(stderr, "Failed to create source | filter pipe\n");
		return 2;
	}

	if (!CreatePipe(&filter_stdout, &sink_stdin, &pipe_sec_attr, 0))
	{
		fprinf(stderr, "Failed to create filter | sink pipe\n");
		return 3;
	}

	// Setup the startup info with current process information
	source_startup_info.cb			= sizeof(STARTUPINFO);
	source_startup_info.hStdError	= stderr;
	source_startup_info.hStdOutput	= filter_stdin;
	source_startup_info.hStdInput	= stdin;
	source_startup_info.dwFlags		|= STARTF_USESTDHANDLES;

	filter_startup_info.cb			= sizeof(STARTUPINFO);
	filter_startup_info.hStdError	= stderr;
	filter_startup_info.hStdOutput	= sink_stdin;
	filter_startup_info.hStdInput	= filter_stdin;
	filter_startup_info.dwFlags		|= STARTF_USESTDHANDLES;

	sink_startup_info.cb			= sizeof(STARTUPINFO);
	sink_startup_info.hStdError		= stderr;
	sink_startup_info.hStdOutput	= stdout;
	sink_startup_info.hStdInput		= sink_stdin;
	sink_startup_info.dwFlags		|= STARTF_USESTDHANDLES;

	// Create Processes
	char cmd[MAX_PATH];
	
	// Create Source Process
	sprintf_s(cmd, MAX_PATH, "utils/source.exe %s", argv[1]);
	CreatePipedProcess(cmd, &source_proc_info, &source_startup_info);

	// Create Filter Process
	CreatePipedProcess("utils/filter.exe", &filter_proc_info, &filter_startup_info);

	// Create Sink Process
	*cmd = '\0';
	sprinf_s(cmd, MAX_PATH, "utils/sink.exe %s", argv[2]);
	CreatePipedProcess(cmd, &sink_proc_info, &sink_startup_info);

	// Close our processes
	CleanUpProcess(&source_proc_info);
	CleanUpProcess(&filter_proc_info);
	CleanUpProcess(&sink_proc_info);

	return 0;
}
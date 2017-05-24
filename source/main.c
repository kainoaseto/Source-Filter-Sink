// Kainoa Seto
// Source-Filter-Sink 
// This is the source program that takes an input file and outputs it to stdout
// Source/main.c

#include "../include.h"

int main(int argc, char* argv[])
{
	// Since the lab is to demonstrate that all the processes are executing, this
	// makes it more interesting to watch execute.
	fprintf_s(stderr, "Started source.exe\n");

	if (argc != 2)
	{
		fprintf_s(stderr, "Must specify filename as the first argument\n");
		return 1;
	}

	FILE* input_file;
	if ( fopen_s(&input_file, argv[1], "rb") )
	{
		fprintf_s(stderr, "Failed to open file\n");
		return 2;
	}

	int curr_char;
	while ((curr_char = fgetc(input_file)) != EOF)
	{
		// Output char to stdout
		fputc(curr_char, stdout);

		// Artificial Delay so we can watch it all execute
		ART_DELAY();
	}

	fclose(input_file);

	fprintf_s(stderr, "Completed source.exe\n");

	return 0;
}
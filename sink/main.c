// Kainoa Seto
// Source-Filter-Sink 
// This sink program outputs the filtered data back into a new file
// Sink/main.c

#include "../include.h"

int main(int argc, char* argv[])
{
	fprintf_s(stderr, "Started sink.exe\n");

	if (argc != 2)
	{
		fprintf(stderr, "Failed to get destination filename\n");
		return 1;
	}

	FILE* dest_file;
	if ( fopen_s(&dest_file, argv[1], "wb") )
	{
		fprintf(stderr, "Failed to open destination file, it may exist\n");
		return 2;
	}

	int curr_char;
	while ((curr_char = fgetc(stdin)) != EOF)
	{
		// Output to new file
		fputc(curr_char, dest_file);

		// Artificial Delay
		ART_DELAY();
	}

	fclose(dest_file);

	fprintf_s(stderr, "Completed sink.exe\n");

	return 0;
}
#include "../include.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf_s(stderr, "Must specify filename as the first argument\n");
		return 1;
	}

	FILE* input_file;
	if ( !fopen_s(input_file, argv[1], "rb") )
	{
		fprintf_s(stderr, "Failed to open file\n");
		return 2;
	}

	int curr_char;
	for (;;)
	{
		if ((curr_char = fgetc(input_file)) == EOF)
		{
			// Signify that we are done by sending the 'end transmission' ascii char
			fputc(EOF, stdout);
			break;
		}
		// Output char to stdout
		fputc(curr_char, stdout);

		// Artificial Delay so we can watch it all execute
		ART_DELAY();
	}

	fclose(input_file);
	
	return 0;
}
#include "../include.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Failed to get destination filename\n");
		return 1;
	}

	FILE* dest_file;
	if ( fopen_s(&dest_file, argv[1], "wb+") )
	{
		fprintf(stderr, "Failed to open destination file\n");
		return 2;
	}

	int curr_char;
	for (;;)
	{
		// We are done reading in the file
		if ((curr_char = fgetc(stdin)) == EOF)
		{
			fputc(EOF, dest_file);
			break;
		}

		// Output to new file
		fputc(curr_char, dest_file);
	}

	fclose(dest_file);

	return 0;
}
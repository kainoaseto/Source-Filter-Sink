// Kainoa Seto
// Source-Filter-Sink 
// This filter program just filters the lowercase vowels and makes them uppercase
// Source/main.c
#include "../include.h"

int main(int argc, char* argv[])
{
	fprintf_s(stderr, "Started filter.exe\n");

	int curr_char;
	
	for (;;)
	{
		curr_char = fgetc(stdin);
		
		// We have been signaled to end transmission
		if (curr_char == EOF)
		{
			fputc(EOF, stdout);
			break;
		}
		if (curr_char == 'a' ||
			curr_char == 'e' ||
			curr_char == 'i' ||
			curr_char == 'o' ||
			curr_char == 'u')
		{
			curr_char = toupper(curr_char);
		}

		// Make everything uppercase and output to stdout
		fputc( curr_char, stdout );

		// Add our Artificial delay
		ART_DELAY();
	}

	fprintf_s(stderr, "Completed filter.exe\n");

	return 0;
}
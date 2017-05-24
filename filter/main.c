#include "../include.h"

int main(int argc, char* argv[])
{
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

	return 0;
}
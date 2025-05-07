#include "printfd.h"

int main()
{
	int fd = 2; // Standard output
	const char *format = "Hello %s! Your number is %x.\n";
	const char *name = "Alice";
	int number = 1337;
	int oo = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (oo == -1)
	{
		write(fd, "Error opening file\n", 19);
		return 1;
	}

	// Call printfd.h with the format string and arguments
	int result = printfd(format, oo, name, number);

	// Check for errors
	if (result == -1)
	{
		write(fd, "Error occurred\n", 15);
		return 1;
	}

	return 0;
}
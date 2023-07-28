
#include "main.h"

/**
* main - entry point
* @argc: arg count
* @argv: arg vector
*
* Return: 0 on success, 1 on error
*/
int main(int argc, char **argv)
{
	info_t input[] = { INPUT_INIT };
	int fdes = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdes)
			: "r" (fdes));
	if (argc == 2)
	{
		fdes = open(argv[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_err(argv[0]);
				puts_err(": 0: Can't open ");
				puts_err(argv[1]);
				putchar_err('\n');
				putchar_err(FLUSH_BUF);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		input->readfdes = fdes;
	}
	display_env_list(input);
	read_hist(input);
	shell(input, argv);
	return (EXIT_SUCCESS);
}

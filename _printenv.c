#include "main.h"
/**
 * _printenv - this is a funtion that print the environment variable
 * @args: array of commands
 */
void _printenv(char **args)
{
	char **env = __environ;
	int i = 0;

	while (args[i] != NULL)
	{
		if (compare_string(args[i], "env"))
		{
			while (*env != NULL)
			{
				write(1, *env, strlen(*env));
				write(1, "\n", 1);
				env++;
			}
			break;
		}
		i++;
	}
}

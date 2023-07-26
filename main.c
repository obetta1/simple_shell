#include "main.h"
/**
 * main - main function
 * Return: 0 or 1
 */
int main(void)
{
	size_t buffer_size =0;
	char *command_lines;
	ssize_t nread = 0;
	int i = 0;
	char **args;
	const char *error_message = " No such file or directory ";

	while (nread != -1)
	{
		write(1, "$", 1);
		nread = getline(&command_lines,  &buffer_size, stdin);
		args = split_arg(command_lines, " \t\n");
		if (compare_string(args[0], "env"))
		{
		_printenv(args);
		continue;
		}
		if (exit_shell(args))
		{
			break;
		}
		if (access(args[0], X_OK) == -1)
		{
			write(1, args[0], strlen(args[0]));
			write(1, ":", 1);
			write(1, error_message, strlen(error_message));
			write(1, "\n", 1);
			continue;
		}
		else
		{
		_execve(args);
		}
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
		free(args);
	}
	free(command_lines);
	return (0);
}

#include "main.h"
/**
 * main - main function
 * Return: 0 or 1
 */
int main(void)
{
	char *command_lines;
	ssize_t nread = 0;
	int i = 0;
	char **args;
	const char *error_message = "No such file or directory ";

	while (nread != -1)
	{
		write(1, "$", 1);
		command_lines = _getline();
		args = split_arg(command_lines, " \t\n");
		_printenv(args);
		if (exit_shell(args))
			break;
		if (access(args[0], X_OK) == -1)
		{
			write(1, error_message, _strlen(error_message));
			write(1, args[0], _strlen(args[0]));
			write(1, "\n", 1);
			continue;
		}
		_execve(args);
		for (i = 0; args[i] != NULL; i++)
		{
			free(args[i]);
		}
		free(args);
	}
	free(command_lines);
	return (0);
}

#include "main.h"
/**
 * _execve - this used to execute command
 * @args: command arguments
 */
void _execve(char **args)
{
	pid_t child_pid;
	int status = 0;
	char *error_message = "No such file or directory: ";

	child_pid = fork();
	if (child_pid == -1)
	{
		exit(1);
	}
	else if (child_pid == 0)
	{
		execve(args[0], args, NULL);
		write(STDERR_FILENO, error_message, _strlen(error_message));
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, "\n", 1);
		exit(1);
	}
	else
	{
		/**
		 * parrent proccess
		 * this waits for the child procees to finish
		 */
		waitpid(child_pid, &status, 0);
	}
}

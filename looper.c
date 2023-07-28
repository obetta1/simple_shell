
#include "main.h"

/**
* shell - this is the main shell loop that connect all the function
* @input: the parameter & return info struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error
*/
int shell(info_t *input, char **av)
{
	ssize_t s = 0;
	int builtin_ret = 0;

	while (s != -1 && builtin_ret != -2)
	{
		clear_input(input);
		if (is_interactive(input))
			_puts("$ ");
		putchar_err(FLUSH_BUF);
		s = get_input(input);
		if (s != -1)
		{
			set_input(input, av);
			builtin_ret = check_for_builtin(input);
			if (builtin_ret == -1)
				check_cmd(input);
		}
		else if (is_interactive(input))
			_putchar('\n');
		free_input(input, 0);
	}
	print_hist(input);
	free_input(input, 1);
	if (!is_interactive(input) && input->status)
		exit(input->status);
	if (builtin_ret == -2)
	{
		if (input->err_num == -1)
			exit(input->status);
		exit(input->err_num);
	}
	return (builtin_ret);
}

/**
* check_for_builtin - finds a builtin command
* @input: the parameter & return info struct
*
* Return: -1 if builtin not found0 if builtin executed successfully,
* 1 if builtin found but not successful -2 if builtin signals exit()
*/
int check_for_builtin(info_t *input)
{
	int i, built_in_ret = -1;
	builtin_list builtin_lst[] = {
		{"exit", exit_shell},
		{"env", custom_env},
		{"help", btn_help},
		{"history", btn_history},
		{"setenv", _createnv},
		{"unsetenv", _removeenv},
		{"cd", btn_cd},
		{"alias", btn_alias},
		{NULL, NULL}
	};

	i = 0;
	while (builtin_lst[i].type)
	{
		if (_strcmp(input->argv[0], builtin_lst[i].type) == 0)
		{
			input->line_counter++;
			built_in_ret = builtin_lst[i].func(input);
			break;
		}
		i++;
	}
	return (built_in_ret);
}

/**
* check_cmd - finds a command in PATH
* @input: the parameter & return info struct
*
* Return: void
*/
void check_cmd(info_t *input)
{
	char *path = NULL;
	int i, j;

	input->path = input->argv[0];
	if (input->linecount_flag == 1)
	{
		input->line_counter++;
		input->linecount_flag = 0;
	}
	for (i = 0, j = 0; input->arg[i]; i++)
		if (!if_delim(input->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = check_path(input, _getenv(input, "PATH="), input->argv[0]);
	if (path)
	{
		input->path = path;
		custom_fork(input);
	}
	else
	{
		if ((is_interactive(input) || _getenv(input, "PATH=")
					|| input->argv[0][0] == '/') && if_iscmd(input, input->argv[0]))
			custom_fork(input);
		else if (*(input->arg) != '\n')
		{
			input->status = 127;
			print_er(input, "not found\n");
		}
	}
}

/**
* custom_fork - forks a an exec thread to run cmd
* @input: the parameter & return info struct
*
* Return: void
*/
void custom_fork(info_t *input)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(input->path, input->argv, get_environment(input)) == -1)
		{
			free_input(input, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(input->status));
		if (WIFEXITED(input->status))
		{
			input->status = WEXITSTATUS(input->status);
			if (input->status == 126)
				print_er(input, "Permission denied\n");
		}
	}
}

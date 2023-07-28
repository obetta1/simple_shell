#include "main.h"

/**
* exit_shell - exits the shell
* @input: Structure containing potential arguments.
* Return: exits with a given exit status
* (0) if info.argv[0] != "exit"
*/
int exit_shell(info_t *input)
{
	int cancle_check;

	if (input->argv[1])
	{
		cancle_check = atoi_error(input->argv[1]);
		if (cancle_check == -1)
		{
			input->status = 2;
			print_er(input, "Invalide number: ");
			puts_err(input->argv[1]);
			putchar_err('\n');
			return (1);
		}
		input->err_num = atoi_error(input->argv[1]);
		return (-2);
	}
	input->err_num = -1;
	return (-2);
}

/**
* btn_cd - function that changes the current directory of the process
* @input: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int btn_cd(info_t *input)
{
	char *r, *dir, buffer[BUFFER_SIZE];
	int ch_dir;

	r = getcwd(buffer, BUFFER_SIZE);
	if (!r)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!input->argv[1])
	{
		dir = _getenv(input, "HOME=");
		if (!dir)
			chdir((dir = _getenv(input, "PWD=")) ? dir : "/");
		else
			ch_dir = chdir(dir);
	}
	else if (_strcmp(input->argv[1], "-") == 0)
	{
		if (!_getenv(input, "OLDPWD="))
		{
			_puts(r);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(input, "OLDPWD=")), _putchar('\n');
		chdir((dir = _getenv(input, "OLDPWD=")) ? dir : "/");
	}
	else
		ch_dir = chdir(input->argv[1]);
	if (ch_dir == -1)
	{
		print_er(input, "can't cd to ");
		puts_err(input->argv[1]), putchar_err('\n');
	}
	else
	{
		_setenv(input, "OLDPWD", _getenv(input, "PWD="));
		_setenv(input, "PWD", getcwd(buffer, BUFFER_SIZE));
	}
	return (0);
}

/**
* btn_help - changes the current directory of the process
* @info: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int btn_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not found \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

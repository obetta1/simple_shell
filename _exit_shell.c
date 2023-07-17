#include "main.h"
/**
 * exit_shell - this is used to exit the shell when user input 'exit'
 * @args: command arguments
 * Return: 1 whejn the user input is equals to  EXIT
 */
int exit_shell(char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		if (compare_string(args[i], "exit"))
		{
			return (1);
		}
		i++;
	}
	return  (0);
}

/**
 * compare_string - this is used to compare two string
 * @str1: input string
 * @str2: second input string
 * Return: 0 if strings are not equal
 */
int compare_string(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}

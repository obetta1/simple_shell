
#include "main.h"

/**
* is_interactive - checks if shell is interactive mode
* @input: struct address
*
* Return: 1 if interactive mode, 0 otherwise
*/
int is_interactive(info_t *input)
{
	return (isatty(STDIN_FILENO) && input->readfdes <= 2);
}

/**
* if_delim - function that checks if character is a delimeter
* @s: the char to check
* @delim: the delimeter string
* Return: 1 if true, 0 if false
*/
int if_delim(char s, char *delim)
{
	for (; *delim; delim++)
	{
		if (*delim == s)
			return (1);
	}
	return (0);
}

/**
*check_alpha - function that checks for alphabetic character
*@s: The character to input
*Return: 1 if c is alphabetic, 0 otherwise
*/

int check_alpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
*custom_atoi - converts a string to an integer
*@s: the string to be converted
*Return: 0 if no numbers in string, converted number otherwise
*/

int custom_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

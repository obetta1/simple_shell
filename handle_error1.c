
#include "main.h"

/**
* atoi_error - converts a string to an integer
* @str: the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*       -1 on error
*/
int atoi_error(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
* print_er - prints an error message
* @input: the parameter & return info struct
* @err_str: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise -1 on error
*/
void print_er(info_t *input, char *err_str)
{
	puts_err(input->fname);
	puts_err(": ");
	print_decimal(input->line_counter, STDERR_FILENO);
	puts_err(": ");
	puts_err(input->argv[0]);
	puts_err(": ");
	puts_err(err_str);
}

/**
* print_decimal - function prints a decimal (integer) number (base 10)
* @input: the input
* @fdes: the filedescriptor to write to
*
* Return: number of characters printed
*/
int print_decimal(int input, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int i, counter = 0;
	unsigned int _abs_, curr;

	if (fdes == STDERR_FILENO)
		__putchar = putchar_err;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curr / i);
			counter++;
		}
		curr %= i;
	}
	__putchar('0' + curr);
	counter++;
	return (counter);
}

/**
* str_to_digit - converter function, a clone of itoa
* @len: number
* @base: base
* @arg_flags: argument flags
*
* Return: string
*/
char *str_to_digit(long int len, int base, int arg_flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = len;

	if (!(arg_flags & TO_UNSIGNED) && len < 0)
	{
		n = -len;
		sign = '-';
	}
	array = arg_flags & TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
* handle_comments - function replaces first instance of '#' with '\0'
* @buffer: address of the string to modify
*
* Return: Always 0;
*/
void handle_comments(char *buffer)
{
	int j;

	for (j = 0; buffer[j] != '\0'; j++)
		if (buffer[j] == '#' && (!j || buffer[j - 1] == ' '))
		{
			buffer[j] = '\0';
			break;
		}
}


#include "main.h"

/**
* puts_err - prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void puts_err(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
		putchar_err(str[i]);
}

/**
* putchar_err - writes the character c to stderr
* @ch: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int putchar_err(char ch)
{
	static int i;
	static char buf[BUFFER_SIZE];

	if (ch == FLUSH_BUF || i >= BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != FLUSH_BUF)
		buf[i++] = ch;
	return (1);
}

/**
* put_fdesc - writes the character c to given fd
* @ch: The character to print
* @f_des: The filedescriptor to write to
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int put_fdesc(char ch, int f_des)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (ch == FLUSH_BUF || i >= BUFFER_SIZE)
	{
		write(f_des, buffer, i);
		i = 0;
	}
	if (ch != FLUSH_BUF)
		buffer[i++] = ch;
	return (1);
}

/**
*puts_file_desc - prints an input string
* @str: the string to be printed
* @f_des: the filedescriptor to write to
*
* Return: the number of chars put
*/
int puts_file_desc(char *str, int f_des)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fdesc(*str++, f_des);
	}
	return (i);
}

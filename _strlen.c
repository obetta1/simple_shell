#include "main.h"

/**
 * _strlen - function that return the length of a string
 * @str: input string
 * Return: number of character in a string
 */
size_t _strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}

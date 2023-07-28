
#include "main.h"

/**
* _strlen - returns the length of a string
* @s: the string whose length to check
*
* Return: integer length of string
*/
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

/**
* _strcmp - performs lexicogarphic comparison of two strangs.
* @str1: the first strang
* @str2: the second strang
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcmp(char *str1, char *str2)
{
	for (; *str1 && *str2; str1++, str2++)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
* begins_with - checks if needle starts with haystack
* @stack: string to search
* @nd: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *begins_with(const char *stack, const char *nd)
{
	while (*nd)
		if (*nd++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
* _strcat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to destination buffer
*/
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	for (; *dest; dest++)
		;
	for (; *src; src++, dest++)
	{
		*dest = *src;
	}
	*dest = *src;
	return (ret);
}

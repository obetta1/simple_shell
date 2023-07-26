#include "main.h"
#include <stdbool.h>
/**
 * _strtok - this is an inbuilt strtok
 * @str: input string
 * @delim: delimeter
 * Return: string
 */
char *_strtok(char *str, const char *delim)
{
	char *savedToken = NULL;
	const char *d;
	char *startToken;
	bool isDelim;

	if (str != NULL)
		savedToken = str;
	if (savedToken == NULL || *savedToken == '\0')
		return (NULL);
	startToken = savedToken;
	while (*savedToken != '\0')
	{
		isDelim = false;
		for (d = delim; *d != '\0'; d++)
		{
			if (*savedToken == *d)
			{
				isDelim = true;
				break;
			}
		}
		if (isDelim)
		{
			*savedToken = '\0';
			savedToken++;
			return (startToken);
		}
		savedToken++;
	}
	return (startToken);
}

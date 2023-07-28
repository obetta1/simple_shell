
#include "main.h"

/**
* **_strtok - splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @b: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/

char **_strtok(char *str, char *b)
{
	int i, p, k, n, len_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!if_delim(str[i], b) && (if_delim(str[i + 1], b) || !str[i + 1]))
			len_words++;
	if (len_words == 0)
		return (NULL);
	s = malloc((1 + len_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, p = 0; p < len_words; p++)
	{
		while (if_delim(str[i], b))
			i++;
		k = 0;
		while (!if_delim(str[i + k], b) && str[i + k])
			k++;
		s[p] = malloc((k + 1) * sizeof(char));
		if (!s[p])
		{
			for (k = 0; k < p; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			s[p][n] = str[i++];
		s[p][n] = 0;
	}
	s[p] = NULL;
	return (s);
}
/**
* **_strtok2 - splits a string into words
* @str: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **_strtok2(char *str, char d)
{
	int i, p, k, n, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	}
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, p = 0; p < numwords; p++)
	{
		for (; str[i] == d && str[i] != d; i++)
			;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[p] = malloc((k + 1) * sizeof(char));
		if (!s[p])
		{
			for (k = 0; k < p; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < k; n++)
			s[p][n] = str[i++];
		s[p][n] = 0;
	}
	s[p] = NULL;
	return (s);
}

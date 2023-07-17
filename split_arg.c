#include "main.h"
/**
 * split_arg - funtion that split strings into arrays of string
 * @str: input string
 * @delim: delimeter
 * Return: array of strings
 */
char **split_arg(char *str, char *delim)
{
	char **words;
	char *token = strtok(strdup(str), delim);
	int i = 0;

	words = (char **)malloc(strlen(str) * sizeof(char *));
	if (words == NULL)
	{
		return (NULL);
	}
	while (token != NULL)
	{
		words[i] = strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	free(words[i]);
	return (words);
}

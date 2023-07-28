
#include "main.h"

/**
* if_iscmd - determines if a file is an executable command
* @input: the info struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int if_iscmd(info_t *input, char *path)
{
	struct stat st;
	(void)input;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
* chr_dup - duplicates characters
* @str: the PATH string
* @begin: starting index
* @end: stopping index
*
* Return: pointer to new buffer
*/
char *chr_dup(char *str, int begin, int end)
{
	static char buffer[BUFFER_SIZE];
	int i = 0, j = 0;

	for (j = 0, i = begin; i < end; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
* check_path - finds this cmd in the PATH string
* @input: the info struct
* @str: the PATH string
* @command: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *check_path(info_t *input, char *str, char *command)
{
	int i = 0, cur_position = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((_strlen(command) > 2) && begins_with(command, "./"))
	{
		if (if_iscmd(input, command))
			return (command);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			path = chr_dup(str, cur_position, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (if_iscmd(input, path))
				return (path);
			if (!str[i])
				break;
			cur_position = i;
		}
		i++;
	}
	return (NULL);
}

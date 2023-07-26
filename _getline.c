#include "main.h"
#define BUFFER_SIZE 1024
/**
 * _getline - this is a getline function to read user input
 * check_line - checcks if lin is empty
 * Return: string of command lines
 */
char *_getline()
{
	char buffer[BUFFER_SIZE], *error_message = "Line too long";
	int position = 0, hasInput = 0, byteRead = 0, lineLenght = 0;
	char *line = (char *)malloc(BUFFER_SIZE * sizeof(char));

	while (1)
	{
		if (position == byteRead)
		{
			byteRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			position = 0;
			if (byteRead == 1)
				return (check_line(hasInput, line, lineLenght));
			if (byteRead == 0)
				return (NULL);
		}
		while (position < byteRead)
		{
			if (buffer[position] == '\n')
			{
				line[lineLenght] = '\0';
				position++;
				return (line);
			}
			else
			{
				line[lineLenght++] = buffer[position++];
				hasInput = 1;
			}
			if (lineLenght >= BUFFER_SIZE - 1)
			{
				write(1, error_message, _strlen(error_message));
				free(line);
				return (NULL);
			}
		}
	}
}
/**
 * check_line - checcks if lin is empty
 * @hasInput: input flag
 * @line: input line
 * @lineLength: lent
 * Return: string of command lines
 */
char *check_line(int hasInput, char *line, int lineLength)
{
	if (!hasInput)
	{
		free(line);
		return (" ");
	}
	line[lineLength] = '\0';
	return (line);
}

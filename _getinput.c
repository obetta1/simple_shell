
#include "main.h"

/**
* clear_input - initializes info_t struct
* @input: struct address
*/
void clear_input(info_t *input)
{
	input->arg = NULL;
	input->argv = NULL;
	input->path = NULL;
	input->argc = 0;
}

/**
* set_input - initializes info_t struct
* @input: struct address
* @av: argument vector
*/
void set_input(info_t *input, char **av)
{
	int j = 0;

	input->fname = av[0];
	if (input->arg)
	{
		input->argv = _strtok(input->arg, " \t");
		if (!input->argv)
		{
			input->argv = malloc(sizeof(char *) * 2);
			if (input->argv)
			{
				input->argv[0] = _strdup(input->arg);
				input->argv[1] = NULL;
			}
		}
		for (j = 0; input->argv && input->argv[j]; j++)
			;
		input->argc = j;
		update_alias(input);
		update_vars(input);
	}
}

/**
* free_input - frees info_t struct fields
* @input: struct address
* @l: true if freeing all fields
*/
void free_input(info_t *input, int l)
{
	free_mem(input->argv);
	input->argv = NULL;
	input->path = NULL;
	if (l)
	{
		if (!input->cmd_buf)
			free(input->arg);
		if (input->env)
			free_list_node(&(input->env));
		if (input->history)
			free_list_node(&(input->history));
		if (input->alias)
			free_list_node(&(input->alias));
		free_mem(input->environ);
		input->environ = NULL;
		custom_free((void **)input->cmd_buf);
		if (input->readfdes > 2)
			close(input->readfdes);
		_putchar(FLUSH_BUF);
	}
}

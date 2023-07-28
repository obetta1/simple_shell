
#include "main.h"

/**
* if_chain - this function checks if
* current char in buffer is a chain delimeter
* @input: the parameter struct
* @buffer: the char buffer
* @ptr: address of current position in buf
*
* Return: 1 if chain delimeter, 0
*/
int if_chain(info_t *input, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		input->cmd_buf_type = _OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		input->cmd_buf_type = _AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		input->cmd_buf_type = _CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
* check_is_chain - this function checks if it should
* continue chaining based on last status
* @input: the parameter struct
* @buffer: the char buffer
* @ptr: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_is_chain(info_t *input, char *buffer, size_t *ptr,
		size_t i, size_t len)
{
	size_t j = *ptr;

	if (input->cmd_buf_type == _AND)
	{
		if (input->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (input->cmd_buf_type == _OR)
	{
		if (!input->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	*ptr = j;
}

/**
* update_alias - replaces an aliases in the tokenized string
* @input: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int update_alias(info_t *input)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_begins_with(input->alias, input->argv[0], '=');
		if (!node)
			return (0);
		free(input->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		input->argv[0] = ptr;
	}
	return (1);
}

/**
* update_vars - replaces vars in the tokenized string
* @input: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int update_vars(info_t *input)
{
	int j = 0;
	list_t *node;

	for (j = 0; input->argv[j]; j++)
	{
		if (input->argv[j][0] != '$' || !input->argv[j][1])
			continue;
		if (!_strcmp(input->argv[j], "$?"))
		{
			update_string(&(input->argv[j]),
					_strdup(str_to_digit(input->status, 10, 0)));
			continue;
		}

		if (!_strcmp(input->argv[j], "$$"))
		{
			update_string(&(input->argv[j]),
					_strdup(str_to_digit(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(input->env, &input->argv[j][1], '=');
		if (node)
		{
			update_string(&(input->argv[j]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		update_string(&input->argv[j], _strdup(""));

	}
	return (0);
}

/**
* update_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int update_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

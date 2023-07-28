#include "main.h"

/**
* get_environment - returns the string array copy of our environ
* @input: Structure containing potential
* Return: Always 0
*/
char **get_environment(info_t *input)
{
	if (!input->environ || input->onchanged_env)
	{
		input->environ = convert_list_to_str(input->env);
		input->onchanged_env = 0;
	}
	return (input->environ);
}

/**
* _unsetenv - Remove an environment variable
* @input: Structure containing potential arguments.
* Return: 1 on delete, 0 otherwise
* @var: the string env var property
*/
int _unsetenv(info_t *input, char *var)
{
	list_t *node = input->env;
	size_t j = 0;
	char *ptr;

	if (!node || !var)
		return (0);
	for (; node; node = node->next, j++)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			input->onchanged_env = remove_node_at_index(&(input->env), j);
			j = 0;
			node = input->env;
			continue;
		}
	}
	return (input->onchanged_env);
}

/**
* _setenv - Initialize a new environment variable,
* @input: Structure containing potential arguments.
* @var: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(info_t *input, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);
	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = input->env;
	while (node)
	{
		ptr = begins_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			input->onchanged_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_to_node_end(&(input->env), buffer, 0);
	free(buffer);
	input->onchanged_env = 1;
	return (0);
}

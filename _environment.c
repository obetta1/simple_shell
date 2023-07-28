#include "main.h"
/**
* custom_env - prints the current environment
* @input: Structure containing potential arguments.
* Used to maintain constant function prototype.
* Return: Always 0
*/
int custom_env(info_t *input)
{
	print_list_str(input->env);
	return (0);
}

/**
* _getenv - gets the value of an environ variable
* @input: Structure containing potential arguments. Used to maintain
* @nam: env var name
*
* Return: the value
*/
char *_getenv(info_t *input, const char *nam)
{
	list_t *node = input->env;
	char *ptr;

	for (; node; node = node->next)
	{
		ptr = begins_with(node->str, nam);
		if (ptr && *ptr)
			return (ptr);
	}
	return (NULL);
}

/**
* _createnv - Initialize a new environment variable, or modify an existing one
* @input: Structure containing potential arguments.
* Used to maintain constant function prototype.
*  Return: Always 0
*/
int _createnv(info_t *input)
{
	if (input->argc != 3)
	{
		puts_err("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(input, input->argv[1], input->argv[2]))
		return (0);
	return (1);
}

/**
* _removeenv - Remove an environment variable
* @input: Structure containing potential arguments.
*  Return: Always 0
*/
int _removeenv(info_t *input)
{
	int j;

	if (input->argc == 1)
	{
		puts_err("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= input->argc; j++)
		_unsetenv(input, input->argv[j]);
	return (0);
}

/**
* display_env_list - populates env linked list
* @input: Structure containing potential arguments. Used to maintain
* Return: Always 0
*/
int display_env_list(info_t *input)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_to_node_end(&node, environ[j], 0);
	input->env = node;
	return (0);
}

#include "main.h"

/**
* btn_history - displays the history list,
* one command by line, preceded with line numbers, starting at 0.
* @input: Structure containing potential arguments.
* Return: Always 0
*/
int btn_history(info_t *input)
{
	print_list(input->history);
	return (0);
}

/**
* unset_btn_alias - sets alias to string
* @input: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int unset_btn_alias(info_t *input, char *str)
{
	char *p, s;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	s = *p;
	*p = 0;
	ret = remove_node_at_index(&(input->alias),
			get_index_of_node(input->alias, node_begins_with(input->alias, str, -1)));
	*p = s;
	return (ret);
}

/**
* set_btn_alias - sets alias to string
* @input: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int set_btn_alias(info_t *input, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_btn_alias(input, str));
	unset_btn_alias(input, str);
	return (add_to_node_end(&(input->alias), str, 0) == NULL);
}

/**
* print_btn_alias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int print_btn_alias(list_t *node)
{
	char *ptr = NULL, *i = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (i = node->str; i <= ptr; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
* btn_alias - mimics the alias builtin (man alias)
* @input: Structure containing potential arguments.constant function prototype.
*  Return: Always 0
*/
int btn_alias(info_t *input)
{
	int j = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (input->argc == 1)
	{
		for (node = input->alias; node; node = node->next)
		{
			print_btn_alias(node);
		}
		return (0);
	}
	for (j = 1; input->argv[j]; j++)
	{
		ptr = _strchr(input->argv[j], '=');
		if (ptr)
			set_btn_alias(input, input->argv[j]);
		else
			print_btn_alias(node_begins_with(input->alias, input->argv[j], '='));
	}
	return (0);
}

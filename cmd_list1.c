
#include "main.h"

/**
* len_of_list - determines length of linked list
* @s: pointer to first node
*
* Return: size of list
*/
size_t len_of_list(const list_t *s)
{
	size_t i = 0;

	for (; s; s = s->next)
	i++;
	return (i);
}

/**
* convert_list_to_str - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **convert_list_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = len_of_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
* print_list - prints all elements of a list_t linked list
* @s: pointer to first node
*
* Return: size of list
*/
size_t print_list(const list_t *s)
{
	size_t i = 0;

	for (; s; s = s->next)
	{
		_puts(str_to_digit(s->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(s->str ? s->str : "(nil)");
		_puts("\n");
		i++;
	}
	return (i);
}

/**
* node_begins_with - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
*
* Return: match node or null
*/
list_t *node_begins_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begins_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
* get_index_of_node - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: index of node or -1
*/
ssize_t get_index_of_node(list_t *head, list_t *node)
{
	size_t i = 0;

	for (; head; head = head->next, i++)
	{
		if (head == node)
			return (i);
	}
	return (-1);
}

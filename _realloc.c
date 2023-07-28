
#include "main.h"

/**
**set_mem - fills memory with a constant byte
*@str: the pointer to the memory area
*@d: the byte to fill *s with
*@n: the amount of bytes to be filled
*Return: (s) a pointer to the memory area s
*/
char *set_mem(char *str, char d, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = d;
	return (str);
}

/**
* free_mem - frees a string of strings
* @ptr: string of strings
*/
void free_mem(char **ptr)
{
	char **a = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(a);
}

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @size_o: byte size of previous block
* @size_n: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int size_o, unsigned int size_n)
{
	char *pt;

	if (!ptr)
		return (malloc(size_n));
	if (!size_n)
		return (free(ptr), NULL);
	if (size_n == size_o)
		return (ptr);
	pt = malloc(size_n);
	if (!pt)
		return (NULL);
	size_o = size_o < size_n ? size_o : size_n;
	while (size_o--)
		pt[size_o] = ((char *)ptr)[size_o];
	free(ptr);
	return (pt);
}

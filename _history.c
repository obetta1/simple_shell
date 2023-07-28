#include "main.h"

/**
* get_hist_file - gets the history file
* @input: parameter struct
*
* Return: allocated string containg history file
*/

char *get_hist_file(info_t *input)
{
	char *buffer, *d;

	d = _getenv(input, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(d) + _strlen(HISTORY) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY);
	return (buffer);
}

/**
* print_hist - creates a file, or appends to an existing file
* @input: the parameter struct
*
* Return: 1 on success, else -1
*/
int print_hist(info_t *input)
{
	ssize_t f_des;
	char *file_n = get_hist_file(input);
	list_t *node = NULL;

	if (!file_n)
		return (-1);
	f_des = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_n);
	if (f_des == -1)
		return (-1);
	for (node = input->history; node; node = node->next)
	{
		puts_file_desc(node->str, f_des);
		put_fdesc('\n', f_des);
	}
	put_fdesc(FLUSH_BUF, f_des);
	close(f_des);
	return (1);
}

/**
* read_hist - reads history from file
* @input: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_hist(info_t *input)
{
	int i, lst = 0, counter = 0;
	ssize_t fdes, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *file_n = get_hist_file(input);

	if (!file_n)
		return (0);
	fdes = open(file_n, O_RDONLY);
	free(file_n);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdes, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdes);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_history_list(input, buf + lst, counter++);
			lst = i + 1;
		}
	if (lst != i)
		create_history_list(input, buf + lst, counter++);
	free(buf);
	input->historycounter = counter;
	while (input->historycounter-- >= HISTORY_MAX_LEN)
		remove_node_at_index(&(input->history), 0);
	update_history_num(input);
	return (input->historycounter);
}

/**
* create_history_list - adds entry to a history linked list
* @input: Structure containing potential arguments. Used to maintain
* @buffer: buffer
* @counter: the history linecount, histcount
*
* Return: Always 0
*/
int create_history_list(info_t *input, char *buffer, int counter)
{
	list_t *node = NULL;

	if (input->history)
		node = input->history;
	add_to_node_end(&node, buffer, counter);
	if (!input->history)
		input->history = node;
	return (0);
}

/**
* update_history_num - renumbers the history linked list after changes
* @input: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int update_history_num(info_t *input)
{
	list_t *node = input->history;
	int j;

	for (j = 0; node; node = node->next, j++)
	{
		node->num = j;
	}
	input->historycounter = j;
	return (j);
}

#include "main.h"

/**
* input_buf - buffers chained commands
* @input: parameter struct
* @buffer: address of buffer
* @size: address of len var
*
* Return: bytes read
*/
ssize_t input_buf(info_t *input, char **buffer, size_t *size)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*size)/* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buffer, &len_p, stdin);
#else
		s = _getline(input, buffer, &len_p);
#endif
		if (s > 0)
		{
			if ((*buffer)[s - 1] == '\n')
			{
				(*buffer)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			input->linecount_flag = 1;
			handle_comments(*buffer);
			create_history_list(input, *buffer, input->historycounter++);
			if (_strchr(*buffer, ';'))
			{
				*size = s;
				input->cmd_buf = buffer;
			}
		}
	}
	return (s);
}

/**
* get_input - gets a line minus the newline
* @input: parameter struct
*
* Return: bytes read
*/
ssize_t get_input(info_t *input)
{
	static char *buffer;
	static size_t  len, i, j;
	ssize_t s = 0;
	char **buf_r = &(input->arg), *ptr;

	_putchar(FLUSH_BUF);
	s = input_buf(input, &buffer, &len);
	if (s == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buffer + i;
		check_is_chain(input, buffer, &j, i, len);
		while (j < len)
		{
			if (if_chain(input, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			input->cmd_buf_type = _NORM;
		}
		*buf_r = ptr;
		return (_strlen(ptr));
	}
	*buf_r = buffer;
	return (s);
}

/**
* read_buf - reads a buffer
* @input: parameter struct
* @buffer: buffer
* @j: size
*
* Return: s
*/
ssize_t read_buf(info_t *input, char *buffer, size_t *j)
{
	ssize_t s = 0;

	if (*j)
		return (0);
	s = read(input->readfdes, buffer, BUFFER_SIZE);
	if (s >= 0)
		*j = s;
	return (s);
}

/**
* _getline - gets the next line of input from STDIN
* @input: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @size: size of preallocated ptr buffer if not NULL
*
* Return: s
*/
int _getline(info_t *input, char **ptr, size_t *size)
{
	static char buf[BUFFER_SIZE];
	char *pt = NULL, *new_pt = NULL, *c;
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;

	pt = *ptr;
	if (pt && size)
		s = *size;
	if (i == len)
		i = len = 0;
	r = read_buf(input, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_pt = _realloc(pt, s, s ? s + k : k + 1);
	if (!new_pt)
		return (pt ? free(pt), -1 : -1);
	if (s)
		_strncat(new_pt, buf + i, k - i);
	else
		_strncpy(new_pt, buf + i, k - i + 1);
	s += k - i;
	i = k;
	pt = new_pt;
	if (size)
		*size = s;
	*ptr = pt;
	return (s);
}

/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUF);
}

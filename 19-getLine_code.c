#include "main.h"

/**
 * input_buf - buffers chained commands
 * @param: parameter struct
 * @buf_addr: address of buffer
 * @var_len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *param, char **buf_addr, size_t *var_len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*var_len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)param->cmd_buf);*/
		free(*buf_addr);
		*buf_addr = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		x = _getline(param, buf_addr, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf_addr)[x - 1] == '\n')
			{
				(*buf_addr)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			param->linecount_flag = 1;
			remove_comments(*buf_addr);
			build_history(param, *buf_addr, param->hist_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*var_len = x;
				param->cmd_buffer = buf_addr;
			}
		}
	}
	return (x);
}

/**
 * get_input - gets a line minus the newline
 * @param: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *param)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, lenght;
	ssize_t a = 0;
	char **buf_p = &(param->arg), *p;

	_putchar(BUFFER_FLUSH);
	a = input_buf(param, &buf, &lenght);
	if (a == -1) /* EOF */
		return (-1);
	if (lenght) /* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		p = buf + x; /* get pointer for return */

		check_chain(param, buf, &y, x, lenght);
		while (y < lenght) /* iterate to semicolon or end */
		{
			if (is_chain(param, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= lenght) /* reached end of buffer? */
		{
			x = lenght = 0; /* reset position and length */
			param->cmd_buffer_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (a); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @param: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *param, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(param->readfd, buf, READ_BUFFER_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * _getline - gets the next line of input from STDIN
 * @param: parameter struct
 * @ptr_addr: address of pointer to buffer, preallocated or NULL
 * @ptr_size: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *param, char **ptr_addr, size_t *ptr_size)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t x, len;
	size_t b;
	ssize_t y = 0, z = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr_addr;
	if (p && ptr_size)
		z = *ptr_size;
	if (x == len)
		x = len = 0;

	y = read_buf(param, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = _strchr(buf + x, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, z, z ? z + b : b + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat(new_p, buf + x, b - x);
	else
		_strncpy(new_p, buf + x, b - x + 1);

	z += b - x;
	x = b;
	p = new_p;

	if (ptr_size)
		*ptr_size = z;
	*ptr_addr = p;
	return (z);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signal_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

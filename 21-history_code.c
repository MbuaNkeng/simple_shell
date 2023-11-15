#include "main.h"

/**
 * retrieve_history - gets the history file
 * @param: parameter struct
 * Return: allocated string containg history file
 */

char *retrieve_history(info_t *param)
{
	char *buff, *directory;

	directory = _getenv(param, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, directory);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * create_history - creates a file, or appends to an existing file
 * @param: the parameter struct
 * Return: 1 on success, else -1
 */
int create_history(info_t *param)
{
	ssize_t file_desc;
	char *file_name = retrieve_history(param);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	file_desc = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_desc == -1)
		return (-1);
	for (node = param->history; node; node = node->next)
	{
		_putsfd(node->str, file_desc);
		_putfd('\n', file_desc);
	}
	_putfd(BUFFER_FLUSH, file_desc);
	close(file_desc);
	return (1);
}

/**
 * read_history - reads history from file
 * @param: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *param)
{
	int x, last = 0, linecount = 0;
	ssize_t file_desc, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = retrieve_history(param);

	if (!filename)
		return (0);

	file_desc = open(filename, O_RDONLY);
	free(filename);
	if (file_desc == -1)
		return (0);
	if (!fstat(file_desc, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(file_desc, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(file_desc);
	for (x = 0; x < fsize; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			build_history(param, buff + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_history(param, buff + last, linecount++);
	free(buff);
	param->hist_count = linecount;
	while (param->hist_count-- >= HIST_MAX)
		delete_node_at_index(&(param->history), 0);
	reorder_history(param);
	return (param->hist_count);
}

/**
 * build_history - adds entry to a history linked list
 * @param: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history(info_t *param, char *buf, int linecount)
{
	list_t *node = NULL;

	if (param->history)
		node = param->history;
	add_node_end(&node, buf, linecount);

	if (!param->history)
		param->history = node;
	return (0);
}

/**
 * reorder_history - renumbers the history linked list after changes
 * @param: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */
int reorder_history(info_t *param)
{
	list_t *node = param->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (param->hist_count = x);
}

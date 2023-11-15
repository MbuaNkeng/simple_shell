#include "main.h"

/**
 * is_cmd - determines if a file is an executable command
 * @param: the param struct
 * @file_path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *param, char *file_path)
{
	struct stat st;

	(void)param;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start, int stop)
{
	static char buffer[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (path_str[x] != ':')
			buffer[y++] = path_str[x];
	buffer[y] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @param: the param struct
 * @path_str: the PATH string
 * @find_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *param, char *path_str, char *find_cmd)
{
	int x = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(find_cmd) > 2) && starts_with(find_cmd, "./"))
	{
		if (is_cmd(param, find_cmd))
			return (find_cmd);
	}
	while (1)
	{
		if (!path_str[x] || path_str[x] == ':')
		{
			path = dup_chars(path_str, curr_pos, x);
			if (!*path)
				_strcat(path, find_cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, find_cmd);
			}
			if (is_cmd(param, path))
				return (path);
			if (!path_str[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}

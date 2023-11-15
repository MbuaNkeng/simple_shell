#include "main.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @param: the parameter struct
 * @buffer: the char buffer
 * @buf_pos: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *param, char *buffer, size_t *buf_pos)
{
	size_t x = *buf_pos;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		param->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		param->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[x] == ';') /* found end of this command */
	{
		buffer[x] = 0; /* replace semicolon with null */
		param->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*buf_pos = x;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @param: the parameter struct
 * @buffer: the char buffer
 * @curr_pos: address of current position in buf
 * @start: starting position in buf
 * @buf_len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *param, char *buffer, size_t *curr_pos, size_t start, size_t buf_len)
{
	size_t x = *curr_pos;

	if (param->cmd_buffer_type == CMD_AND)
	{
		if (param->status)
		{
			buffer[start] = 0;
			x = buf_len;
		}
	}
	if (param->cmd_buffer_type == CMD_OR)
	{
		if (!param->status)
		{
			buffer[start] = 0;
			x = buf_len;
		}
	}

	*curr_pos = x;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @param: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *param)
{
	int x;
	list_t *node;
	char *y;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(param->alias, param->argv[0], '=');
		if (!node)
			return (0);
		free(param->argv[0]);
		y = _strchr(node->str, '=');
		if (!y)
			return (0);
		y = _strdup(y + 1);
		if (!y)
			return (0);
		param->argv[0] = y;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @param: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *param)
{
	int x = 0;
	list_t *node;

	for (x = 0; param->argv[x]; x++)
	{
		if (param->argv[x][0] != '$' || !param->argv[x][1])
			continue;

		if (!_strcmp(param->argv[x], "$?"))
		{
			replace_string(&(param->argv[x]),
					_strdup(convert_number(param->status, 10, 0)));
			continue;
		}
		if (!_strcmp(param->argv[x], "$$"))
		{
			replace_string(&(param->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(param->env, &param->argv[x][1], '=');
		if (node)
		{
			replace_string(&(param->argv[x]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&param->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

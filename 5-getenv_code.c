#include "main.h"

/**
 * get_environ - returns the string array copy of our environ
 * @param: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *param)
{
	if (!param->environ || param->env_changed)
	{
		param->environ = list_to_strings(param->env);
		param->env_changed = 0;
	}

	return (param->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @param: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @str_var: the string env var property
 */
int _unsetenv(info_t *param, char *str_var)
{
	list_t *node = param->env;
	size_t x = 0;
	char *y;

	if (!node || !str_var)
		return (0);

	while (node)
	{
		y = starts_with(node->str, str_var);
		if (y && *y == '=')
		{
			param->env_changed = delete_node_at_index(&(param->env), x);
			x = 0;
			node = param->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (param->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @param: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @str_var: the string env var property
 * @str_value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *param, char *str_var, char *str_value)
{
	char *buffer = NULL;
	list_t *node;
	char *y;

	if (!str_var || !str_value)
		return (0);

	buffer = malloc(_strlen(str_var) + _strlen(str_value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, str_var);
	_strcat(buffer, "=");
	_strcat(buffer, str_value);
	node = param->env;
	while (node)
	{
		y = starts_with(node->str, str_var);
		if (y && *y == '=')
		{
			free(node->str);
			node->str = buffer;
			param->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(param->env), buffer, 0);
	free(buffer);
	param->env_changed = 1;
	return (0);
}

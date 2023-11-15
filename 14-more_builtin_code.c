#include "main.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @param: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *param)
{
	print_list(param->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @param: parameter struct
 * @str_alias: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *param, char *str_alias)
{
	char *x, y;
	int result;

	x = _strchr(str_alias, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	result = delete_node_at_index(&(param->alias),
		get_node_index(param->alias, node_starts_with(param->alias, str_alias, -1)));
	*x = y;
	return (result);
}

/**
 * set_alias - sets alias to string
 * @param: parameter struct
 * @str_alias: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *param, char *str_alias)
{
	char *x;

	x = _strchr(str_alias, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(param, str_alias));

	unset_alias(param, str_alias);
	return (add_node_end(&(param->alias), str_alias, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @alias_node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *x = NULL, *a = NULL;

	if (alias_node)
	{
		x = _strchr(alias_node->str, '=');
		for (a = alias_node->str; a <= x; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @param: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *param)
{
	int x = 0;
	char *y = NULL;
	list_t *node = NULL;

	if (param->argc == 1)
	{
		node = param->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; param->argv[x]; x++)
	{
		y = _strchr(param->argv[x], '=');
		if (y)
			set_alias(param, param->argv[x]);
		else
			print_alias(node_starts_with(param->alias, param->argv[x], '='));
	}

	return (0);
}

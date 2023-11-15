#include "main.h"

/**
 * _myenv - prints the current environment
 * @param: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *param)
{
	print_list_str(param->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @param: Structure containing potential arguments. Used to maintain
 * @env_name: env var name
 * Return: the value
 */
char *_getenv(info_t *param, const char *env_name)
{
	list_t *node = param->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, env_name);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @param: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *param)
{
	if (param->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(param, param->argv[1], param->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @param: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *param)
{
	int x;

	if (param->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= param->argc; x++)
		_unsetenv(param, param->argv[x]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @param: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *param)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	param->env = node;
	return (0);
}

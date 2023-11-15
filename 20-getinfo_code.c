#include "main.h"

/**
 * clear_info - initializes info_t struct
 * @param: struct address
 */
void clear_info(info_t *param)
{
	param->arg = NULL;
	param->argv = NULL;
	param->path = NULL;
	param->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @param: struct address
 * @arg_vector: argument vector
 */
void set_info(info_t *param, char **arg_vector)
{
	int x = 0;

	param->fname = arg_vector[0];
	if (param->arg)
	{
		param->argv = strtow(param->arg, " \t");
		if (!param->argv)
		{
			param->argv = malloc(sizeof(char *) * 2);
			if (param->argv)
			{
				param->argv[0] = _strdup(param->arg);
				param->argv[1] = NULL;
			}
		}
		for (x = 0; param->argv && param->argv[x]; x++)
			;
		param->argc = x;

		replace_alias(param);
		replace_vars(param);
	}
}

/**
 * free_info - frees info_t struct fields
 * @param: struct address
 * @all_fields: true if freeing all fields
 */
void free_info(info_t *param, int all_fields)
{
	ffree(param->argv);
	param->argv = NULL;
	param->path = NULL;
	if (all_fields)
	{
		if (!param->cmd_buffer)
			free(param->arg);
		if (param->env)
			free_list(&(param->env));
		if (param->history)
			free_list(&(param->history));
		if (param->alias)
			free_list(&(param->alias));
		ffree(param->environ);
			param->environ = NULL;
		bfree((void **)param->cmd_buffer);
		if (param->readfd > 2)
			close(param->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

#include "main.h"

/**
 * hsh - main shell loop
 * @param: the parameter & return param struct
 * @arg_vector: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *param, char **arg_vector)
{
	ssize_t x = 0;
	int builtin_result = 0;

	while (x != -1 && builtin_result != -2)
	{
		clear_info(param);
		if (interactive(param))
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		x = get_input(param);
		if (x != -1)
		{
			set_info(param, arg_vector);
			builtin_result = find_builtin(param);
			if (builtin_result == -1)
				find_cmd(param);
		}
		else if (interactive(param))
			_putchar('\n');
		free_info(param, 0);
	}
	create_history(param);
	free_info(param, 1);
	if (!interactive(param) && param->status)
		exit(param->status);
	if (builtin_result == -2)
	{
		if (param->err_num == -1)
			exit(param->status);
		exit(param->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - finds a builtin command
 * @param: the parameter & return param struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *param)
{
	int x, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(param->argv[0], builtintbl[x].type) == 0)
		{
			param->line_count++;
			built_in_result = builtintbl[x].func(param);
			break;
		}
	return (built_in_result);
}

/**
 * find_cmd - finds a command in PATH
 * @param: the parameter & return param struct
 * Return: void
 */
void find_cmd(info_t *param)
{
	char *path = NULL;
	int x, y;

	param->path = param->argv[0];
	if (param->linecount_flag == 1)
	{
		param->line_count++;
		param->linecount_flag = 0;
	}
	for (x = 0, y = 0; param->arg[x]; x++)
		if (!is_delim(param->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	path = find_path(param, _getenv(param, "PATH="), param->argv[0]);
	if (path)
	{
		param->path = path;
		fork_cmd(param);
	}
	else
	{
		if ((interactive(param) || _getenv(param, "PATH=")
					|| param->argv[0][0] == '/') && is_cmd(param, param->argv[0]))
			fork_cmd(param);
		else if (*(param->arg) != '\n')
		{
			param->status = 127;
			print_error(param, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @param: the parameter & return param struct
 * Return: void
 */
void fork_cmd(info_t *param)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(param->path, param->argv, get_environ(param)) == -1)
		{
			free_info(param, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(param->status));
		if (WIFEXITED(param->status))
		{
			param->status = WEXITSTATUS(param->status);
			if (param->status == 126)
				print_error(param, "Permission denied\n");
		}
	}
}

#include "main.h"

/**
 * _myexit - exits the shell
 * @param: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if param.argv[0] != "exit"
 */
int _myexit(info_t *param)
{
	int exit_check;

	if (param->argv[1]) /* If there is an exit arguement */
	{
		exit_check = _erratoi(param->argv[1]);
		if (exit_check == -1)
		{
			param->status = 2;
			print_error(param, "Illegal number: ");
			_eputs(param->argv[1]);
			_eputchar('\n');
			return (1);
		}
		param->err_num = _erratoi(param->argv[1]);
		return (-2);
	}
	param->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @param: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *param)
{
	char *str, *dir, buffer[1024];
	int chdir_result;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!param->argv[1])
	{
		dir = _getenv(param, "HOME=");
		if (!dir)
			chdir_result = /* TODO: what should this be? */
				chdir((dir = _getenv(param, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (_strcmp(param->argv[1], "-") == 0)
	{
		if (!_getenv(param, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(param, "OLDPWD=")), _putchar('\n');
		chdir_result = /* TODO: what should this be? */
			chdir((dir = _getenv(param, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(param->argv[1]);
	if (chdir_result == -1)
	{
		print_error(param, "can't cd to ");
		_eputs(param->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(param, "OLDPWD", _getenv(param, "PWD="));
		_setenv(param, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @param: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *param)
{
	char **arg_array;

	arg_array = param->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

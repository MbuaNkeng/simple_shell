#include "main.h"

/**
 * _erratoi - converts a string to an integer
 * @str_conv: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str_conv)
{
	int x = 0;
	unsigned long int product = 0;

	if (*str_conv == '+')
		str_conv++;  /* TODO: why does this make main return 255? */
	for (x = 0;  str_conv[x] != '\0'; x++)
	{
		if (str_conv[x] >= '0' && str_conv[x] <= '9')
		{
			product *= 10;
			product += (str_conv[x] - '0');
			if (product > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (product);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @str_err: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *str_err)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(str_err);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @file_desc: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int file_desc)
{
	int (*__putchar)(char) = _putchar;
	int x, counter = 0;
	unsigned int _abs_, current;

	if (file_desc == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			counter++;
		}
		current %= x;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @arg_flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int arg_flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long x = num;

	if (!(arg_flags & CONVERT_UNSIGNED) && num < 0)
	{
		x = -num;
		sign = '-';

	}
	array = arg_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[x % base];
		x /= base;
	} while (x != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @str_add: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *str_add)
{
	int x;

	for (x = 0; str_add[x] != '\0'; x++)
		if (str_add[x] == '#' && (!x || str_add[x - 1] == ' '))
		{
			str_add[x] = '\0';
			break;
		}
}

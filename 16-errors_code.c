#include "main.h"

/**
 * _eputs - prints an input string
 * @str_print: the string to be printed
 * Return: Nothing
 */
void _eputs(char *str_print)
{
	int i = 0;

	if (!str_print)
		return;
	while (str_print[i] != '\0')
	{
		_eputchar(str_print[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @char_print: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char char_print)
{
	static int x;
	static char buf[WRITE_BUFFER_SIZE];

	if (char_print == BUFFER_FLUSH || x >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (char_print != BUFFER_FLUSH)
		buf[x++] = char_print;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @char_print: The character to print
 * @file_desc: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char char_print, int file_desc)
{
	static int x;
	static char buf[WRITE_BUFFER_SIZE];

	if (char_print == BUFFER_FLUSH || x >= WRITE_BUFFER_SIZE)
	{
		write(file_desc, buf, x);
		x = 0;
	}
	if (char_print != BUFFER_FLUSH)
		buf[x++] = char_print;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str_print: the string to be printed
 * @file_desc: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str_print, int file_desc)
{
	int x = 0;

	if (!str_print)
		return (0);
	while (*str_print)
	{
		x += _putfd(*str_print++, file_desc);
	}
	return (x);
}

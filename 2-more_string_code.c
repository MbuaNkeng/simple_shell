#include "main.h"

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int x = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[x])
	{
		destination[x] = source[x];
		x++;
	}
	destination[x] = 0;
	return (destination);
}

/**
 * _strdup - duplicates a string
 * @str_dup: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str_dup)
{
	int len = 0;
	char *result;

	if (str_dup == NULL)
		return (NULL);
	while (*str_dup++)
		len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	for (len++; len--;)
		result[len] = *--str_dup;
	return (result);
}

/**
 * _puts - prints an input string
 * @str_print: the string to be printed
 * Return: Nothing
 */
void _puts(char *str_print)
{
	int x = 0;

	if (!str_print)
		return;
	while (str_print[x] != '\0')
	{
		_putchar(str_print[x]);
		x++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @char_print: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char char_print)
{
	static int x;
	static char buffer[WRITE_BUFFER_SIZE];

	if (char_print == BUFFER_FLUSH || x >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (char_print != BUFFER_FLUSH)
		buffer[x++] = char_print;
	return (1);
}

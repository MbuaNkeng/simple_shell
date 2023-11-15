#include "main.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @input_str: the input string
 * @delim_str: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *input_str, char *delim_str)
{
	int x, y, a, b, num_words = 0;
	char **str;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!delim_str)
		delim_str = " ";
	for (x = 0; input_str[x] != '\0'; x++)
		if (!is_delim(input_str[x], delim_str) && (is_delim(input_str[x + 1], delim_str) || !input_str[x + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (is_delim(input_str[x], delim_str))
			x++;
		a = 0;
		while (!is_delim(input_str[x + a], delim_str) && input_str[x + a])
			a++;
		str[y] = malloc((a + 1) * sizeof(char));
		if (!str[y])
		{
			for (a = 0; a < y; a++)
				free(str[a]);
			free(str);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			str[y][b] = input_str[x++];
		str[y][b] = 0;
	}
	str[y] = NULL;
	return (str);
}

/**
 * **strtow2 - splits a string into words
 * @string: the input string
 * @delimiter: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *string, char delimiter)
{
	int x, y, a, b, num_words = 0;
	char **str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != delimiter && string[x + 1] == delimiter) ||
				    (string[x] != delimiter && !string[x + 1]) || string[x + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	str = malloc((1 + num_words) * sizeof(char *));
	if (!str)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (string[x] == delimiter && string[x] != delimiter)
			x++;
		a = 0;
		while (string[x + a] != delimiter && string[x + a] && string[x + a] != delimiter)
			a++;
		str[y] = malloc((a + 1) * sizeof(char));
		if (!str[y])
		{
			for (a = 0; a < y; a++)
				free(str[a]);
			free(str);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			str[y][b] = string[x++];
		str[y][b] = 0;
	}
	str[y] = NULL;
	return (str);
}

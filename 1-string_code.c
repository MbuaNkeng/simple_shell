#include "main.h"

/**
 * _strlen - returns the length of a string
 * @str_check: the string whose length to check
 * Return: integer length of string
 */
int _strlen(char *str_check)
{
	int x = 0;

	if (!str_check)
		return (0);

	while (*str_check++)
		x++;
	return (x);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @string1: the first strang
 * @string2: the second strang
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @str_search: string to search
 * @str_find: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *str_search, const char *str_find)
{
	while (*str_find)
		if (*str_find++ != *str_search++)
			return (NULL);
	return ((char *)str_search);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, char *source)
{
	char *results = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (results);
}
#include "main.h"

/**
 **_strncpy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@char_num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *destination, char *source, int char_num)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < char_num - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < char_num)
	{
		j = i;
		while (j < char_num)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@num_bytes: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *destination, char *source, int num_bytes)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < num_bytes)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < num_bytes)
		destination[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@parse_str: the string to be parsed
 *@search_char: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *parse_str, char search_char)
{
	do {
		if (*parse_str == search_char)
			return (parse_str);
	} while (*parse_str++ != '\0');

	return (NULL);
}

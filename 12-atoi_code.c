#include "main.h"

/**
 * interactive - returns true if shell is interactive mode
 * @param: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *param)
{
	return (isatty(STDIN_FILENO) && param->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @char_check: the char to check
 * @delimiter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char char_check, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == char_check)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @char_inp: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int char_inp)
{
	if ((char_inp >= 'a' && char_inp <= 'z') || (char_inp >= 'A' && char_inp <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @conv_str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *conv_str)
{
	int x, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0; conv_str[x] != '\0' && flag != 2; x++)
	{
		if (conv_str[x] == '-')
			sign *= -1;

		if (conv_str[x] >= '0' && conv_str[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (conv_str[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

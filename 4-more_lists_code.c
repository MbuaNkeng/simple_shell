#include "main.h"

/**
 * list_len - determines length of linked list
 * @head_node: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *head_node)
{
	size_t x = 0;

	while (head_node)
	{
		head_node = head_node->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head_node: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head_node)
{
	list_t *node = head_node;
	size_t x = list_len(head_node), y;
	char **strings;
	char *string;

	if (!head_node || !x)
		return (NULL);
	strings = malloc(sizeof(char *) * (x + 1));
	if (!strings)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (y = 0; y < x; y++)
				free(strings[y]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, node->str);
		strings[x] = string;
	}
	strings[x] = NULL;
	return (strings);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head_node: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *head_node)
{
	size_t x = 0;

	while (head_node)
	{
		_puts(convert_number(head_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head_node->str ? head_node->str : "(nil)");
		_puts("\n");
		head_node = head_node->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @head_node: pointer to list head
 * @str_match: string to match
 * @next_char: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head_node, char *str_match, char next_char)
{
	char *x = NULL;

	while (head_node)
	{
		x = starts_with(head_node->str, str_match);
		if (x && ((next_char == -1) || (*x == next_char)))
			return (head_node);
		head_node = head_node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head_node: pointer to list head
 * @node_ptr: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head_node, list_t *node_ptr)
{
	size_t x = 0;

	while (head_node)
	{
		if (head_node == node_ptr)
			return (x);
		head_node = head_node->next;
		x++;
	}
	return (-1);
}
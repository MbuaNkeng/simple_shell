#include "main.h"

/**
 * add_node - adds a node to the start of the list
 * @head_node: address of pointer to head node
 * @str_node: str field of node
 * @node_index: node index used by history
 * Return: size of list
 */
list_t *add_node(list_t **head_node, const char *str_node, int node_index)
{
	list_t *new_hnode;

	if (!head_node)
		return (NULL);
	new_hnode = malloc(sizeof(list_t));
	if (!new_hnode)
		return (NULL);
	_memset((void *)new_hnode, 0, sizeof(list_t));
	new_hnode->num = node_index;
	if (str_node)
	{
		new_hnode->str = _strdup(str_node);
		if (!new_hnode->str)
		{
			free(new_hnode);
			return (NULL);
		}
	}
	new_hnode->next = *head_node;
	*head_node = new_hnode;
	return (new_hnode);
}

/**
 * add_node_end- adds a node to the end of the list
 * @head_node: address of pointer to head node
 * @str_node: str field of node
 * @node_index: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **head_node, const char *str_node, int node_index)
{
	list_t *new_node, *node;

	if (!head_node)
		return (NULL);

	node = *head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = node_index;
	if (str_node)
	{
		new_node->str = _strdup(str_node);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head_node = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @first_node: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *first_node)
{
	size_t x = 0;

	while (first_node)
	{
		_puts(first_node->str ? first_node->str : "(nil)");
		_puts("\n");
		first_node = first_node->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head_node: address of pointer to first node
 * @node_delete: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_node, unsigned int node_delete)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!head_node || !*head_node)
		return (0);

	if (!node_delete)
	{
		node = *head_node;
		*head_node = (*head_node)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head_node;
	while (node)
	{
		if (x == node_delete)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_pointer: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_pointer)
{
	list_t *node, *next_node, *head;

	if (!head_pointer || !*head_pointer)
		return;
	head = *head_pointer;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_pointer = NULL;
}

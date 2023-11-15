#include "main.h"

/**
 * _memset - fills memory with a constant byte
 * @ptr_mem: the pointer to the memory area
 * @byte_fill: the byte to fill *s with
 * @byte_amt: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *ptr_mem, char byte_fill, unsigned int byte_amt)
{
	unsigned int i;

	for (i = 0; i < byte_amt; i++)
		ptr_mem[i] = byte_fill;
	return (ptr_mem);
}

/**
 * ffree - frees a string of strings
 * @str_str: string of strings
 */
void ffree(char **str_str)
{
	char **a = str_str;

	if (!str_str)
		return;
	while (*str_str)
		free(*str_str++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @prev_ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @curr_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *prev_ptr, unsigned int prev_size, unsigned int curr_size)
{
	char *p;

	if (!prev_ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(prev_ptr), NULL);
	if (curr_size == prev_size)
		return (prev_ptr);

	p = malloc(curr_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < curr_size ? prev_size : curr_size;
	while (prev_size--)
		p[prev_size] = ((char *)prev_ptr)[prev_size];
	free(prev_ptr);
	return (p);
}

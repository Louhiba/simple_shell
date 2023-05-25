#include "header.h"

/**
 * fr_p_a - clear pointer and NULLs the addr
 * @ptr: addr of pointer to be cleared
 *
 * Return: 1 if cleared, or 0.
 */
int fr_p_a(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

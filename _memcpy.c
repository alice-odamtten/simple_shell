#include "shell.h"

/**
 * _memcpy - copies memory
 * @dest: a void pointer
 * @src: void pointer
 * @n: a variable
 */

void _memcpy(void *dest, const void *src, unsigned int n)
{
	char *srcptr = (char *)src;
	char *destptr = (char *)dest;

	while (n > 0)
	{
		destptr[n - 1] = srcptr[n - 1];
		n--;
	}
	destptr[n] = '\0';
}

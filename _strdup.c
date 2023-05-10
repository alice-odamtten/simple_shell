#include "shell.h"

/**
 * _strdup - duplicate a string
 * @s: string to duplicate
 * Return: Always a string
 */

char *_strdup(const char *s)
{
	size_t e = _strlen(s) + 1;
	char *n = malloc(e);

	if (n == NULL)
	{
		return (NULL);
	}
	_memcpy(n, s, e);
	return (n);
}

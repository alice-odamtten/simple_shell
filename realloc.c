#include "main.h"

/**
 * _eprint_one_line - print error for one line
 * @s: string
 */
void _eprint_one_line(const char *s)
{
	while (*s != '\0')
	{
		_eputchar(*s);
		s++;
	}
}

/**
 *_realloc - allocate extra memory
 *@ptr: void pointer
 *@os: size
 *@nsize: new size
 *Return: Always new space
 */
void *_realloc(void *ptr, size_t os, size_t nsize)
{
	void *nptr;

	if (ptr == NULL)
	{
		return (malloc(nsize));
	}
	if (nsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(nsize);

	if (nptr == NULL)
	{
		return (NULL);
	}
	if (nsize < os)
	{
		_memcpy(nptr, ptr, nsize);
	}
	else
	{
		_memcpy(nptr, ptr, os);
	}
	free(ptr);
	return (nptr);
}

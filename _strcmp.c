#include "shell.h"

/**
 * _strcmp - compares length of a string
 * @s: string to compare
 * @t: string to compare
 * Return: Always zero
 */

int _strcmp(const char *s, const char *t)
{
	while (*s && (*s == *t))
	{
		++s;
		++t;
	}
	return (*(const unsigned char *)s - *(const unsigned char *)t);
}

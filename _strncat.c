#include "shell.h"

/**
 * _strncat - Concanate string
 * @t: A variable
 * @s: A variable
 * @n: Number of string to concanate
 * Return: Always a char
 */

char *_strncat(char *t, const char *s, int n)
{
	char *o = t;

	while (*t != '\0')
	{
		t++;
	}
	while (*s != '\0' && n > 0)
	{
		*t++ = *s++;
		n--;
	}
	*t = '\0';
	return (o);
}


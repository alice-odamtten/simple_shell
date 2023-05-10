#include "shell.h"

/**
 * _strcat - Concanate a string
 * @dest: a variable
 * @src: A variable
 * Return: Always concanated string
 */

char *_strcat(char *dest, const char *src)
{
	char *p = dest;

	while (*p != '\0')
	{
		p++;
	}

	while (*src != '\0')
	{
		*p = *src;
		p++;
		src++;
	}

	*p = '\0';
	return (dest);
}

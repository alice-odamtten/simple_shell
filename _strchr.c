#include "shell.h"

/**
 * _strchr - it search for the occurance of a specified char
 * @r: The char to search from
 * @c: the char to search for
 * Return: always char
 */

char *_strchr(const char *r, char c)
{
	while (*r != '\0')
	{
		if (*r == c)
		{
			return ((char *) r);
		}
		r++;
	}
	return (NULL);
}

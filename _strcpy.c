#include "shell.h"

/**
 * _strcpy - copies a string into another variable
 * @dest: Variable to copy string into
 * @src: Variable to copy string from
 * Return: Always a char
 */

char *_strcpy(char *dest, char *src)
{
	int n = 0;

	while (src[n] != '\0')
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

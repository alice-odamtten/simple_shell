#include "shell.h"

/**
 * _strlen - Counts the number of char in a string
 * @s: the string
 * Return: Always a number
 */

int _strlen(char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

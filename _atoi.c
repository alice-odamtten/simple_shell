#include "shell.h"

/**
 * _atoi - converts a string to an interger
 * @src: pointer to the string to convert
 *
 * Return: the converted integer value
 */
int _atoi(const char *src)
{
	int n = 0;
	int s = 1;
	const char *p = src;

	while (*p == ' ' || *p == '\n' || *p == '\f')
	{
		p++;
	}
	if (*p == '-')
	{
		s = -1;
		p++;
	}
	else if (*p >= '0' && *p <= '9')
	{
		n = n * 10 + (*p - '0');
		p++;
	}

	return (n * s);
}

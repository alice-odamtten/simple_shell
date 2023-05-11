#include  "shell.h"

/**
 * _isalpha - entry point
 * @q: the chr
 * Return: always int
 */

int _isalpha(char q)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

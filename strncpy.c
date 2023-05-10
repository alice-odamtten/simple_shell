#include "shell.h"

/**
 * _strncpy - Copies sepcific amount of string
 * @ds: The variable to copy to
 * @sr: The vaiable to copy from
 * @n: Number of chars to copy
 * Return: Always char
 */

char *_strncpy(char *ds, const char *sr, int n)
{
	char *od = ds;
	int q;

	for (q = 0; i < n && sr[q] != '\0'; q++)
	{
		ds[q] = sr[q];
	}
	for (; q < n; q++)
	{
		ds[q] = '\0';
	}
	return (od);
}

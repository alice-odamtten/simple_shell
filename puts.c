#include "main.h"

/**
 * _puts - print strings with new line
 * @s: the string to print
 */

void _puts(const char *s)
{
	while (*s != '\0')
	{
		_putchar(*s);
		s++;
	}
	_putchar('\n');
}

/**
 * _putchar - prints char
 * @c: the char to print
 */
void _putchar(char c)
{
	if (!c)
	{
		return;
	}
	write(STDOUT_FILENO, &c, 1);
}

/**
 * _eputchar - used for errors
 * @c: the char
 */
void _eputchar(char c)
{
	if (!c)
	{
		return;
	}
	write(STDERR_FILENO, &c, 1);
}

/**
 * _eputs - prints error message
 * @s: string to print for error
 */
void _eputs(const char *s)
{
	while (*s != '\0')
	{
		_putchar(*s);
		s++;
	}
	_putchar('\n');
}

/**
 * _print_one_line - print a line
 * @s: the line to print
 */
void _print_one_line(const char *s)
{
	while (*s != '\0')
	{
		_putchar(*s);
		s++;
	}
}

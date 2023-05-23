#include "main.h"



/**
 * _sttrtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_sttrtok(char str[], const char *delim)
{
	static char *next = NULL;
	char *begin, *stop;

	if (str != NULL) 
	{
		next = str;
	}
	if (next == NULL) 
	{
		return NULL;
	}

	begin = next;
	while (*begin != '\0' && (_strchr(delim, *begin) != NULL)) 
	{
		begin++;
	}

	if (*begin == '\0')
	{
		next = NULL;
		return NULL;
	}
	stop = begin + 1;
	while (*stop != '\0' && (_strchr(delim, *stop) == NULL))
	{
		stop++;
	}

	if (*stop == '\0')
	{
		next = NULL;
	}
	else
	{
		*stop = '\0';
		next = stop + 1;
	}
	return begin;
}



/**
 *_realloc - allocate extra memory
 *@ptr: void pointer
 *@os: size
 *@nsize: new size
 *Return: Always new space
 */
void *_realloc(void *ptr, size_t os, size_t nsize)
{
	void *nptr;

	if (ptr == NULL)
	{
		return (malloc(nsize));
	}
	if (nsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(nsize);

	if (nptr == NULL)
	{
		return (NULL);
	}
	if (nsize < os)
	{
		_memcpy(nptr, ptr, nsize);
	}
	else
	{
		_memcpy(nptr, ptr, os);
	}
	free(ptr);
	return (nptr);
}

/**
 * _getline - gets inputs from the cli
 * @line: string input from the cli
 * @len: len of string
 * @fd: file descriptor
 */
int _getline(char **line, size_t len, int fd)
{
	size_t i = 0;
	size_t buffer_size = len;
	char *buff = *line;
	int bufffer_allocated = 0;
	char *nb;

	if (line == NULL)
		return -1;

	if (buff == NULL)
	{
		bufffer_allocated = 1;
		buffer_size  = 128;
		buff = malloc(sizeof(char *) * buffer_size);
		if (buff == NULL)
			return -1;
	}
 	while (((read(fd, &buff[i], 1)) > 0) && buff[i] != '\n')
	{
		i++;
		if (i > buffer_size -1)
		{
			nb = _realloc(buff, sizeof(char *) * buffer_size, sizeof(char *) * (buffer_size * 2));
			if (nb == NULL)
			{
				free(nb);
				return -1;
			}
			buff = nb;
		}
	}
	buff[i] = '\0';
	*line = buff;

	if (bufffer_allocated == 1)
	free(buff);

	return (i);
}
/**
 * _eprint_one_line - displays strings to std err
 * @s: string to print
 * Return: nothing
 */
void _eprint_one_line(const char *s)
{
	while (*s != '\0')
	{
		_eputchar(*s);
		s++;
	}
}

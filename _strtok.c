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
	static char *next;
	char *begin, *stop;

	if (str != NULL)
	{
		next = str;
	}
	if (next == NULL)
	{
		return (NULL);
	}

	begin = next;
	while (*begin != '\0' && (_strchr(delim, *begin) != NULL))
	{
		begin++;
	}

	if (*begin == '\0')
	{
		next = NULL;
		return (NULL);
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
	return (begin);
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
 * Return: 1 or 0 or Negative
 */
int _getline(char **line, size_t *len, int fd)
{
	size_t buffer_size = *len, i = 0, obs, nbs;
	char *buff = *line, *nb;
	int buffer_allocated = 0;
	char tmp[MAX_COMMAND_LENGTH];

	if (line == NULL || len == NULL)
		return (-1);
	if (buff == NULL)
	{
		buffer_allocated = 1;
		buffer_size  = 128;
		buff = malloc(sizeof(char) * buffer_size);
		if (buff == NULL)
			return (-1);
	}
	while (((read(fd, &buff[i], 1)) > 0))
	{
		if (buff[i] == '\n')
			break;
		i++;
		if (i >= (buffer_size - 1))
		{	obs = buffer_size * sizeof(char);
			nbs = buffer_size / 2 + buffer_size;
			nb = _realloc(buff, obs, sizeof(char) * nbs);
			if (nb)
			{
				free(buff);
				return (-1);
			}
			buff = nb;
		}

	}
	buff[i] = '\0';
	_strcpy(tmp, buff);
	*line = tmp;
	*len = buffer_size;
	if (buffer_allocated == 1)
		free(buff);

	return (1);
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

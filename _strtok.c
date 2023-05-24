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
	size_t buff_size = *len, bytesread;
	char *buff = *line;
	char *temp;

	if (line == NULL || len == NULL)
		return (-1);
	temp = handle_eof(buff, buff_size, &bytesread, fd);

	if (bytesread == 0)
	{
		free(buff);
		return (-1);
	}
	else
	{
		*line = temp;
		*len = buff_size;
	}
	return (bytesread);
}

/**
 * handle_eof - handles error
 * @buff: variable to read into
 * @buffer_size: size of buffer read
 * @br: the status of read function
 * @fd: file descriptor
 * Return: Always char
 */
char *handle_eof(char *buff, size_t buffer_size, size_t *br, int fd)
{
	size_t i = 0, obs, nbs;
	char *nb;

	if (buff == NULL)
	{
		buffer_size  = 128;
		buff = malloc(sizeof(char *) * buffer_size);
		if (buff == NULL)
			return (NULL);
	}
	while (((*br = read(fd, (&buff[i]), 1)) > 0) && buff[i] != '\n')
	{
		i++;
		if (i > buffer_size - 1)
		{
			obs = sizeof(char *) * buffer_size;
			nbs = sizeof(char *) * (buffer_size / 2 + obs);
			nb = _realloc(buff, obs, nbs);

			if (nb == NULL)
			{
				free(nb);
				return (NULL);
			}
			buff = nb;
		}
	}
	buff[i] = '\0';

	return (buff);
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

#include "main.h"

/**
 * _strpbrk - breakes string into parets
 * @str: string
 * @set: part to break
 * Return: Alwats string
 */
char *_strpbrk(const char *str, const char *set)
{
	const char *tr;

	while (*str != '\0')
	{
		tr = set;
		while (*tr != '\0')
		{
			if (*tr == *str)
			{
				return ((char *)str);
			}
			tr++;
		}
		str++;
	}
	return (NULL);
}

/**
 * _sttrtok - tokenize string
 * @p: string to tokenize
 * @delim: the delimitor
 * Return: Always a string
 */
char *_sttrtok(char *p, const char *delim)
{
	static char *t;
	static char *nt;
	char *dp, *ct;

	if (p != NULL)
	{
		t = p;
		nt = p;
	}
	if (t == NULL)
	{
		return (NULL);
	}
	dp = _strpbrk(nt, delim);
	if (dp != NULL)
	{
		*dp = '\0';
		ct = t;
		t = dp + 1;
		nt = t;
		return (ct);
	}
	else if (*t != '\0')
	{
		ct = t;
		t = NULL;
		return (ct);
	}
	return (NULL);
}

/**
 * _getline - reads line from user
 * @line: pointer to store string
 * @len: the length
 * @fd: the buffer
 * Return: Always an int
 */
int _getline(char **line, size_t len, int fd)
{
	int i = 0;
	size_t b = len;
	char *buff = *line, *nb;
	int bufffer_allocated = 0;

	if (line == NULL)
	{
		return (-1);
	}
	if (buff == NULL)
	{
		bufffer_allocated = 1;
		b = 128;
		buff = malloc(sizeof(char *) * b);
		if (buff == NULL)
		{
			return (-1);
		}
		while (((read(fd, &buff[i], 1)) > 0) && buff[i] != '\n')
		{
			i++;
			if (i > b - 1)
			{
				nb = _realloc(buff, b * sizeof(char *), (b * 2) *  sizeof(char *));
				if (nb == NULL)
				{
					free(nb);
					return (-1);
				}
				buff = nb;
			}
		}
		buff[i] = '\0';
		*line = buff;
		if (bufffer_allocated == 1)
		{
			free(buff);
		}
	}
	return (i);
}



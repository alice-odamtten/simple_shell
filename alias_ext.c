#include "main.h"


/**
 * surround_with_quotes - surrounds a string with quotes
 * @str: the string to add qoutes
 * Return: a quouted string
 */
char *surround_with_quotes(char *str)
{
	size_t len = _strlen(str);
	char *quoted_str = malloc(len + 3);

	if (quoted_str == NULL)
	{
		_eputs("Error: Could not allocate memory for quoted string.");
		return (NULL);
	}

	quoted_str[0] = '\'';

	_strncpy(quoted_str + 1, str, len);

	quoted_str[len + 1] = '\'';
	quoted_str[len + 2] = '\0';

	return (quoted_str);
}

/**
 * contains_quotes - checks if a string contains qoute
 * @str: the string
 * Return: 1 if true  or 0
 */
int contains_quotes(const char *str)
{
	return ((_strchr(str, '\"') != NULL) || (_strchr(str, '\'') != NULL));
}

/**
 * is_valid_alias - checks if an alias
 * @info: global data struction for application state
 * @s: the alias string
 * Return: 1 if true 0r 0 if false
 */
int is_valid_alias(g_data *info, char *s)
{
	char *arg_check;

	arg_check = _strchr(s, '=');
	if (!arg_check)
	{
		error_handler(info, 127);
		return (0);
	}

	return (1);
}

/**
 * find_alias - searches for an alias
 * @info: global data structure for application state
 * @idx: index to check for alias
 * Return: a node
 */
l_node *find_alias(g_data *info, int idx)
{
	l_node *tmp;

	tmp = info->alias_db;
	while (tmp != NULL)
	{
		if (_strcmp(info->arguments[idx], tmp->data) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}

	return (NULL);
}


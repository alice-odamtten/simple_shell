#include "main.h"

/**
 * exit_func - function to handle exits
 * @info: globals for state manaagements
 * Return: 1 or 0
 */
int exit_func(g_data *info)
{
	char *u;
	int status;

	if (info->arguments[1] != NULL)
	{
		/* Todo: check if is a valid digit */
		u = _sttrtok(info->arguments[1] + 4, " ");
		status = _atoi(u);
		exit(status);
	}
	else
	{
		/* exit(0) */
		return (0);
	}
	return (0);
}

/**
 * cd_func - handles cd cmds
 * @info: globals for state manaagements
 * Return: 1 or 0
 */
int cd_func(g_data *info)
{
	char *d, *n, *c;

	if (info->arguments[1] == NULL)
	{
		d = _getenv("HOME", info->environ);
		if (d == NULL)
		{
			perror("cd");
			return (-1);
		}
	}
	else if (strcmp(info->arguments[1], "-") == 0)
	{
		d = _getenv("OLDPWD", info->environ);
		if (d == NULL)
		{
			perror("cd");
			return (-1);
		}
	}
	else
	{
		n = malloc(PATH_MAX);
		getcwd(n, PATH_MAX);
		_setenv("OLDPWD", n, 1);
		free(n);
		if (chdir(info->arguments[1]))
		{
			perror("cd");
			return (-1);
		}
		c = malloc(PATH_MAX + 5);
		getcwd(c, PATH_MAX);
		_setenv("PWD", c, 1);
		free(c);
	}

	return (1);
}

/**
 * alias_func - alias handler
 * @info: globals and state managements
 * Return: 1 or 0
 */
int alias_func(g_data *info)
{
	char *alias;
	l_node *tmp;
	int idx = 1;

	if (info->arguments[1])
	{
		alias = _strchr(info->arguments[1], '=');
		if (!alias)
		{
			while (info->arguments[idx] != NULL)
			{
				tmp = find_alias(info, idx);
				if (tmp)
				{
					print_alias(tmp);
				}
				else
					error_handler(info, 127);
				idx++;
			}
		}
		else
			set_alias(info);
	}
	else
	{
		tmp = info->alias_db;
		while (tmp != NULL)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
	}
	return (1);
}

/**
 * help_func - a help
 * @info: globals and state management
 * Return: 1 or 0
 */
int help_func(g_data *info)
{
	_puts("Simple Shell");
	_puts("builtin commands avaiable are:");
	_puts("exit - Used to exit the shell");
	_puts("cd - Used to change directory");
	_puts("help - Gives lists of command s available");
	_puts("setenv - Initialize a new environment variable");

	return (1);
}

/**
 * builtin_setenv - handles variable settitng
 * @a: variable to set
 * @e: value key of env
 * Return: 1 or 0
 */
int builtin_setenv(const char *a, const char *e)
{
	int i = 1;
	char *ev;

	if (a == NULL || e == NULL)
	{
		perror("setenv");
		return (-1);
	}
	ev = getenv(a);
	if (ev != NULL)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}

	if (_setenv(a, e, i) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}


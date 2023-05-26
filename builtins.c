#include "main.h"

/**
 * exit_func - function to handle exits
 * @info: globals for state manaagements
 * Return: 1 or 0
 */
int exit_func(g_data *info)
{
	char *u;
	size_t status, len;

	if (info->arguments[1] != NULL)
	{
		/* Todo: check if is a valid digit */
		u = _sttrtok(info->arguments[1], " ");

		status = _atoi(u);
		len = _strlen(info->arguments[1]);

		if (len > 10 || status < 1 || status > (unsigned int)INT_MAX)
		{
			error_handler(info, 2);
			info->status = 2;
			return (0);
		}

		info->status = status % 256;
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
	char *dir;
	int ishome, ishome2, isddash;

	dir = info->arguments[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(info);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(info);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(info);
		return (1);
	}

	cd_to(info);
	free(info->command);
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
int help_func(__attribute__((unused)) g_data *info)
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
 * is_executable - determines if is an executable
 *
 * @info: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(g_data *info)
{
	struct stat st;
	int i;
	char *input;

	input = info->arguments[0];
	if (input == NULL)
		return (-1);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	error_handler(info, 127);
	return (-1);
}




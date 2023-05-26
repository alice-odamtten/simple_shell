#include "main.h"

/**
 * error_handler - handles various errrors
 * @info: global data structure for application state
 * @err_val: error value
 * Return: 1 or 0
 */
int error_handler(g_data *info, int err_val)
{
	char *er_str;

	switch (err_val)
	{
		case -1:
			er_str = env_err(info);
			break;
		case 2:
			er_str = exit_shell_err(info);
			break;
		case 3:
			er_str = get_cd_error(info);
			break;
		case 126:
			er_str = path_126_err(info);
			break;
		case 127:
			er_str = not_found_err(info);
			break;
		default:
			er_str = command_failure_err(info);
	}

	if (er_str)
	{
		write(STDERR_FILENO, er_str, _strlen(er_str));
		free(er_str);
	}

	return (err_val);
}

/**
 * handle_builtins - handles the builtins functions
 * @info: global data structure for application state
 * Return: 1 or 0
 */
ssize_t handle_builtins(g_data *info)
{
	int idx, result = -1;
	csh_builtin cbuiltins[] = {
	{"exit", exit_func},
	{"cd", cd_func},
	{"env", _envp},
	/**
	 * {"setenv", _setenv},
	 * {"unset", _unsetenv},
	 */
	{"alias", alias_func},
	{"unalias", unalias_func},
	{"help", help_func},
	{NULL, NULL}
	};

	if (info->arguments[0])
	{
		for (idx = 0; cbuiltins[idx].name; idx++)
		{
			if (_strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
			{
				if (_strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
				{
					result = cbuiltins[idx].handler(info);
					break;
				}
			}
		}
	}
	return (result);
}

/**
 * _strncmp - compares length of a string
 * @s: string to compare
 * @t: string to compare
 * @len: length to compare
 * Return: Always zero
 */

int _strncmp(const char *s, const char *t, size_t len)
{
	size_t i = 0;

	while ((*s && (*s == *t)) && i < len)
	{
		++s;
		++t;
		i++;
	}
	return (*(const unsigned char *)s - *(const unsigned char *)t);
}

/**
 * token_copier - copies the content of token
 * @info: global data structure for application state
 * @token: an array of tokens
 * @idx: index of token
 * Return: 1 or 0
 */
int token_copier(g_data *info, char **token, int *idx)
{
	char *token_copy;

	token_copy = malloc(sizeof(char *) * 1024);
	if (!token_copy)
	{
		free(token_copy);
		return (0);
	}
	_strcpy(token_copy, info->arguments[*idx]);
	(*idx)++;
	while (info->arguments[*idx] != NULL)
	{
		_strcat(token_copy, " ");
		_strcat(token_copy, info->arguments[*idx]);

		if ((_strchr(info->arguments[*idx], '\''))
				|| (_strchr(info->arguments[*idx], '\"')))
		break;

		(*idx)++;
	}
	*token = _sttrtok(token_copy, "=");
	free(token_copy);

	return (*idx);
}

/**
 * perform_alias_insert - inserts an alias into the alias db
 * @info: global data structure for application state
 * @data: alias key
 * @sd: alias value
 * Returns: nothing
 */
void perform_alias_insert(g_data *info, char **data, char **sd)
{
	l_node *tmp;

	tmp = info->alias_db;
	if (tmp != NULL)
	{
		while (tmp != NULL)
		{
			if (_strcmp(*data, tmp->data) == 0)
			{
				tmp->data = *data;
				tmp->sub_data = *sd ? *sd : "'\'\'";
				break;
			}
			else if (tmp->next == NULL)
			{
				insert_at_end(&(info->alias_db), _strdup(*data), _strdup(*sd));
			}

			tmp = tmp->next;
		}
	}
	else
	{
		insert_at_end(&(info->alias_db), _strdup(*data), _strdup(*sd));
	}
}

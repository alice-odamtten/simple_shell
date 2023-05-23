#include "main.h"

/**
 * parse_command - parses inputs from the cli
 * @info: globals for state managements
 * Return: nothing
 */
void parse_command(g_data *info)
{
	int argIndex = 0, idx = 0;
	char *token, *rest, *alias_cmd;
	char *quote = "\"'";
	char *delim = " \t\n\r\a";
	l_node *alias;

	info->number_of_args = 0;

	if (_strchr(quote, info->command[0]))
	{
		alias = find_alias(info, 0);
		if (alias)
			_strcpy(info->command, alias->sub_data);
		rest = sanitize_string2(info->command);
		token = _sttrtok(rest, delim);
	}
	else
	{
		alias = find_alias(info, 0);

		if (alias)
			_strcpy(info->command, sanitize_string2(alias->sub_data));

		rest = info->command;
		token = _sttrtok(rest, delim);
	}

	while (token != NULL)
	{
		info->arguments[argIndex] = token;
		token = _sttrtok(NULL, delim);
		argIndex++;
		info->number_of_args++;
	}
	info->arguments[argIndex] = NULL;
}

/**
 * find_command_path - find path for command
 * @info: globals and state managements
 * @command: input command
 * Return: command path
 */
char *find_command_path(g_data *info, const char *command)
{
	char *path_env, *path_env_cpy, *path;
	char *command_path[MAXIMUM_CONTENT_LENGTH];

	path_env = _getenv("PATH", info->environ);
	path_env_cpy = strdup(path_env);

	path = _sttrtok(path_env_cpy, ":");

	while (path != NULL)
	{
		strcpy(command_path, path);

		if (commandPath[strlen(command_path) - 1] != '/')
			strcat(command_path, "/");

		strcat(command_path, command);

		if (access(command_path, F_OK) == 0)
		{
			free(path_env_cpy);
			return (strdup(command_path));
		}

		path = strtok(NULL, ":");
	}

	free(path_env_cpy);
	return (NULL);
}

/**
 * sanitize_string - sanitizes a string
 * @str: the string to be sanitized
 * Return: a new string without quotes
 */
char *sanitize_string(char *str)
{
	int len = strlen(str), j = 0, i;
	char *sanitized_str = malloc(len * 2 + 1);

	if (sanitized_str == NULL)
	{
		_eputs("Error: Could not allocate memory for sanitized string.\n");
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
		{
			sanitized_str[j++] = '\\';
		}
		sanitized_str[j++] = str[i];
	}
	sanitized_str[j] = '\0';
	return (sanitized_str);
}

/**
 * sanitize_string2 - removes quoutes from strings
 * @str: string to sanitize
 * Return: a sanitized string
 */
char *sanitize_string2(char *str)
{
	int len = strlen(str), j = 0, i;
	char sanitized_str[(len * 2) + 1];

	for (i = 0; i < len; i++)
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
		{
			continue;
		}
		sanitized_str[j++] = str[i];
	}
	sanitized_str[j] = '\0';

	return (strdup(sanitized_str));
}
